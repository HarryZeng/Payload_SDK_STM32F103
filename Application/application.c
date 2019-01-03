/**
 ******************************************************************************
 * @file    application.c
 * @version V1.3.0
 * @date    2018/09/19
 * @brief   An example program of PSDK for demo board.
 *
 * @copyright (c) 2017-2018 DJI. All rights reserved.
 *
 * All information contained herein is, and remains, the property of DJI.
 * The intellectual and technical concepts contained herein are proprietary
 * to DJI and may be covered by U.S. and foreign patents, patents in process,
 * and protected by trade secret or copyright law.  Dissemination of this
 * information, including but not limited to data and other proprietary
 * material(s) incorporated within the information, in any form, is strictly
 * prohibited without the express written consent of DJI.
 *
 * If you receive this source code without DJI’s authorization, you may not
 * further disseminate the information, and you must immediately remove the
 * source code and notify DJI of its removal. DJI reserves the right to pursue
 * legal actions against you for any loss(es) or damage(s) caused by your
 * failure to do so.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include <app_config.h>
#include <psdk.h>
#include "led_button_switch.h"
//#include "ms5607.h"
#include <string.h>
#include "sys.h"
#include "uart.h"
#include "log_printf.h"
#include <stdio.h>
#include <psdk_upper.h>
//#include "flash.h"
#include "communicate.h"
#include "application.h"
#include "app_infor.h"
#include "test_app_func.h"
#include "test_msg_push.h"
#include "test_payload_cam_emu.h"
#include "test_payload_gimbal_emu.h"
#include "MotorDriver.h"
#include "ADC.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

//PSDK protocol handle structure
T_PsdkUpper s_psdkUpperHandle;

#if SKYPORT_FW_FIX_VER_NEED
//fixed SKYPORT FW version
static T_PsdkUserFixSkyport s_fixSkyport = {0};
#endif

#if PSDK_APP_ALIAS_NEED
//PSDK application alias
static T_PsdkUserCustomInfo s_productAlias;
#endif

//buffer used to receive data from UART interface
static uint8_t s_uartRecBuf[PSDK_UART_REC_BUF_LEN];
//buffer used to store data to be sent
static char s_printBuffer[512];
//PSDK user information
static T_PsdkUserInfo s_userInfo;

/* Exported variables --------------------------------------------------------*/

//a switch flag of PSDK communication channel
uint32_t g_can_uart_sw_settings = 0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
 * @brief Check user information string and fill in user information to structure.
 * @param userInfo Pointer to user information structure to be written.
 * @return None.
 */
static void FillInUserInfo(T_PsdkUserInfo *userInfo)
{
    memset(userInfo->APP_Name, 0, sizeof(userInfo->APP_Name));
    memset(userInfo->APP_Id, 0, sizeof(userInfo->APP_Id));
    memset(userInfo->APP_Key, 0, sizeof(userInfo->APP_Key));
    memset(userInfo->DeveloperAccount, 0, sizeof(userInfo->DeveloperAccount));

    if(strlen(USER_APP_NAME) <= sizeof(userInfo->APP_Name) &&
        strlen(USER_APP_ID) <= sizeof(userInfo->APP_Id) &&
        strlen(USER_APP_KEY) <= sizeof(userInfo->APP_Key) &&
        strlen(USER_DEVELOPER_ACCOUNT) <= sizeof(userInfo->DeveloperAccount)) {
        strcpy(userInfo->APP_Name, USER_APP_NAME);
        strcpy(userInfo->APP_Id, USER_APP_ID);
        strcpy(userInfo->APP_Key, USER_APP_KEY);
        strcpy(userInfo->DeveloperAccount, USER_DEVELOPER_ACCOUNT);
    } else {
        LOG_ERROR("Length of user information string is beyond limit. Please check.\r\n");
    }

    if(!strcmp(userInfo->APP_Name, "your_app_name") ||
        !strcmp(userInfo->APP_Id, "your_app_id") ||
        !strcmp(userInfo->APP_Key, "your_app_key") ||
        !strcmp(userInfo->DeveloperAccount, "your_developer_account")) {
        LOG_ERROR("Please fill in correct user information to app_infor.h file.\r\n");
    }
}

/* Exported functions --------------------------------------------------------*/

/**
 * @brief Low level PSDK frame send function.
 * @param pSendData Pointer to frame to be sent.
 * @param dataLen Frame length.
 * @return PSDK function process state.
 */
E_PsdkStat Psdk_Write(const uint8_t *pSendData, uint16_t dataLen)
{
    UART_Write(PSDK_UART_NUM, pSendData, dataLen);
    return PSDK_STAT_OK;
}

/**
 * @brief Low level PSDK frame read function.
 * @param pReadData Pointer to frame to be read.
 * @param dataLen Frame length.
 * @retval -1: Read error.
 *          not -1: Counts of bytes read actually.
 */
int Psdk_Read(uint8_t *pReadData, uint16_t dataLen)
{
    int res;

    res = UART_Read(PSDK_UART_NUM, pReadData, dataLen);

    return res;
}

#if PSDK_ARCH_USE_OS
/**
 * @brief Demo board based task function.
 * @details Control the switch of PSDK communication channel and LED.
 * @param parameter
 * @return None.
 */
void RunIndicateTask(void const *parameter)
{
    uint16_t cnt = 0;
    uint32_t setting = 0;

    while (1) {
        setting = flash_read_settings();
        if (g_can_uart_sw_settings != setting) {
            flash_wirte_settings(g_can_uart_sw_settings);
            Button_StartUpdate();
        }

        OS_DELAY(1);
        if (cnt++ > 500) {
            LED_Control(LED1_GREEN, LED_OPT_TOGGLE);
            cnt = 0;
        }
    }
}

/**
 * @brief PSDK test task function.
 * @details Send sensor MS5607's data to mobile APP via transparent transmission and float window style.
 * @param parameter
 * @return None.
 */
void PsdkTestTask(void const *parameter)
{
    double temp, press;
    uint16_t realSendLen;

    Ms5607_Init();

    /*
     * Please keep packet transmission frequency less than 200Hz.
     * */

    while (1) {
        Ms5607_GetSenorData(&temp, &press);
        sprintf(s_printBuffer, "Demo Sensor Info:\r\n\r\nBaro Pre = %f mbar\r\n\r\nBoard Temp = %f `C\r\n", press, temp);

        //push this info to DJI Pilot Floating Window
        PsdkAppFunc_PushMsgToFloatingWindow(&s_psdkUpperHandle, s_printBuffer);

        //transfer this info to MSDK
        PsdkAppFunc_TransferToApp(&s_psdkUpperHandle, (const uint8_t *) s_printBuffer, strlen(s_printBuffer) + 1,
                                  &realSendLen);
        OS_DELAY(1000);
    }
}

/**
 * @brief PSDK data receive task function.
 * @note All callback function process in this task.
 * @param parameter
 * @return None.
 */
void ProcessPsdkRecTask(void const *parameter)
{
    int res = 0;

    while (1) {
        //res = UART_Read(PSDK_UART_NUM, s_uartRecBuf, sizeof(s_uartRecBuf));
        res = Psdk_Read(s_uartRecBuf, sizeof(s_uartRecBuf));

        if (res > 0) {
            //===================== PSDK Recievie Function ==============================//
            //all callbacks process in this thread.
            PsdkUpper_ProcessReceiveData(&s_psdkUpperHandle, s_uartRecBuf, res);

        }

        osDelay(1);
    }
}
#else
/**
 * @brief Demo board communication interface switch function.
 * @details Control whether SKYPORT adapter connects to MCU on development board. If not, users can
 * @param None.
 * @return None.
 */
void PsdkComInfSw(void)
{
    uint32_t setting = 0;

    //setting = flash_read_settings();
	setting = 1;
    if (g_can_uart_sw_settings != setting) {
//        flash_wirte_settings(g_can_uart_sw_settings);
//        Button_StartUpdate();
    }
}

/**
 * @brief PSDK running indicate function.
 * @param None.
 * @return None.
 */
void PsdkRunIndicate(void)
{
   // LED_Control(LED1_GREEN, LED_OPT_TOGGLE);
}

/**
 * @brief PSDK test function.
 * @details Send sensor MS5607's data to mobile APP via transparent transmission and float window style.
 * @param None.
 * @return None.
 */
void PsdkMotorTest(void)
{
		char *Status[]={"Opening","closing","Stop"};
		
		char *MotorStatus;
    uint16_t realSendLen;

		if(Motor_Run_flag==1) 
		{
			if(Motor_Direction_flag==1)
					MotorStatus = Status[0];
			else if(Motor_Direction_flag==0)
					MotorStatus = Status[1];
		}
		else if(Motor_Run_flag==0) MotorStatus = Status[2];
			
    sprintf(s_printBuffer, "Motor:\r\n\r\n Status = %s \r\n\r\n Voltage : %f", MotorStatus,ADC_value);

    //push this info to DJI Pilot Floating Window
    PsdkAppFunc_PushMsgToFloatingWindow(&s_psdkUpperHandle, s_printBuffer);

    //transfer this info to MSDK
    PsdkAppFunc_TransferToApp(&s_psdkUpperHandle, (const uint8_t *) s_printBuffer, strlen(s_printBuffer) + 1,
                              &realSendLen);
}


void PsdkBigLEDTest(void)
{
		char *Status[]={"Open","close"};
		
		char *LEDStatus;
    uint16_t realSendLen;

		if(LED_Open_Flag==1) 
		{
			LEDStatus = Status[0];
			USART_TX_BUF[8] = 0x01;
		}
		else if(LED_Open_Flag==0) 
		{
			LEDStatus = Status[1];
			USART_TX_BUF[8] = 0x00;
		}

    sprintf(s_printBuffer, "MainLED:\r\n\r\n Status = %s \r\n\r\n Voltage : %f", LEDStatus,ADC_value);

    //push this info to DJI Pilot Floating Window
    PsdkAppFunc_PushMsgToFloatingWindow(&s_psdkUpperHandle, s_printBuffer);

    //transfer this info to MSDK
    PsdkAppFunc_TransferToApp(&s_psdkUpperHandle, (const uint8_t *) s_printBuffer, strlen(s_printBuffer) + 1,
                              &realSendLen);
}

/**
 * @brief PSDK data receive and process function.
 * @param None.
 * @return None.
 */
void PsdkProcessRec(void)
{
    int res = 0;

    res = Psdk_Read(s_uartRecBuf, sizeof(s_uartRecBuf));

    if (res > 0) {
        PsdkUpper_ProcessReceiveData(&s_psdkUpperHandle, s_uartRecBuf, res);
    }
}
#endif

/**
 * @brief Initialize the load application.
 * @param None.
 * @return None.
 */
void application_init(void)
{
    //device init
    LED_Init();
    //LED_Control(LED1_GREEN, LED_OPT_OFF);
	
    LOG_Init();

    UART_Init(PSDK_UART_NUM, 115200);

    //===================== PSDK init ==============================//
    //base init
    FillInUserInfo(&s_userInfo);
    PsdkUpper_Init(&s_psdkUpperHandle, &s_userInfo);
    PsdkUpper_RegSendFunction(&s_psdkUpperHandle, Psdk_Write);

    //app function init
    PsdkAppFunc_Init(&s_psdkUpperHandle);
    PsdkAppFunc_SetReceiveFromAppCallback(&s_psdkUpperHandle, Test_ReceiveFromMobileSDKFunc);

    PsdkAppFunc_SetWidgetList(&s_psdkUpperHandle, g_TestWidgetList, g_TestWidgetCount);
    PsdkAppFunc_RegGetWidgetValueCallback(&s_psdkUpperHandle, Test_GetWidgetValueFunc);
    PsdkAppFunc_RegSetWidgetValueCallback(&s_psdkUpperHandle, Test_SetWidgetValueFunc);

    //Msg subscribe Function init, callback functions in Application/psdk_test/test_msg_push.c
    PsdkMsgSub_Init(&s_psdkUpperHandle);
    PsdkMsgSub_RegMsgCallbackList(&s_psdkUpperHandle, &g_PushDataMsgCallbackList);

    //Camera function Emulate Test, callback functions in Application/psdk_test/test_payload_cam_emu.c
    //If want transfer video to Mobile SDK or DJI Pilot, this function must call to init Payload camera.
    //PsdkCamera_Init(&s_psdkUpperHandle, &g_testCameraHandler);

    //Gimbal function Emulate Test, callback functions in Application/psdk_test/test_payload_gimbal_emu.c
    PsdkGimbal_Init(&s_psdkUpperHandle, &g_testGimbalHandler);
    //===================== PSDK init End ============================//

    //set fixed SKYPORT FW version
#if SKYPORT_FW_FIX_VER_NEED
    s_fixSkyport.verMajor  = SKYPORT_FW_FIX_VER_MAJOR;
    s_fixSkyport.verMinor  = SKYPORT_FW_FIX_VER_MINOR;
    s_fixSkyport.verModify = SKYPORT_FW_FIX_VER_MODIFY;
    s_fixSkyport.verDebug  = SKYPORT_FW_FIX_VER_DEBUG;

    PsdkUpper_SetFixVersion(&s_fixSkyport);
#endif

    //set PSDK product alias
#if PSDK_APP_ALIAS_NEED
    strcpy(s_productAlias.ProductAlias, PSDK_APP_ALIAS);
    PsdkUpper_SetProductAlias(&s_productAlias);
#endif
}
