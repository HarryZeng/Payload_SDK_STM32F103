/**
 ******************************************************************************
 * @file    psdk_msg_subcribe.h
 * @version V0.0.0
 * @date    2017/11/10
 * @brief
 * This is the header file for "psdk_msg_subcribe.c", defining the structure and
 * (exported) function prototypes. 
 *
 * @Copyright (c) 2017-2018 DJI. All rights reserved.
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
#ifndef PSDK_MSG_SUBCRIBE_H
#define PSDK_MSG_SUBCRIBE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "psdk_upper.h"
#include "psdk_cmdset.h"

/** @addtogroup PSDK
 * @{
 */

/** @addtogroup PSDK_Message_Push
 * @{
 */

/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

/** @defgroup M_Push_Exported_Types Exported Types
 * @{
 */

/** @defgroup M_Push_Callback_Related Callback Related
 * @{
 */

/**
 * @brief Callback function list for receiving push data.
 * @details This structure type is used to define a list structure that
 * includes all the callback functions that you can design for the push data:
 * 1. Image transmission bandwidth push
 * 2. UAV attitude push
 * 3. Battery information push
 * 4. GPS information push
 * 5. UAV state push
 * 6. APP time and date push
 * 7. Barometric height push
 * 8. GPS raw data push
 * 9. RTK raw data push
 * @note You must specify the message rate through DJI Assistant 2 for the push data.
 */
typedef struct {
    void (*bandWidthMsgCallback)        (const T_BandWidthMsg *);   /*!< Image transmission bandwidth push callback function. */
    void (*uavAttitudeMsgCallback)      (const T_UavAttitudeMsg *); /*!< UAV attitude push callback function. */
    void (*batteryInfoMsgCallback)      (const T_BatteryInfoMsg *, T_BatteryInfoAck *);
                                                                     /*!< Battery information push callback function. */
    void (*gpsInfoMsgCallback)          (const T_GPSInfoMsg *);     /*!< GPS information push callback function. */
    void (*uavStateMsgCallback)         (const T_UavStateMsg *);    /*!< UAV state push callback function. */
    void (*appDateTimeMsgCallback)      (const T_AppDateTimeMsg *); /*!< APP time and date push callback function. */
    void (*baroHeightDataMsgCallback)   (const T_baroHeightDataMsg *);/*!< Barometric height push callback function. */
    void (*gpsRawDataMsgCallback)       (const T_GpsRawDataMsg *);  /*!< GPS raw data push callback function. */
    void (*rtkRawDataMsgCallback)       (const T_RtkRawDataMsg *);  /*!< RTK raw data push callback function. */
} T_PsdkPushDataMsgCallbackList;

/**
 * @}
 */

/**
 * @}
 */

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @addtogroup M_Push_Exported_Functions
 * @{
 */

E_PsdkStat PsdkMsgSub_Init(T_PsdkUpper *psdkUpper);
E_PsdkStat PsdkMsgSub_RegMsgCallbackList(T_PsdkUpper *psdkUpper, const T_PsdkPushDataMsgCallbackList *PushDataMsgCallbackList);

/**
 * @}
 */

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

#endif //PSDK_MSG_SUBCRIBE_H

/************************ (C) COPYRIGHT DJI Innovations *******END OF FILE******/
