/**
 **********************************************************************
 * @file    psdk_payload_gimbal.h
 * @version V1.0.0
 * @date    2017/11/10
 * @brief   This is the header file for "psdk_payload_gimbal.c", defining the
 * structures and (exported) function prototypes.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef PSDK_GIMBAL_H
#define PSDK_GIMBAL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "psdk_core.h"
#include "psdk_ack_code.h"

/** @addtogroup PSDK
 * @{
 */

/** @addtogroup PSDK_Gimbal
 * @{
 */

/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

/** @addtogroup Gimbal_Exported_Types
 * @{
 */

/** @defgroup Gimbal_Callback_Related Callback Related
 * @{
 */

/**
 * @brief Function list for handling gimbal commands.
 * @details This structure type is used to define a list that
 * includes all the callback functions related gimbal function:
 * 1. Get gimbal state
 * 2. Set gimbal mode
 * 3. Gimbal return head
 * 4. Control gimbal speed
 * 5. Start gimbal calibration
 */
typedef struct {
    ///Get gimbal state callback function.
    void (*GetGimbalState)(const T_PsdkGimbalGetGimbalStateReq *req, T_PsdkGimbalGetGimbalStateAck *ack);
    ///Set gimbal mode callback function.
    void (*SetGimbalMode)(const T_PsdkGimbalSetGimbalModeReq *req, T_PsdkGimbalSetGimbalModeAck *ack);
    ///Control gimbal return head callback function.
    void (*ReturnHead)(const T_PsdkGimbalReturnHeadReq *req, T_PsdkGimbalReturnHeadAck *ack);
    ///Control gimbal angle speed callback function.
    void (*ControlSpeed)(const T_PsdkGimbalControlSpeedReq *req, T_PsdkGimbalControlSpeedAck *ack);
    ///Gimbal calibration callback function.
    void (*StartCalibration)(const T_PsdkGimbalStartCalibrationReq *req, T_PsdkGimbalStartCalibrationAck *ack);
} T_PsdkGimbalHandler;

/**
 * @}
 */

/**
 * @}
 */

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @addtogroup Gimbal_Exported_Functions
 * @{
 */

E_PsdkStat PsdkGimbal_Init(T_PsdkUpper *psdkUpper, const T_PsdkGimbalHandler *gimbalHandler);

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

#endif //PSDK_PAYLOAD_GIMBAL_H

/****************** (C) COPYRIGHT DJI Innovations *****END OF FILE****/
