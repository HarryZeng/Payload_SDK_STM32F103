/**
 ******************************************************************************
 * @file    psdk_msg_subcribe.c
 * @version V1.0.0
 * @date    2017/11/10
 * @brief   This file provides the API functions for receiving the push data from
 * PSDK port.
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
#include "psdk_msg_subcribe.h"
#include <string.h>

/** @addtogroup PSDK
 * @{
 */

/** @defgroup PSDK_Message_Push PSDK Message Push
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/** @defgroup M_Push_Private_Variables Private Variables
 * @{
 */

/** @defgroup M_Push_P_Variables_Callback_Related Callback Related
 * @{
 */

///callback function list
static T_PsdkPushDataMsgCallbackList s_PushDataMsgCallbackList = {0};

/**
 * @}
 */

/**
 * @}
 */

/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup M_Push_Private_Functions Private functions
 * @{
 */

/**
 * @brief Receive image transmission bandwidth data.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
static E_PsdkStat
MsgPushCmd_PushBandWidth(struct _PsdkProt *protHandle, const T_PsdkProtInfo *inProtInfo, const uint8_t *inProtData)
{
    if (s_PushDataMsgCallbackList.bandWidthMsgCallback != NULL) {
        s_PushDataMsgCallbackList.bandWidthMsgCallback((const T_BandWidthMsg *) inProtData);
    }
    return PSDK_STAT_OK;
}

/**
 * @brief Receive UAV attitude data.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
static E_PsdkStat MsgPushCmd_PushAttitude(struct _PsdkProt *protHandle, const T_PsdkProtInfo *inProtInfo,
                                          const uint8_t *inProtData)
{
    if (s_PushDataMsgCallbackList.uavAttitudeMsgCallback != NULL) {
        s_PushDataMsgCallbackList.uavAttitudeMsgCallback((const T_UavAttitudeMsg *) inProtData);
    }
    return PSDK_STAT_OK;
}

/**
 * @brief Receive battery information.
 * @note When battery power is normal, the ack is to be ignored.
          Please refer to ::T_BatteryInfoAck for details.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
static E_PsdkStat MsgPushCmd_PushBatteryInfo(struct _PsdkProt *protHandle, const T_PsdkProtInfo *inProtInfo,
                                             const uint8_t *inProtData)
{
    T_BatteryInfoAck batteryInfoAck;

    if (s_PushDataMsgCallbackList.batteryInfoMsgCallback != NULL) {
        s_PushDataMsgCallbackList.batteryInfoMsgCallback((const T_BatteryInfoMsg *) inProtData, &batteryInfoAck);
    }

    PsdkProto_SendAckData(protHandle, inProtInfo, (uint8_t *)&batteryInfoAck, sizeof(T_BatteryInfoAck));
    return PSDK_STAT_OK;
}

/**
 * @brief Receive GPS information.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
static E_PsdkStat MsgPushCmd_PushGpsInfo(struct _PsdkProt *protHandle, const T_PsdkProtInfo *inProtInfo,
                                         const uint8_t *inProtData)
{
    if (s_PushDataMsgCallbackList.gpsInfoMsgCallback != NULL) {
        s_PushDataMsgCallbackList.gpsInfoMsgCallback((const T_GPSInfoMsg *) inProtData);
    }
    return PSDK_STAT_OK;
}

/**
 * @brief Receive UAV state data.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
static E_PsdkStat MsgPushCmd_PushUavState(struct _PsdkProt *protHandle, const T_PsdkProtInfo *inProtInfo,
                                          const uint8_t *inProtData)
{
    if (s_PushDataMsgCallbackList.uavStateMsgCallback != NULL) {
        s_PushDataMsgCallbackList.uavStateMsgCallback((const T_UavStateMsg *) inProtData);
    }
    return PSDK_STAT_OK;
}

/**
 * @brief Receive APP date and time data.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
static E_PsdkStat MsgPushCmd_PushAppDateTime(struct _PsdkProt *protHandle, const T_PsdkProtInfo *inProtInfo,
                                             const uint8_t *inProtData)
{
    if (s_PushDataMsgCallbackList.appDateTimeMsgCallback != NULL) {
        s_PushDataMsgCallbackList.appDateTimeMsgCallback((const T_AppDateTimeMsg *) inProtData);
    }
    return PSDK_STAT_OK;
}

/**
 * @brief Receive baro height data.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
static E_PsdkStat MsgPushCmd_PushBaroHeight(struct _PsdkProt *protHandle, const T_PsdkProtInfo *inProtInfo,
                                            const uint8_t *inProtData)
{
    if (s_PushDataMsgCallbackList.baroHeightDataMsgCallback != NULL) {
        s_PushDataMsgCallbackList.baroHeightDataMsgCallback((const T_baroHeightDataMsg *) inProtData);
    }
    return PSDK_STAT_OK;
}

/**
 * @brief Receive GPS raw data.
 * @note If there is no GPS signal, the GPS data will not be changed so it will remains the same as
 *        the last time there is GPS signal.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
static E_PsdkStat MsgPushCmd_GpsRawData(struct _PsdkProt *protHandle, const T_PsdkProtInfo *inProtInfo,
                                        const uint8_t *inProtData)
{
    if (s_PushDataMsgCallbackList.gpsRawDataMsgCallback != NULL) {
        s_PushDataMsgCallbackList.gpsRawDataMsgCallback((const T_GpsRawDataMsg *) inProtData);
    }
    return PSDK_STAT_OK;
}

/**
 * @brief Receive RTK raw data.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
static E_PsdkStat MsgPushCmd_RtkRawData(struct _PsdkProt *protHandle, const T_PsdkProtInfo *inProtInfo,
                                        const uint8_t *inProtData)
{
    if (s_PushDataMsgCallbackList.rtkRawDataMsgCallback != NULL) {
        s_PushDataMsgCallbackList.rtkRawDataMsgCallback((const T_RtkRawDataMsg *) inProtData);
    }
    return PSDK_STAT_OK;
}
/**
 * @}
 */

/** @addtogroup M_Push_Private_Variables
 * @{
 */

/** @defgroup P_Variables_Command_Related Command Related
 * @{
 */

/**
 * @brief Data push commands process function list.
 */
static const T_PsdkProtCmdItem s_PushDataMsgSubProtCmdList[] =
        {
                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_DATA_PUSH, PSDK_DATAPUSH_CMD_ID_PUSH_BANDWIDTH, MsgPushCmd_PushBandWidth),
                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_DATA_PUSH, PSDK_DATAPUSH_CMD_ID_PUSH_ATTITUDE, MsgPushCmd_PushAttitude),
                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_DATA_PUSH, PSDK_DATAPUSH_CMD_ID_PUSH_BATTERY_INFO, MsgPushCmd_PushBatteryInfo),
                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_DATA_PUSH, PSDK_DATAPUSH_CMD_ID_PUSH_GPS_INFO, MsgPushCmd_PushGpsInfo),
                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_DATA_PUSH, PSDK_DATAPUSH_CMD_ID_PUSH_UAV_STATE, MsgPushCmd_PushUavState),
                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_DATA_PUSH, PSDK_DATAPUSH_CMD_ID_PUSH_APP_DATETIME, MsgPushCmd_PushAppDateTime),
                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_DATA_PUSH, PSDK_DATAPUSH_CMD_ID_PUSH_BARO_HEIGHT_DATA, MsgPushCmd_PushBaroHeight),
                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_DATA_PUSH, PSDK_DATAPUSH_CMD_ID_PUSH_GPS_RAW_DATA, MsgPushCmd_GpsRawData),
                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_DATA_PUSH, PSDK_DATAPUSH_CMD_ID_PUSH_RTK_RAW_DATA, MsgPushCmd_RtkRawData),
        };

/**
 * @}
 */

/**
 * @}
 */

/* Exported functions --------------------------------------------------------*/

/** @defgroup M_Push_Exported_Functions Exported Functions
 * @{
 */

/**
 * @brief Initialize the PSDK data push functionality.
 * @details Mount data push command process functions.
 * @param psdkUpper Pointer to the top level PSDK structure.
 * @return PSDK function process state.
 */
E_PsdkStat PsdkMsgSub_Init(T_PsdkUpper *psdkUpper)
{
    T_PsdkProtCmdSetHandle cmdSetHandle;

    memset(&s_PushDataMsgCallbackList, 0x00, sizeof(s_PushDataMsgCallbackList));
    cmdSetHandle.cmdSet = PSDK_CMDSET_DATA_PUSH;
    cmdSetHandle.cmdList = s_PushDataMsgSubProtCmdList;
    cmdSetHandle.cmdCount = sizeof(s_PushDataMsgSubProtCmdList) / sizeof(T_PsdkProtCmdItem);

    return PsdkProto_RegCmdSetHandler(&(psdkUpper->protHandle), &cmdSetHandle);
}

/**
 * @brief Register the callback function list for push data by the user.
 * @param psdkUpper Pointer to the top-level PSDK structure.
 * @param PushDataMsgCallbackList Pointer to callback functions list.
 * @return PSDK function process state.
 */
E_PsdkStat PsdkMsgSub_RegMsgCallbackList(T_PsdkUpper *psdkUpper, const T_PsdkPushDataMsgCallbackList *PushDataMsgCallbackList)
{
    memcpy(&s_PushDataMsgCallbackList, PushDataMsgCallbackList, sizeof(T_PsdkPushDataMsgCallbackList));

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
