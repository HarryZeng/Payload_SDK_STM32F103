/**
 ******************************************************************************
 * @file    psdk_cmdset_gimbal.h
 * @version V1.0.0
 * @date    2017/11/9
 * @brief   This file defines payload sdk gimbal command set.
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
 * ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef PSDK_CMD_SET_GIMBAL_H
#define PSDK_CMD_SET_GIMBAL_H

/* Includes ------------------------------------------------------------------*/
#include "psdk_typedef.h"

/** @addtogroup PSDK
 * @{
 */

/** @addtogroup PSDK_Gimbal
 * @{
 */

/* Exported constants --------------------------------------------------------*/
#define GIMBAL_ACTION       1
#define GOMBAL_STOP_ACTION 0

/* Exported macros -----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

/** @defgroup Gimbal_Exported_Types Exported types
 * @{
 */

/** @defgroup Gimbal_Command_Related Command Related
 * @{
 */

/**
 * @brief Gimbal Command ID
 */
typedef enum {
    PSDK_GIMBAL_CMD_ID_GET_GIMBAL_PARAM = 0x01,         /*!< Get gimbal state command. */
    PSDK_GIMBAL_CMD_ID_SET_GIMBAL_MODE = 0x02,          /*!< Set gimbal mode command. */
    PSDK_GIMBAL_CMD_ID_RETURN_HEAD = 0x03,               /*!< Control gimbal return head command. */
    PSDK_GIMBAL_CMD_ID_CONTROL_SPEED = 0x04,            /*!< Control gimbal angle speed command. */
    PSDK_GIMBAL_CMD_ID_START_CALIBRATION = 0x07,        /*!< Gimbal calibration command. */
    PSDK_GIMBAL_CMD_ID_SUPPORT_STATE = 0xFF,            /*!< Get gimbal function support state command. */
} E_PsdkGimbalCmd;

/**
 * @}
 */

/** @defgroup Gimbal_Related Gimbal Related
 * @{
 */

/**
 * @brief Gimbal mode.
 */
typedef enum {
    PSDK_GIMBAL_GIMBAL_MODE_FREE = 0,           /*!< Free mode, Pitch, roll and yaw are all controllable. */
    PSDK_GIMBAL_GIMBAL_MODE_FPV = 1,            /*!< FPV mode, Only pitch is controllable. */
    PSDK_GIMBAL_GIMBAL_MODE_YAW_FOLLOW = 2,    /*!< Yaw follow mode, Pitch and roll are controllable. */
} E_PsdkGimbalGimbalMode;

/**
 * @}
 */

/** @addtogroup Gimbal_Command_Related
 * @{
 */

#pragma pack(1)

//PSDK_GIMBAL_CMD_ID_GET_GIMBAL_PARAM
/**
 * @brief Get gimbal state command request data structure.
 */
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkGimbalGetGimbalStateReq;

/**
 * @brief Get gimbal state command ack data structure.
 */
typedef struct {
    uint8_t ackCode;                /*!< Specifies PSDK command ack code.
                                         This parameter can be any value of ::E_PsdkCmdAckCode */
    uint8_t gimbalMode;             /*!< This parameter can be any value of ::E_PsdkGimbalGimbalMode. */

    uint8_t isMountedUpwards: 1;    /*!< Specifies gimbal mounting direction. 0 represents downward mounting,
                                         1 represents upward mounting. */
    uint8_t isYawLimit      : 1;    /*!< Specifies whether YAW axis reaches limits. */
    uint8_t isRollLimit     : 1;    /*!< Specifies whether ROLL axis reaches limits. */
    uint8_t isPitchLimit    : 1;    /*!< Specifies whether PITCH axis reaches limits. */
    uint8_t reserved        : 4;

    int16_t pitch;                  /*!< Specifies current PITCH axis angle, unit: 0.1 degree.
                                         @note The parameter refer to NED coordinate system. */
    int16_t roll;                   /*!< Specifies current ROLL axis angle, unit: 0.1 degree.
                                         @note The parameter refer to NED coordinate system. */
    int16_t yaw;                    /*!< Specifies current YAW axis angle, unit: 0.1 degree.
                                         @note The parameter refer to NED coordinate system. */
} T_PsdkGimbalGetGimbalStateAck;

//PSDK_GIMBAL_CMD_ID_SET_GIMBAL_MODE
/**
 * @brief Set gimbal mode command request data structure.
 */
typedef struct {
    uint8_t gimbalMode; /*!< This parameter can be any value of ::E_PsdkGimbalGimbalMode. */
} T_PsdkGimbalSetGimbalModeReq;

/**
 * @brief Set gimbal mode command ack data structure.
 */
typedef struct {
    uint8_t ackCode;    /*!< Specifies PSDK command ack code.
                             This parameter can be any value of ::E_PsdkCmdAckCode */
} T_PsdkGimbalSetGimbalModeAck;

//PSDK_GIMBAL_CMD_ID_RETURN_HEAD
/**
 * @brief Control gimbal return head command request data structure.
 */
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkGimbalReturnHeadReq;

/**
 * @brief Control gimbal return head command ack data structure.
 */
typedef struct {
    uint8_t ackCode;    /*!< Specifies PSDK command ack code.
                             This parameter can be any value of ::E_PsdkCmdAckCode */
} T_PsdkGimbalReturnHeadAck;

//PSDK_GIMBAL_CMD_ID_CONTROL_SPEED
/**
 * @brief Control gimbal angle speed command request data structure.
 */
typedef struct {
    int16_t pitchSpeed; /*!< Pitch axis speed, unit: 0.1 degree/s. */
    int16_t rollSpeed;  /*!< Roll axis speed, unit: 0.1 degree/s. */
    int16_t yawSpeed;   /*!< Yaw axis speed, unit: 0.1 degree/s. */
    uint8_t ctrlFlag;   /*!< Specifies gimbal control action. 1 represents control gimbal,
                             0 represents stop control gimbal. */
} T_PsdkGimbalControlSpeedReq;

/**
 * @brief Control gimbal angle speed command ack data structure.
 */
typedef struct {
    uint8_t ackCode;    /*!< Specifies PSDK command ack code.
                             This parameter can be any value of ::E_PsdkCmdAckCode */
} T_PsdkGimbalControlSpeedAck;

//PSDK_GIMBAL_CMD_ID_START_CALIBRATION
/**
 * @brief Control gimbal calibration command request data structure.
 */
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkGimbalStartCalibrationReq;

/**
 * @brief Control gimbal calibration command ack data structure.
 */
typedef struct {
    uint8_t ackCode;    /*!< Specifies PSDK command ack code.
                             This parameter can be any value of ::E_PsdkCmdAckCode */
} T_PsdkGimbalStartCalibrationAck;

//PSDK_GIMBAL_CMD_ID_SUPPORT_STATE
/**
 * @brief Get gimbal function support state command request data structure.
 */
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkGimbalSupportStateReq;

/**
 * @brief Get gimbal function support state command ack data structure.
 */
typedef struct {
    uint8_t ackCode;                    /*!< Specifies PSDK command ack code.
                                             This parameter can be any value of ::E_PsdkCmdAckCode */
    uint8_t isGimbalCmdSetSupport : 1;  /*!< Specifies if gimbal commands is supported. */
    uint8_t reserved : 7;
} T_PsdkGimbalSupportStateAck;

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

#endif //PSDK_CMD_SET_GIMBAL_H
