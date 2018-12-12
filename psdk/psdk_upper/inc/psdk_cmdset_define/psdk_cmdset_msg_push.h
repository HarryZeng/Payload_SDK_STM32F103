/**
 ******************************************************************************
 * @file    psdk_cmdset_msg_push.h
 * @version V1.0.0
 * @date    2017/08/10
 * @brief   This file defines the message push command set.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef PSDK_CMDSET_MSG_PUSH_H
#define PSDK_CMDSET_MSG_PUSH_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <psdk_typedef.h>

/** @addtogroup PSDK
 * @{
 */

/** @addtogroup PSDK_Message_Push
 * @{
 */

/* Exported constants --------------------------------------------------------*/

/** @defgroup M_Push_Exported_Constants Exported Constants
 * @{
 */

/** @defgroup E_Constants_Psdk_UAV_Type Psdk UAV Type
 * @{
 */

#define PSDK_UAV_TYPE_UNKNOWN     0 /*!< Specifies unknown UAV type. */
#define PSDK_UAV_TYPE_M200        1 /*!< Specifies M200 UAV. */
#define PSDK_UAV_TYPE_M210        2 /*!< Specifies M210 UAV. */
#define PSDK_UAV_TYPE_M210RTK     3 /*!< Specifies M210 RTK UAV. */
#define PSDK_UAV_TYPE_M600        4 /*!< Specifies M600 UAV. */
#define PSDK_UAV_TYPE_M600PRO     5 /*!< Specifies M600 PRO UAV. */

/**
 * @}
 */

/** @defgroup E_Constants_Psdk_BaseBandState Psdk BaseBandState
 * @{
 */

#define PSDK_BASE_BAND_STATE_LINK         1 /*!< Specifies base band state is normal. */
#define PSDK_BASE_BAND_STATE_UNLINK       0 /*!< Specifies base band state is abnormal. */

/**
 * @}
 */

/** @defgroup E_Constants_Psdk_BatteryPowerState Psdk BatteryPowerState
 * @{
 */

#define PSDK_BATTERY_POWER_ON              0    /*!< Specifies battery power is normal. */
#define PSDK_BATTERY_POWER_OFF             1    /*!< Specifies battery is to be power off. */

/**
 * @}
 */

/** @defgroup E_Constants_Psdk_PayloadPowerOffReadyState Psdk PayloadPowerOffReadyState
 * @{
 */

#define PSDK_PAYLOAD_POWER_OFF_NOT_READY 0    /*!< Specifies payload is not ready for power off. */
#define PSDK_PAYLOAD_POWER_OFF_READY      1    /*!< Specifies payload is ready for power off. */

/**
 * @}
 */

/** @defgroup E_Constants_Psdk_MsgPushLinkState Psdk MsgPushLinkState
 * @{
 */

#define PSDK_MSG_PUSH_LINK_STATE_LINK         1 /*!< Specifies link state is normal. */
#define PSDK_MSG_PUSH_LINK_STATE_UNLINK       0 /*!< Specifies link state is abnormal. */

/**
 * @}
 */

/** @defgroup E_Constants_Psdk_AppConnectionState Psdk AppConnectionState
 * @{
 */

#define PSDK_APP_CONNECTION_STATE_LINK        1 /*!< Specifies app link state is normal. */
#define PSDK_APP_CONNECTION_STATE_UNLINK      0 /*!< Specifies app link state is abnormal. */

/**
 * @}
 */

/** @defgroup E_Constants_Psdk_GPS_State Psdk GPS State
 * @{
 */

#define PSDK_GPS_STATE_NO_SIGNAL          0 /*!< Specifies GPS has no signal at all. */
#define PSDK_GPS_STATE_WEAK_SIGNAL        1 /*!< Specifies GPS signal is very weak. */
#define PSDK_GPS_STATE_MEDIUM_SIGNAL      2 /*!< Specifies GPS signal is in medium strength. */
#define PSDK_GPS_STATE_GOOD_SIGNAL        3 /*!< Specifies GPS signal is very strong. */

/**
 * @}
 */

/** @defgroup E_Constants_Psdk_Compass_State Psdk Compass State
 * @{
 */

#define PSDK_COMPASS_STATE_NORMAL         0 /*!< Specifies compass state is normal. */
#define PSDK_COMPASS_STATE_ABNORMAL       1 /*!< Specifies compass state is abnormal. */

/**
 * @}
 */

/** @defgroup E_Constants_Psdk_Motor_State Psdk Motor State
 * @{
 */

#define PSDK_MOTOR_STATE_ROTATING         1 /*!< Specifies motor is rotating. */
#define PSDK_MOTOR_STATE_UNROTATING       0 /*!< Specifies motor is not rotating. */

/**
 * @}
 */

/** @defgroup E_Constants_Psdk_Land_State Psdk Land State
 * @{
 */

#define PSDK_LAND_STATE_UNKNOWN           0 /*!< Specifies UAV land state is unknown. */
#define PSDK_LAND_STATE_LANDED            1 /*!< Specifies UAV has landed. */
#define PSDK_LAND_STATE_UNLANDED          2 /*!< Specifies UAV is in the sky. */

/**
 * @}
 */

/**
 * @}
 */

/* Exported macros -----------------------------------------------------------*/

/** @defgroup M_Push_Exported_Macros Exported Macros
 * @{
 */

/** @defgroup E_Macros_Psdk_UAV_Type Psdk UAV Type
 * @{
 */

///Judge whether input value is UAV type.
#define IS_PSDK_UAV_TYPE(UAV_TYPE) (((UAV_TYPE) == PSDK_UAV_TYPE_UNKNOWN)   || \
                                        ((UAV_TYPE) == PSDK_UAV_TYPE_M200)      || \
                                        ((UAV_TYPE) == PSDK_UAV_TYPE_M210)      || \
                                        ((UAV_TYPE) == PSDK_UAV_TYPE_M210RTK)   || \
                                        ((UAV_TYPE) == PSDK_UAV_TYPE_M600)      || \
                                        ((UAV_TYPE) == PSDK_UAV_TYPE_M600PRO))

/**
 * @}
 */

/** @defgroup E_Macros_Psdk_BaseBandState Psdk BaseBandState
 * @{
 */

///Judge whether input value is base band state.
#define IS_PSDK_BASE_BAND_STATE(STATE) (((STATE) == PSDK_BASE_BAND_STATE_LINK)  || \
                                            ((STATE) == PSDK_BASE_BAND_STATE_UNLINK))

/**
 * @}
 */

/** @defgroup E_Macros_Psdk_BatteryPowerState Psdk BatteryPowerState
 * @{
 */

///Judge whether input value is battery power state.
#define IS_PSDK_BATTERY_POWER_STATE(STATE) (((STATE) == PSDK_BATTERY_POWER_ON)  || \
                                                 ((STATE) == PSDK_BATTERY_POWER_OFF))

/**
 * @}
 */

/** @defgroup E_Macros_Psdk_PayloadPowerOffReadyState Psdk PayloadPowerOffReadyState
 * @{
 */

///Judge whether input value is payload power off ready state.
#define IS_PSDK_PAYLOAD_POWER_OFF_READY_STATE(STATE) (((STATE) == PSDK_PAYLOAD_POWER_OFF_NOT_READY)  || \
                                                            ((STATE) == PSDK_PAYLOAD_POWER_OFF_READY))

/**
 * @}
 */

/** @defgroup E_Macros_Psdk_MsgPushLinkState Psdk MsgPushLinkState
 * @{
 */

///Judge whether input value is link state.
#define IS_PSDK_MSGPUSH_LINK_STATE(STATE) (((STATE) == PSDK_MSG_PUSH_LINK_STATE_LINK)  || \
                                          ((STATE) == PSDK_MSG_PUSH_LINK_STATE_UNLINK))

/**
 * @}
 */

/** @defgroup E_Macros_Psdk_AppConnectionState Psdk AppConnectionState
 * @{
 */

///Judge whether input value is app connection state.
#define IS_PSDK_APP_CONNECTION_STATE(STATE) (((STATE) == PSDK_APP_CONNECTION_STATE_LINK)  || \
                                                  ((STATE) == PSDK_APP_CONNECTION_STATE_UNLINK))

/**
 * @}
 */

/** @defgroup E_Macros_Psdk_GPS_State Psdk GPS State
 * @{
 */

///Judge whether input value is GPS signal state.
#define IS_PSDK_GPS_STATE(STATE) (((STATE) == PSDK_GPS_STATE_NO_SIGNAL)     || \
                                     ((STATE) == PSDK_GPS_STATE_WEAK_SIGNAL)   || \
                                     ((STATE) == PSDK_GPS_STATE_MEDIUM_SIGNAL) || \
                                     ((STATE) == PSDK_GPS_STATE_GOOD_SIGNAL)

/**
 * @}
 */

/** @defgroup E_Macros_Psdk_Compass_State Psdk Compass State
 * @{
 */

///Judge whether input value is compass state.
#define IS_PSDK_COMPASS_STATE(STATE) (((STATE) == PSDK_COMPASS_STATE_NORMAL)    || \
                                          ((STATE) == PSDK_COMPASS_STATE_ABNORMAL))

/**
 * @}
 */

/** @defgroup E_Macros_Psdk_Motor_State Psdk Motor State
 * @{
 */

///Judge whether input value is motor rotating state.
#define IS_PSDK_MOTOR_STATE(STATE) (((STATE) == PSDK_MOTOR_STATE_ROTATING)  || \
                                       ((STATE) == PSDK_MOTOR_STATE_UNROTATING))

/**
 * @}
 */

/** @defgroup E_Macros_Psdk_Land_State Psdk Land State
 * @{
 */

///Judge whether input value is UAV land state.
#define IS_PSDK_LAND_STATE(STATE) (((STATE) == PSDK_LAND_STATE_UNKNOWN)     || \
                                      ((STATE) == PSDK_LAND_STATE_LANDED)      || \
                                      ((STATE) == PSDK_LAND_STATE_UNLANDED))

/**
 * @}
 */

/**
 * @}
 */

/* Exported types ------------------------------------------------------------*/

/** @defgroup M_Push_Exported_Types Exported Types
 * @{
 */

/** @defgroup M_Push_Command_Related Command Related
 * @{
 */

/**
 * @brief Data Push Command ID
 */
typedef enum {
    PSDK_DATAPUSH_CMD_ID_PUSH_BANDWIDTH = 0x01,         /*!< image transmission bandwidth push command */
    PSDK_DATAPUSH_CMD_ID_PUSH_ATTITUDE = 0x02,          /*!< UAV attitude push command */
    PSDK_DATAPUSH_CMD_ID_PUSH_BATTERY_INFO = 0x03,      /*!< battery information push command */
    PSDK_DATAPUSH_CMD_ID_PUSH_GPS_INFO = 0x04,          /*!< GPS data push command */
    PSDK_DATAPUSH_CMD_ID_PUSH_UAV_STATE = 0x05,         /*!< UAV state push command */
    PSDK_DATAPUSH_CMD_ID_PUSH_APP_DATETIME = 0x06,      /*!< APP time and date push command */
    PSDK_DATAPUSH_CMD_ID_PUSH_BARO_HEIGHT_DATA = 0x07,  /*!< baro pressure altitude push command */
    PSDK_DATAPUSH_CMD_ID_PUSH_GPS_RAW_DATA = 0x08,      /*!< GPS raw data push command */
    PSDK_DATAPUSH_CMD_ID_PUSH_RTK_RAW_DATA = 0x09,      /*!< RTK raw data push command */
} E_PsdkDataPushCmd;

#pragma pack(1)

// PSDK_DATAPUSH_CMD_ID_PUSH_BANDWIDTH
/**
 * @brief The structure defining Image Transmission Bandwidth Push contents.
 */
typedef struct {
    uint8_t baseBandState;               /*!< Specifies the base band state of wireless image transmission.
                                              This parameter can be any value of @ref Psdk_BaseBandState. */
    uint8_t maxBandWidth;                /*!< Specifies image transmission max bandwidth, unit: Mbps. */
    uint8_t reserve;

    uint8_t remoteControlLinkState :1;   /*!< Specifies remote control connection state.
                                              This parameter can be any value of @ref Psdk_MsgPushLinkState. */
    uint8_t downVideoLinkState :1;       /*!< Specifies downlink image transmission link connection state.
                                              This parameter can be any value of @ref Psdk_MsgPushLinkState. */
    uint8_t downDataCmdLinkState :1;     /*!< Specifies downlink data transmission link connection state.
                                              This parameter can be any value of @ref Psdk_MsgPushLinkState. */
    uint8_t AppLinkState :1;             /*!< Specifies APP connection state.
                                              This parameter can be any value of @ref Psdk_AppConnectionState. */
    uint8_t linkStateReserveBit :4;

    uint32_t maxUpComPortBandWidth;      /*!< Specifies uplink max bandwidth, unit: Byte/s. */
    uint32_t maxDownComPortBandWidth;    /*!< Specifies downlink max bandwidth, unit: Bytes/s. */
    uint32_t maxDownNetPortBandWidth;    /*!< Specifies net port max bandwidth, unit:Kb/s.
                                              @note Net port bandwidth includes video stream bandwidth and data stream bandwidth. */

    uint8_t isUpComPortOverrun : 1;      /*!< Specifies uplink busy state.
                                              This value will be set to 1 when uplink bandwidth is beyond T_BandWidthMsg::maxUpComPortBandWidth. */
    uint8_t isDownComPortOverrun : 1;    /*!< Specifies downlink busy state.
                                              This value will be set to 1 when downlink bandwidth is beyond T_BandWidthMsg::maxDownComPortBandWidth. */
    uint8_t isDownNetPortOverrun : 1;    /*!< Specifies net port link busy state.
                                              This value will be set to 1 when net port data bandwidth is beyond T_BandWidthMsg::maxDownNetPortBandWidth. */
    uint8_t overrunReserveBit : 5;

    uint32_t upComPortBandWidth;         /*!< Specifies uplink realtime bandwidth, unit:Byte/s. */
    uint32_t downComPortBandWidth;       /*!< Specifies downlink realtime bandwidth, unit:Bytes/s. */
    uint32_t downVideoStreamBandWidth;   /*!< Specifies net port video stream realtime bandwidth, unit:Kbps. */
    uint32_t downDataStreamBandWidth;    /*!< Specifies net port data stream realtime bandwidth, unit:Kbps. */
} T_BandWidthMsg;

// PSDK_DATAPUSH_CMD_ID_PUSH_ATTITUDE
/**
 * @brief The structure defining UAV Attitude Push contents.
 */
typedef struct {
    //q = q0 + q1*i + q2*j + q3*k
    psdk_f32_t q0;
    psdk_f32_t q1;
    psdk_f32_t q2;
    psdk_f32_t q3;
} T_UavAttitudeMsg;

// PSDK_DATAPUSH_CMD_ID_PUSH_BATTERY_INFO
/**
 * @brief The structure defining Battery Information Push contents.
 */
typedef struct {
    uint8_t capacityPercent;    /*!< Specifies percentage of battery power, between 0 and 100. */
    uint8_t powerOffNotice;     /*!< Specifies battery power-off state,
                                     This parameter can be any value of @ref Psdk_BatteryPowerState,
                                     and please refer to @ref Psdk_BatteryPowerState for details. */
} T_BatteryInfoMsg;

/**
 * @brief The structure defining ack of Battery Information Push Command.
 * @note When battery power is normal, the ack is to be ignored.
 */
typedef struct {
    uint8_t ackCode;            /*!< Specifies PSDK command ack code.
                                     This parameter can be any value of ::E_PsdkCmdAckCode */
    uint8_t powerOffReady;      /*!< Specifies payload power-off ready state,
                                     This parameter can be any value of @ref Psdk_PayloadPowerOffReadyState,
                                     and please refer to @ref Psdk_PayloadPowerOffReadyState for details. */
} T_BatteryInfoAck;

// PSDK_DATAPUSH_CMD_ID_PUSH_GPS_INFO
/**
 * @brief The structure defining GPS Information Push contents.
 */
typedef struct {
    psdk_f64_t longitude;       /*!< GPS longitude, unit: rad. */
    psdk_f64_t latitude;        /*!< GPS latitude, unit: rad. */
    int16_t refHeight;          /*!< Relative takeoff height, unit: 0.1m. */
    uint8_t sateNum;            /*!< Specifies number of satellites. */
    uint8_t gpsState;           /*!< This parameter can be any value of @ref Psdk_GPS_State,
                                     Please refer to @ref Psdk_GPS_State for details. */
} T_GPSInfoMsg;

// PSDK_DATAPUSH_CMD_ID_PUSH_BARO_HEIGHT_INFO
/**
 * @brief The structure defining Baro Height Data Push contents.
 */
typedef struct {
    psdk_f32_t baroHeight;          /*!< The absolute height measured by barometer, unit: m. */
} T_baroHeightDataMsg;

// PSDK_DATAPUSH_CMD_ID_PUSH_GPS_RAW_DATA_INFO
/**
 * @brief The structure defining GPS Raw Data Push contents.
 */
typedef struct {
    uint32_t date;                 /*!< Specifies a integer indicating a GMT+8 date, format: yyyymmdd
                                        (E.g. 20150205 = February 5th, 2015). */
    uint32_t time;                 /*!< Specifies a integer indicating a GMT+8 time in a 24-hour clock,
                                        format: hhmmss (E.g. 90209 = 09:02:09). */
    int32_t posLongitude;          /*!< Specifies the longitude measured by GPS, unit: E-7 deg. */
    int32_t posLatitude;           /*!< Specifies the latitude measured by GPS, unit: E-7 deg. */
    int32_t posHeight;             /*!< Specifies the height above sea level measured by GPS, unit: mm. */
    psdk_f32_t velocityNorth;      /*!< Specifies the velocity to the North measured by GPS, unit: cm/s. */
    psdk_f32_t velocityEast;       /*!< Specifies the velocity to the East measured by GPS, unit: cm/s. */
    psdk_f32_t velocityDownward;   /*!< Specifies the downward velocity measured by GPS, unit: cm/s. */
    psdk_f32_t hdop;               /*!< Specifies horizontal dilution of precision,
                                        <1:ideal, 1-2:excellent, 2-5:good, 5-10:moderate, 10-20 fair, >20:poor. */
    psdk_f32_t pdop;               /*!< Specifies position dilution of precision,
                                        <1:ideal, 1-2:excellent, 2-5:good, 5-10:moderate, 10-20 fair, >20:poor. */
    psdk_f32_t gpsFixState;        /*!< Specifies the state of GPS fix, three indicating 3D data. */
    psdk_f32_t vacc;               /*!< Specifies vertical position accuracy; the smaller, the better. */
    psdk_f32_t hacc;               /*!< Specifies horizontal position accuracy; the smaller, the better.
                                        The value indicates the possible error of the measured position, unit: mm. */
    psdk_f32_t sacc;               /*!< Specifies the speed accuracy; the smaller, the better, unit: cm/s. */
    uint32_t gpsUsed;              /*!< Specifies the number of GPS satellites used for position fix. */
    uint32_t glonassUsed;          /*!< Specifies the number of GLONASS satellites used for position fix. */
    uint16_t totalNumUsed;         /*!< Specifies the total number of satellites used for position fix. */
    uint16_t gpsState;             /*!< Specifies the times of sending GPS data. When the counter > 65535,
                                        it will turn 0 and continue increase every time GPS data is sent. */
} T_GpsRawDataMsg;

/**
 * @brief The structure defining RTK Raw Data Push contents.
 */
typedef struct {
    psdk_f64_t lon_p;   /*!< Specifies the longitude measured by RTK, unit: deg */
    psdk_f64_t lat_p;   /*!< Specifies the latitude measured by RTK, unit: deg */
    psdk_f32_t hmsl_p;  /*!< Specifies the height above sea level measured by RTK, unit: m */
    psdk_f32_t vel_N;   /*!< Specifies the velocity to the North measured by RTK, unit: cm/s */
    psdk_f32_t vel_E;   /*!< Specifies the velocity to the East measured by RTK, unit: cm/s */
    psdk_f32_t vel_D;   /*!< Specifies the downward velocity measured by RTK, unit: cm/s */
    int16_t yaw;        /*!< Specifies the azimuth measured by RTK */
    uint8_t pos_health; /*!< Specifies the type of RTK positioning, indicating different solutions for calculating the position.
                             <1:ideal, 1-2:excellent, 2-5:good, 5-10:moderate, 10-20 fair, >20:poor */
    uint8_t yaw_health; /*!< Specifies the type of RTK orientation, indicating different solutions for calculating the orientation.
                             <1:ideal, 1-2:excellent, 2-5:good, 5-10:moderate, 10-20 fair, >20:poor */
} T_RtkRawDataMsg;

// PSDK_DATAPUSH_CMD_ID_PUSH_UAV_STATE
/**
 * @brief The structure defining UAV State Push contents.
 */
typedef struct {
    struct {
        uint8_t compassState : 1;    /*!< Specifies UAV compass state.
                                          This parameter can be any value of @ref Psdk_Compass_State. */
        uint8_t motorState   : 1;    /*!< Specifies UAV motor state.
                                          This parameter can be any value of @ref Psdk_Motor_State. */
        uint8_t landState    : 2;    /*!< Specifies UAV land state.
                                          This parameter can be any value of @ref Psdk_Land_State. */
        uint8_t reserved     : 4;
    } uavState;
    uint16_t flightTime;             /*!< Specifies UAV flying duration, unit: 0.1s. */
    uint8_t uavType;                 /*!< Specifies uav type.
                                          This parameter can be any value of @ref Psdk_UAV_Type. */
} T_UavStateMsg;

// PSDK_DATAPUSH_CMD_ID_PUSH_APP_DATETIME
/**
 * @brief The structure defining APP Time and Date Push contents.
 */
typedef struct {
    uint16_t year;  /*!< year, @note LSB is at the front and MSB is the back. */
    uint8_t month;  /*!< month */
    uint8_t day;    /*!< day */
    uint8_t hour;   /*!< hour */
    uint8_t minute; /*!< minute */
    uint8_t second; /*!< second */
} T_AppDateTimeMsg;

#pragma pack()

/**
 * @}
 */

/**
 * @}
 */

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif //PSDK_CMDSET_MSG_PUSH_H

/************************ (C) COPYRIGHT DJI Innovations *******END OF FILE******/
