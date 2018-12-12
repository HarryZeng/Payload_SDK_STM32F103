/**
 ******************************************************************************
 * @file    psdk_app_func.c
 * @version V1.0.0
 * @date    2017/11/10
 * @brief   This file provides the API functions for handling the transparent data
 * transmission between a mobile app (ground) and user's payload via PSDK port,
 * data display of the floating window on "DJI Pilot" app and widgets set & get.
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
#include "psdk_app_func.h"
#include <string.h>
#include <psdk_ack_code.h>
#include <psdk_cmdset_define/psdk_cmdset_app_func.h>

/** @addtogroup PSDK
 * @{
 */

/** @defgroup PSDK_App_Function PSDK App Function
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/** @defgroup A_Func_Private_Variables Private Variables
 * @{
 */

/** @defgroup A_Func_P_Variables_Callback_Related Callback Related
 * @{
 */

///Receive data from mobile APP callback function
static ReceiveFromAppFunc s_receiveFromAppFunc = NULL;
///Get widget value callback function
static GetWidgetValueFunc s_getWidgetValueFunc = NULL;
///Set widget value callback function
static SetWidgetValueFunc s_setWidgetValueFunc = NULL;

/**
 * @}
 */

/** @defgroup A_Func_P_Variables_Widget_Related Widget Related
 * @{
 */

///Pointer to widget item, including widget attribute
static const T_PsdkAppFuncWidgetListItem *s_widgetList = NULL;
///Total widget count
static uint8_t s_widgetItemCount = 0;

/**
 * @}
 */

/**
 * @}
 */

/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup A_Func_Private_Functions Private functions
 * @{
 */

/**
 * @brief Handle transparent data transmission from APP to load.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
static E_PsdkStat
AppFuncCmd_TT_AppToLoad(struct _PsdkProt *protHandle, const T_PsdkProtInfo *inProtInfo, const uint8_t *inProtData)
{
    if (s_receiveFromAppFunc != NULL) {
        s_receiveFromAppFunc(inProtData, inProtInfo->dataLen);
    }

    return PSDK_STAT_OK;
}

/**
 * @brief Handle Get Widget List Length Command.
 * @details Send widget list length to SKYPORT.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
static E_PsdkStat AppFuncCmd_GetWidgetListLength(struct _PsdkProt *protHandle, const T_PsdkProtInfo *inProtInfo,
                                                 const uint8_t *inProtData)
{
    T_PsdkAppFuncGetWidgetListLengthAck ack;

    ack.ackCode = PSDK_CMD_ACK_CODE_OK;
    if (s_widgetList != NULL) {
        ack.widgetListLength = s_widgetItemCount;
    } else {
        ack.widgetListLength = 0;
    }

    PsdkProto_SendAckData(protHandle, inProtInfo, (uint8_t *) &ack, sizeof(T_PsdkAppFuncGetWidgetListLengthAck));
    return PSDK_STAT_OK;
}

/**
 * @brief Handle Get Widget List Value Command.
 * @details Send specified widget attribute to SKYPORT.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
static E_PsdkStat AppFuncCmd_GetWidgetListValue(struct _PsdkProt *protHandle, const T_PsdkProtInfo *inProtInfo,
                                                const uint8_t *inProtData)
{
    T_PsdkAppFuncGetWidgetListValueReq *pReq = (T_PsdkAppFuncGetWidgetListValueReq *) inProtData;
    T_PsdkAppFuncGetWidgetListValueAck ack;
    uint8_t sub = pReq->widgetListSubscript;
    uint16_t ackLen;

    if (sub >= s_widgetItemCount || s_widgetList == NULL) {
        ack.ackCode = PSDK_CMD_ACK_CODE_ERROR;
        ackLen = 1;
        goto out;
    }

    ackLen = APPFUNC_MAX_WIDGET_NAME_SIZE + 3;

    ack.prop.widgetType = s_widgetList[sub].widgetType;
    ack.prop.widgetIndex = s_widgetList[sub].widgetIndex;
    memset(ack.prop.widgetName, 0x00, sizeof(ack.prop.widgetName));
    strncpy((char *) ack.prop.widgetName, s_widgetList[sub].widgetName, APPFUNC_MAX_WIDGET_NAME_SIZE - 1);

    if (ack.prop.widgetType == PSDK_APPFUNC_WIDGET_TYPE_LIST) {
        memset(ack.prop.widgetAttribute.listAttribute.listItemName, 0x00, sizeof(ack.prop.widgetAttribute.listAttribute.listItemName));
        ack.prop.widgetAttribute.listAttribute.listItemNum = s_widgetList[sub].widgetAttribute.listAttribute.listItemNum;

        for (int i = 0; i < ack.prop.widgetAttribute.listAttribute.listItemNum; i++) {
            strncpy((char *) ack.prop.widgetAttribute.listAttribute.listItemName[i], s_widgetList[sub].widgetAttribute.listAttribute.listItemName[i],
                    APPFUNC_LIST_MAX_ITEM_NAME_SIZE - 1);
        }

        ackLen += 1 + ack.prop.widgetAttribute.listAttribute.listItemNum * APPFUNC_LIST_MAX_ITEM_NAME_SIZE;
    } else if (ack.prop.widgetType == PSDK_APPFUNC_WIDGET_TYPE_INT_INPUT_BOX) {
        memset(ack.prop.widgetAttribute.intInputBoxAttribute.promptChar, 0x00, sizeof(ack.prop.widgetAttribute.intInputBoxAttribute.promptChar));
        strncpy((char *) ack.prop.widgetAttribute.intInputBoxAttribute.promptChar, s_widgetList[sub].widgetAttribute.intInputBoxAttribute.promptStr,
                APPFUNC_INT_INPUT_BOX_PROMPT_CHAR_MAX_SIZE - 1);

        ackLen += APPFUNC_INT_INPUT_BOX_PROMPT_CHAR_MAX_SIZE;
    }

    ack.ackCode = PSDK_CMD_ACK_CODE_OK;

    out:
    PsdkProto_SendAckData(protHandle, inProtInfo, (uint8_t *) &ack, ackLen);
    return PSDK_STAT_OK;
}

/**
 * @brief Handle Get Widget Group Count Command.
 * @details Send widget group count to SKYPORT.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
static E_PsdkStat AppFuncCmd_GetWidgetGroupCount(struct _PsdkProt *protHandle, const T_PsdkProtInfo *inProtInfo,
                                                 const uint8_t *inProtData)
{
    T_PsdkAppFuncGetWidgetGroupCountAck ack;

    ack.ackCode = PSDK_CMD_ACK_CODE_OK;
    if (s_widgetItemCount % APPFUNC_WIDGET_VALUE_GROUP_MAX_ITEM_COUNT == 0) {
        ack.groupCount = (uint8_t) (s_widgetItemCount / APPFUNC_WIDGET_VALUE_GROUP_MAX_ITEM_COUNT);
    } else {
        ack.groupCount = (uint8_t) (s_widgetItemCount / APPFUNC_WIDGET_VALUE_GROUP_MAX_ITEM_COUNT + 1);
    }

    PsdkProto_SendAckData(protHandle, inProtInfo, (uint8_t *) &ack, sizeof(T_PsdkAppFuncGetWidgetGroupCountAck));
    return PSDK_STAT_OK;
}

/**
 * @brief Handle Get Widget Group Value Command.
 * @details Send widget value of a widget group to SKYPORT.
 * @note Button widget value will be 0 all the time, because button widget value is meaningless when getting widget value.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
static E_PsdkStat AppFuncCmd_GetWidgetGroupValue(struct _PsdkProt *protHandle, const T_PsdkProtInfo *inProtInfo,
                                                 const uint8_t *inProtData)
{
    T_PsdkAppFuncGetWidgetGroupValueReq *pReq = (T_PsdkAppFuncGetWidgetGroupValueReq *) inProtData;
    T_PsdkAppFuncGetWidgetGroupValueAck ack;
    uint16_t ackLen;
    U_AppFuncWidgetValue widgetValue;

    uint8_t stIndex;
    uint8_t itemLen;

    stIndex = (uint8_t) (pReq->groupNum * APPFUNC_WIDGET_VALUE_GROUP_MAX_ITEM_COUNT);
    if (stIndex >= s_widgetItemCount) {
        ack.ackCode = PSDK_CMD_ACK_CODE_ERROR;
        ackLen = 1;
        goto out;
    }

    if ((s_widgetItemCount - stIndex) > APPFUNC_WIDGET_VALUE_GROUP_MAX_ITEM_COUNT) {
        itemLen = APPFUNC_WIDGET_VALUE_GROUP_MAX_ITEM_COUNT;
    } else {
        itemLen = s_widgetItemCount - stIndex;
    }

    ackLen = itemLen * sizeof(T_PsdkAppFuncWidgetValueItem) + 2;

    ack.widgetValueCount = itemLen;

    for (int i = 0; i < itemLen; i++) {
        if (s_widgetList[stIndex + i].widgetType == PSDK_APPFUNC_WIDGET_TYPE_BUTTON) {
            //button not need get value
            ack.widgetValue[i].widgetType = s_widgetList[stIndex + i].widgetType;
            ack.widgetValue[i].widgetIndex = s_widgetList[stIndex + i].widgetIndex;
            ack.widgetValue[i].widgetValue.data = 0;
            continue;
        }

        if (s_getWidgetValueFunc == NULL) {
            ack.widgetValue[i].widgetType = s_widgetList[stIndex + i].widgetType;
            ack.widgetValue[i].widgetIndex = s_widgetList[stIndex + i].widgetIndex;

            //warning
            PSDK_LOG_WARN("Can't get widget value, widget type = %d , widget index = %d", ack.widgetValue[i].widgetType,
                          ack.widgetValue[i].widgetIndex);
            ack.widgetValue[i].widgetValue.data = 0;
            continue;
        }

        if (s_getWidgetValueFunc(s_widgetList[stIndex + i].widgetType, s_widgetList[stIndex + i].widgetIndex,
                                 &widgetValue) == PSDK_STAT_OK) {
            ack.widgetValue[i].widgetType = s_widgetList[stIndex + i].widgetType;
            ack.widgetValue[i].widgetIndex = s_widgetList[stIndex + i].widgetIndex;
            ack.widgetValue[i].widgetValue = widgetValue;
        } else {
            ack.widgetValue[i].widgetType = s_widgetList[stIndex + i].widgetType;
            ack.widgetValue[i].widgetIndex = s_widgetList[stIndex + i].widgetIndex;

            //warning
            PSDK_LOG_WARN("Can't get widget value, widget type = %d , widget index = %d", ack.widgetValue[i].widgetType,
                          ack.widgetValue[i].widgetIndex);
            ack.widgetValue[i].widgetValue.data = 0;
        }
    }

    ack.ackCode = PSDK_CMD_ACK_CODE_OK;

    out:
    PsdkProto_SendAckData(protHandle, inProtInfo, (uint8_t *) &ack, ackLen);
    return PSDK_STAT_OK;
}

/**
 * @brief Handle Set Widget Value Command.
 * @details Determine whether the widget value meets requirements and write it to widget list.
 * @note Button widget value will not be written, but corresponding callback dunction will be called still.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
static E_PsdkStat AppFuncCmd_SetWidgetValue(struct _PsdkProt *protHandle, const T_PsdkProtInfo *inProtInfo,
                                            const uint8_t *inProtData)
{
    T_PsdkAppFuncSetWidgetValueReq *pReq = (T_PsdkAppFuncSetWidgetValueReq *) inProtData;
    T_PsdkAppFuncSetWidgetValueAck ack;

    if (s_setWidgetValueFunc != NULL) {
        if (s_setWidgetValueFunc((E_PsdkAppFuncWidgetType) pReq->widgetValue.widgetType, pReq->widgetValue.widgetIndex,
                                 &pReq->widgetValue.widgetValue) != PSDK_STAT_OK) {
            PSDK_LOG_WARN("Can't set widget value, widget type = %d , widget index = %d", pReq->widgetValue.widgetType,
                          pReq->widgetValue.widgetIndex);
            ack.ackCode = PSDK_CMD_ACK_CODE_ERROR;
        } else {
            ack.ackCode = PSDK_CMD_ACK_CODE_OK;
        }
    } else {
        ack.ackCode = PSDK_CMD_ACK_CODE_ERROR;
    }

    PsdkProto_SendAckData(protHandle, inProtInfo, (uint8_t *) &ack, sizeof(T_PsdkAppFuncSetWidgetValueAck));
    return PSDK_STAT_OK;
}

/**
 * @}
 */

/** @addtogroup A_Func_Private_Variables
 * @{
 */

/** @defgroup A_Func_P_Variables_Command_Related Command Related
 * @{
 */

/**
 * @brief App function commands process function list.
 */
static const T_PsdkProtCmdItem s_appFuncProtCmdList[] =
        {
                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_APP_FUNC, PSDK_APPFUNC_CMDID_TT_APP_TO_LOAD, AppFuncCmd_TT_AppToLoad),
                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_APP_FUNC, PSDK_APPFUNC_CMDID_GET_WIDGET_LIST_LENGTH, AppFuncCmd_GetWidgetListLength),
                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_APP_FUNC, PSDK_APPFUNC_CMDID_GET_WIDGET_LIST_VALUE, AppFuncCmd_GetWidgetListValue),
                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_APP_FUNC, PSDK_APPFUNC_CMDID_GET_WIDGET_GROUP_COUNT, AppFuncCmd_GetWidgetGroupCount),
                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_APP_FUNC, PSDK_APPFUNC_CMDID_GET_WIDGET_GROUP_VALUE, AppFuncCmd_GetWidgetGroupValue),
                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_APP_FUNC, PSDK_APPFUNC_CMDID_SET_WIDGET_VALUE, AppFuncCmd_SetWidgetValue),
        };

/**
 * @}
 */

/**
 * @}
 */

/* Exported functions --------------------------------------------------------*/

/** @defgroup A_Func_Exported_Functions Exported Functions
 * @{
 */

/**
 * @brief Initialize the PSDK mobile APP integration functionality.
 * @details Mount APP function command process functions.
 * @param psdkUpper Pointer to the top level PSDK structure.
 * @return PSDK function process state.
 */
E_PsdkStat PsdkAppFunc_Init(T_PsdkUpper *psdkUpper)
{
    T_PsdkProtCmdSetHandle cmdSetHandle;
    E_PsdkStat psdkStat;

    s_receiveFromAppFunc = NULL;
    s_widgetList = NULL;
    s_widgetItemCount = 0;
    s_getWidgetValueFunc = NULL;
    s_setWidgetValueFunc = NULL;

    cmdSetHandle.cmdSet = PSDK_CMDSET_APP_FUNC;
    cmdSetHandle.cmdList = s_appFuncProtCmdList;
    cmdSetHandle.cmdCount = sizeof(s_appFuncProtCmdList) / sizeof(T_PsdkProtCmdItem);

    psdkStat = PsdkProto_RegCmdSetHandler(&(psdkUpper->protHandle), &cmdSetHandle);
    if (psdkStat != PSDK_STAT_OK) {
        return psdkStat;
    }

    return PSDK_STAT_OK;
}

/**
 * @brief Transparently send data to mobile app.
 * @param psdkUpper pointer to the top level PSDK structure.
 * @param pSendData pointer to the data buffer to be sent.
 * @param needSendLen the length of the data to be sent.
 * @param pRealSendLen the length of the data that has been actually sent.
 * @return PSDK function process state.
 */
E_PsdkStat PsdkAppFunc_TransferToApp(T_PsdkUpper *psdkUpper, const uint8_t *pSendData, uint16_t needSendLen,
                                     uint16_t *pRealSendLen)
{
    T_PsdkProtInfo protInfo;
    uint16_t packCount;
    uint16_t lastPackLen;
    const uint8_t *pSendPtr;
    int i;

    lastPackLen = (uint16_t) (needSendLen % APPFUNC_LOAD_TO_APP_MAX_LEN);
    packCount = (uint16_t) (needSendLen / APPFUNC_LOAD_TO_APP_MAX_LEN);

    protInfo.packetType = PSDK_PROT_PACKET_TYPE_CMD;
    protInfo.ackReq = PSDK_PROT_ACK_REQ_NONEED;
    protInfo.encType = PSDK_PROT_ENC_AES;
    protInfo.cmdSet = PSDK_CMDSET_APP_FUNC;
    protInfo.cmdID = PSDK_APPFUNC_CMDID_TT_LOAD_TO_APP;

    pSendPtr = pSendData;

    //send pack
    protInfo.dataLen = APPFUNC_LOAD_TO_APP_MAX_LEN;
    for (i = 0; i < packCount; i++) {
        protInfo.seqNum = PsdkProt_GetCurrentSendSeq(&(psdkUpper->protHandle));
        if (PsdkProto_Send(&(psdkUpper->protHandle), &protInfo, pSendPtr) != PSDK_STAT_OK) {
            *pRealSendLen = (uint16_t) (pSendPtr - pSendData);
            return PSDK_STAT_ERR;
        }
        pSendPtr += APPFUNC_LOAD_TO_APP_MAX_LEN;
    }

    //send last pack
    if (lastPackLen != 0) {
        protInfo.dataLen = lastPackLen;
        protInfo.seqNum = PsdkProt_GetCurrentSendSeq(&(psdkUpper->protHandle));
        if (PsdkProto_Send(&(psdkUpper->protHandle), &protInfo, pSendPtr) != PSDK_STAT_OK) {
            *pRealSendLen = (uint16_t) (pSendPtr - pSendData);
            return PSDK_STAT_ERR;
        }
        pSendPtr += lastPackLen;
    }


    *pRealSendLen = (uint16_t) (pSendPtr - pSendData);
    return PSDK_STAT_OK;
}

/**
 * @brief Send a string to floating window in DJI pilot APP.
 * @param psdkUpper Pointer to the top level PSDK structure.
 * @param msg Pointer to the char buffer to be sent.
 * @return PSDK function process state.
 */
E_PsdkStat PsdkAppFunc_PushMsgToFloatingWindow(T_PsdkUpper *psdkUpper, const char *msg)
{
    T_PsdkProtInfo protInfo;

    if (strlen(msg) + 1 > APPFUNC_FLOAT_WINDOW_MSG_MAX_SIZE) {
        return PSDK_STAT_ERR_PARAM;
    }

    protInfo.packetType = PSDK_PROT_PACKET_TYPE_CMD;
    protInfo.ackReq = PSDK_PROT_ACK_REQ_NONEED;
    protInfo.encType = PSDK_PROT_ENC_AES;
    protInfo.cmdSet = PSDK_CMDSET_APP_FUNC;
    protInfo.cmdID = PSDK_APPFUNC_CMDID_PUSH_FLOATING_WINDOW_MSG;
    protInfo.dataLen = (uint16_t) (strlen(msg) + 1);

    protInfo.seqNum = PsdkProt_GetCurrentSendSeq(&(psdkUpper->protHandle));
    if (PsdkProto_Send(&(psdkUpper->protHandle), &protInfo, (const uint8_t *) msg) != PSDK_STAT_OK) {
        return PSDK_STAT_ERR;
    }

    return PSDK_STAT_OK;
}

/**
 * @brief Register the Widget List from user.
 * @param psdkUpper Pointer to the top-level PSDK structure.
 * @param widgetList Pointer to the widget list structure.
 * @param widgetItemCount Widget item count.
 * @return An enum that represents a status of PSDK.
 */
E_PsdkStat PsdkAppFunc_SetWidgetList(T_PsdkUpper *psdkUpper, const T_PsdkAppFuncWidgetListItem *widgetList,
                                     uint8_t widgetItemCount)
{
    s_widgetItemCount = widgetItemCount;
    s_widgetList = widgetList;

    return PSDK_STAT_OK;
}

/**
 * @brief Register the callback functions for receiving the transparent data from the mobile app.
 * @param psdkUpper  pointer to the top-level PSDK structure.
 * @param func the callback function to handle the received transparent data.
 * @return an enum that represents a status of PSDK.
 */
E_PsdkStat PsdkAppFunc_SetReceiveFromAppCallback(T_PsdkUpper *psdkUpper, ReceiveFromAppFunc func)
{
    s_receiveFromAppFunc = func;

    return PSDK_STAT_OK;
}

/**
 * @brief Register the callback function for receiving "Get Widget Value Group Data".
 * @note The Button widget does not need to get value.
 * @param psdkUpper  pointer to the top-level PSDK structure.
 * @param getWidgetValueFunc the callback function for receiving "Get Widget Value Group Data".
 * @return an enum that represents a status of PSDK.
 */
E_PsdkStat PsdkAppFunc_RegGetWidgetValueCallback(T_PsdkUpper *psdkUpper, GetWidgetValueFunc getWidgetValueFunc)
{
    s_getWidgetValueFunc = getWidgetValueFunc;

    return PSDK_STAT_OK;
}

/**
 * @brief Register the callback function for receiving "Set Widget value".
 * @param psdkUpper pointer to the top-level PSDK structure.
 * @param setWidgetValueFunc the callback function for receiving "Set Widget value".
 * @return an enum that represents a status of PSDK.
 */
E_PsdkStat PsdkAppFunc_RegSetWidgetValueCallback(T_PsdkUpper *psdkUpper, SetWidgetValueFunc setWidgetValueFunc)
{
    s_setWidgetValueFunc = setWidgetValueFunc;

    return PSDK_STAT_OK;
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

/************************ (C) COPYRIGHT DJI Innovations *******END OF FILE******/
