/**
 *********************************************************************
 * @file    psdk_payload_gimbal.c
 * @version V1.0.0
 * @date    2017/11/10
 * @brief   This file provides the API functions for handling the gimbal
 * commands from the mobile app (ground) via PSDK port.
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
 *********************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include <psdk.h>
#include <psdk_cmdset_define/psdk_cmdset_gimbal.h>

/** @addtogroup PSDK
 * @{
 */

/** @defgroup PSDK_Gimbal PSDK Gimbal
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/** @defgroup Gimbal_Private_Macro Private Macro
 * @{
 */

/**
 * @brief Macro used to define gimbal command process function.
 */
#define MODLE_FUNC_GIMCMD(name) \
static E_PsdkStat \
GimbalCmd_##name(struct _PsdkProt *protHandle, const T_PsdkProtInfo *inProtInfo, const uint8_t *inProtData)\
{\
    T_PsdkGimbal##name##Ack ack;\
    ack.ackCode = PSDK_CMD_ACK_CODE_UNSUPPORT;\
    if (s_gimbalHandler.name != NULL) {\
        s_gimbalHandler.name((const T_PsdkGimbal##name##Req *) inProtData, &ack);\
    }\
    PsdkProto_SendAckData(protHandle, inProtInfo, (uint8_t *) &ack, sizeof(T_PsdkGimbal##name##Ack));\
    return PSDK_STAT_OK;\
}

/**
 * @brief Function name macro.
 */
#define GIMCMD(name)    GimbalCmd_##name

/**
 * @}
 */

/* Private variables ---------------------------------------------------------*/

/** @defgroup Gimbal_Private_Variables Private Variables
 * @{
 */

///gimbal command callback function list
static T_PsdkGimbalHandler s_gimbalHandler;
///gimbal command support state
static uint8_t s_isSupportGimbal = 0;

/**
 * @}
 */

/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup Gimbal_Private_Functions Private functions
 * @{
 */

/**
 * @brief Handle Get Gimbal State command.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
MODLE_FUNC_GIMCMD(GetGimbalState)

/**
 * @brief Handle Set Gimbal Mode command.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
MODLE_FUNC_GIMCMD(SetGimbalMode)

/**
 * @brief Handle Gimbal Return Head command.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
MODLE_FUNC_GIMCMD(ReturnHead)

/**
 * @brief Handle Control Gimbal Angle Speed command.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
MODLE_FUNC_GIMCMD(ControlSpeed)

/**
 * @brief Handle Gimbal Calibration command.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
MODLE_FUNC_GIMCMD(StartCalibration)

/**
 * @brief Handle Get Gimbal Command Set Support State command.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
static E_PsdkStat
GimbalCmd_SupportState(struct _PsdkProt *protHandle, const T_PsdkProtInfo *inProtInfo, const uint8_t *inProtData)
{
    T_PsdkGimbalSupportStateAck ack;
    ack.ackCode = PSDK_CMD_ACK_CODE_OK;
    ack.isGimbalCmdSetSupport = s_isSupportGimbal;

    PsdkProto_SendAckData(protHandle, inProtInfo, (uint8_t *) &ack, sizeof(T_PsdkGimbalSupportStateAck));
    return PSDK_STAT_OK;
}

/**
 * @}
 */

/** @addtogroup Gimbal_Private_Variables
 * @{
 */

/**
 * @brief Gimabl commands process function list.
 */
static const T_PsdkProtCmdItem s_PayloadGimbalCmdList[] =
        {
                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_GIMBAL, PSDK_GIMBAL_CMD_ID_GET_GIMBAL_PARAM, GIMCMD(GetGimbalState)),
                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_GIMBAL, PSDK_GIMBAL_CMD_ID_SET_GIMBAL_MODE, GIMCMD(SetGimbalMode)),
                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_GIMBAL, PSDK_GIMBAL_CMD_ID_RETURN_HEAD, GIMCMD(ReturnHead)),
                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_GIMBAL, PSDK_GIMBAL_CMD_ID_CONTROL_SPEED, GIMCMD(ControlSpeed)),
                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_GIMBAL, PSDK_GIMBAL_CMD_ID_START_CALIBRATION, GIMCMD(StartCalibration)),
                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_GIMBAL, PSDK_GIMBAL_CMD_ID_SUPPORT_STATE, GIMCMD(SupportState)),
        };

/**
 * @}
 */

/* Exported functions --------------------------------------------------------*/

/** @defgroup Gimbal_Exported_Functions Exported Functions
 * @{
 */

/**
 * @brief Initialize PSDK gimbal commands handling.
 * @details Initialise gimbal command support state and mount gimbal command process functions
 *            and register gimbal command set callback functions.
 * @param psdkUpper Pointer to the top level PSDK structure.
 * @param gimbalHandler Pointer to gimbal command set callback function list.
 * @return PSDK function process state.
 */
E_PsdkStat PsdkGimbal_Init(T_PsdkUpper *psdkUpper, const T_PsdkGimbalHandler *gimbalHandler)
{
    T_PsdkProtCmdSetHandle cmdSetHandle;

    s_gimbalHandler = *gimbalHandler;

    cmdSetHandle.cmdSet = PSDK_CMDSET_GIMBAL;
    cmdSetHandle.cmdList = s_PayloadGimbalCmdList;
    cmdSetHandle.cmdCount = sizeof(s_PayloadGimbalCmdList) / sizeof(T_PsdkProtCmdItem);

    s_isSupportGimbal = 1;

    return PsdkProto_RegCmdSetHandler(&(psdkUpper->protHandle), &cmdSetHandle);
}

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/****************** (C) COPYRIGHT DJI Innovations *****END OF FILE****/
