/**
 ******************************************************************************
 * @file    test_msg_push.c
 * @version V1.3.0
 * @date    2018/09/19
 * @brief   The file define PSDK message push command callback functions for demo board.
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
#include <psdk.h>
#include <psdk_cmdset_define/psdk_cmdset_msg_push.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/**
 * @brief PSDK image link bandwidth message push command callback function.
 * @param bandWidthMsg Image bandwidth message structure.
 * @return None.
 */
static void bandWidthMsgCallback(const T_BandWidthMsg *bandWidthMsg)
{
//    PSDK_LOG_DEBUG("Receive bandwidth message");
}

/**
 * @brief PSDK UAV attitude message push command callback function.
 * @param uavAttitudeMsg UAV attitude message structure.
 * @return None.
 */
static void uavAttitudeMsgCallback(const T_UavAttitudeMsg *uavAttitudeMsg)
{
//    PSDK_LOG_DEBUG("Receive Uav AttitudeMsg");
}

/**
 * @brief PSDK battery information push command callback function.
 * @param batteryInfoMsg UAV battery information structure.
 * @param batteryInfoAck Battery information push command ack structure, specifies payload power-off ready state.
 * @return None.
 */
static void batteryInfoMsgCallback(const T_BatteryInfoMsg *batteryInfoMsg, T_BatteryInfoAck *batteryInfoAck)
{
//    PSDK_LOG_DEBUG("Receive Battery Info Msg");

    /*
     * Users can add power off preparation work here, but if execution time of this part is too long,
     * please put it to anther task.
     */
    batteryInfoAck->ackCode = PSDK_CMD_ACK_CODE_OK;
    batteryInfoAck->powerOffReady = PSDK_PAYLOAD_POWER_OFF_READY;
}

/**
 * @brief PSDK GPS information push command callback function.
 * @param gpsInfoMsg GPS information structure.
 * @return None.
 */
static void gpsInfoMsgCallback(const T_GPSInfoMsg *gpsInfoMsg)
{
//    PSDK_LOG_DEBUG("Receive gps info msg");
}

/**
 * @brief PSDK UAV state message push command callback function.
 * @param uavStateMsg UAV state message structure.
 * @return None.
 */
static void uavStateMsgCallback(const T_UavStateMsg *uavStateMsg)
{
//    PSDK_LOG_DEBUG("Receive Uav state Msg");
}

/**
 * @brief PSDK mobile APP date and time message push command callback function.
 * @param appDateTimeMsg Mobile APP date and time message structure.
 * @return None.
 */
static void appDateTimeMsgCallback(const T_AppDateTimeMsg *appDateTimeMsg)
{
//    PSDK_LOG_DEBUG("Receive AppdateTime Msg");
}

/**
 * @brief PSDK barometer height data message push command callback function.
 * @param baroHeightDataMsg Barometer height data message structure.
 * @return None.
 */
static void baroHeightDataMsgCallback(const T_baroHeightDataMsg *baroHeightDataMsg)
{
//    PSDK_LOG_DEBUG("Receive BaroHeight Msg");
}

/**
 * @brief PSDK GPS raw data push command callback function.
 * @param gpsRawDataMsg GPS raw data structure.
 * @return None.
 */
static void gpsRawDataMsgCallback(const T_GpsRawDataMsg *gpsRawDataMsg)
{
//    PSDK_LOG_DEBUG("Receive GpsRawData Msg");
}

/**
 * @brief PSDK RTK raw data push command callback function.
 * @param rtkRawDataMsg RTK raw data structure.
 * @return None.
 */
static void rtkRawDataMsgCallback(const T_RtkRawDataMsg *rtkRawDataMsg)
{
//    PSDK_LOG_DEBUG("Receive RtkRawData Msg");
}

//message subscribe function list
const T_PsdkPushDataMsgCallbackList g_PushDataMsgCallbackList = {
        .bandWidthMsgCallback = bandWidthMsgCallback,
        .uavAttitudeMsgCallback = uavAttitudeMsgCallback,
        .batteryInfoMsgCallback = batteryInfoMsgCallback,
        .gpsInfoMsgCallback = gpsInfoMsgCallback,
        .uavStateMsgCallback = uavStateMsgCallback,
        .appDateTimeMsgCallback = appDateTimeMsgCallback,
        .baroHeightDataMsgCallback = baroHeightDataMsgCallback,
        .gpsRawDataMsgCallback = gpsRawDataMsgCallback,
        .rtkRawDataMsgCallback = rtkRawDataMsgCallback,
};

/****************** (C) COPYRIGHT DJI Innovations *****END OF FILE****/
