/**
 ******************************************************************************
 * @file    led_button_switch.c
 * @version V1.0.0
 * @date    2017/11/10
 * @brief   The file defines macros related to LED and BUTTON of demo board, and some driver functions of LED and BUTTON.
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
#include "psdk_arch_sys.h"
#include "led_button_switch.h"
#include <stm32f10x.h>
#include "log_printf.h"
#include "flash.h"
//#include <os_util.h>


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

//default PSDK communication interface setting
#define DEFAULT_SETTINGS    0xFFFFFFFF

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

//button press callback function
static ButtonPressCallbackFunc s_btPressCallback = NULL;

/* Exported variables --------------------------------------------------------*/

//PSDK communication interface setting variable
extern uint32_t g_can_uart_sw_settings;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/**
 * @brief LED initialize.
 * @param None.
 * @return None.
 */
void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* GPIO Periph clock enable */
    RCC_APB2PeriphClockCmd(LED1_RCC, ENABLE);

    /* Configure GPIO_InitStructure */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_InitStructure.GPIO_Pin = LED1_PIN;
    GPIO_Init(LED1_PORT, &GPIO_InitStructure);
}

/**
 * @brief Control LED turn on, turn off or toggle.
 * @param led LED controlled.
 * @param eLedOption LED operating option.
 */
void LED_Control(E_LED led, E_LEDOption eLedOption)
{
    GPIO_TypeDef *ledPort;
    uint16_t ledPin;

    if (led == LED1_GREEN) {
        ledPort = LED1_PORT;
        ledPin = LED1_PIN;
    } else {
        return;
    }

    if (eLedOption == LED_OPT_ON) {
        GPIO_ResetBits(ledPort, ledPin);
    } else if (eLedOption == LED_OPT_OFF){
        GPIO_SetBits(ledPort, ledPin);
    } else if (eLedOption == LED_OPT_TOGGLE) {
        if (GPIO_ReadOutputDataBit(ledPort, ledPin) == 1) {
            GPIO_ResetBits(ledPort, ledPin);
        } else {
            GPIO_SetBits(ledPort, ledPin);
        }
    }
}


/************************ (C) COPYRIGHT DJI Innovations *******END OF FILE******/
