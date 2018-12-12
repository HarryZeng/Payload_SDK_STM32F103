/**
 ******************************************************************************
 * @file    psdk_cmdset_camera.h
 * @version V1.0.0
 * @date    2017/11/9
 * @brief   This file defines the payload SDK camera command set.
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
#ifndef PSDK_CMD_CAMERA_H
#define PSDK_CMD_CAMERA_H

/* Includes ------------------------------------------------------------------*/
#include "psdk_typedef.h"

/** @addtogroup PSDK
 * @{
 */

/** @addtogroup PSDK_Camera
 * @{
 */

/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

/** @defgroup Camera_Exported_Types Exported types
 * @{
 */

/** @defgroup Camera_Command_Related Command Related
 * @{
 */

/**
 * @brief Camera Command ID
 */
typedef enum {
    //base command
    PSDK_CAMERA_CMD_ID_SET_MODE = 0x01,                   /*!< set camera work mode command */
    PSDK_CAMERA_CMD_ID_GET_MODE = 0x02,                   /*!< get camera work mode command */

    PSDK_CAMERA_CMD_ID_SHOOT_PHOTO = 0x03,               /*!< shoot photo command */
    PSDK_CAMERA_CMD_ID_GET_SHOOT_PHOTO_STATE = 0x04,    /*!< get shoot photo state command */

    PSDK_CAMERA_CMD_ID_SET_SHOOT_PHOTO_MODE = 0x05,     /*!< set shoot photo mode command */
    PSDK_CAMERA_CMD_ID_GET_SHOOT_PHOTO_MODE = 0x06,     /*!< get shoot photo mode command */

    PSDK_CAMERA_CMD_ID_RECORD_VIDEO = 0x07,              /*!< record video command */
    PSDK_CAMERA_CMD_ID_GET_RECORD_VIDEO_STATE = 0x08,   /*!< get record video state command */

    PSDK_CAMERA_CMD_ID_GET_SDCARD_PARAM = 0x09,         /*!< get SD card parameter command */
    PSDK_CAMERA_CMD_ID_FORMAT_SDCARD = 0x0A,            /*!< format SD card command */

    PSDK_CAMERA_CMD_ID_SET_METERING_MODE = 0x20,        /*!< set metering mode command */
    PSDK_CAMERA_CMD_ID_GET_METERING_MODE = 0x21,        /*!< get metering mode command */

    PSDK_CAMERA_CMD_ID_SET_SPOT_METERING = 0x22,        /*!< set spot metering zone command */
    PSDK_CAMERA_CMD_ID_GET_SPOT_METERING = 0x23,        /*!< get spot metering zone command */

    //focus command
    PSDK_CAMERA_CMD_ID_SET_FOCUS_MODE = 0x30,           /*!< set focus mode command */
    PSDK_CAMERA_CMD_ID_GET_FOCUS_MODE = 0x31,           /*!< get focus mode command */

    PSDK_CAMERA_CMD_ID_SET_FOCUS_ZONE = 0x32,           /*!< set focus zone command */
    PSDK_CAMERA_CMD_ID_GET_FOCUS_ZONE = 0x33,           /*!< get focus zone command */

    //zoom command
    PSDK_CAMERA_CMD_ID_SET_DIGTALZOOM_FACTOR = 0x34,    /*!< set digital zoom factor command */
    PSDK_CAMERA_CMD_ID_GET_DIGTALZOOM_FACTOR = 0x35,    /*!< get digital zoom factor command */

    PSDK_CAMERA_CMD_ID_GET_OPTICALZOOM_SPEC = 0x36,     /*!< get optical zoom specification command */

    PSDK_CAMERA_CMD_ID_SET_OPTICALZOOM_FOCAL_LENGTH = 0x37,     /*!< set optical zoom focal length command */
    PSDK_CAMERA_CMD_ID_GET_OPTICALZOOM_FOCAL_LENGTH = 0x38,     /*!< get optical zoom focal length command */

    PSDK_CAMERA_CMD_ID_GET_OPTICALZOOM_FACTOR = 0x39,           /*!< get optical zoom focal command */

    PSDK_CAMERA_CMD_ID_START_CONTINUOUS_OPTICAL_ZOOM = 0x40,    /*!< start continuous optical zoom command */
    PSDK_CAMERA_CMD_ID_STOP_CONTINUOUS_OPTICAL_ZOOM = 0x41,     /*!< stop continuous optical zoom command */

    //append focus command
    PSDK_CAMERA_CMD_ID_SET_FOCUS_ASSISTANT_SETTING = 0x42,      /*!< set focus assistant settings command */
    PSDK_CAMERA_CMD_ID_GET_FOCUS_ASSISTANT_SETTING = 0x43,      /*!< get focus assistant settings command */
    PSDK_CAMERA_CMD_ID_GET_FOCUS_RING_VALUE_UPPER_BOUND = 0x44, /*!< get focus ring value upper bound command */
    PSDK_CAMERA_CMD_ID_SET_FOCUS_RING_VALUE = 0x45,             /*!< set focus ring value command */
    PSDK_CAMERA_CMD_ID_GET_FOCUS_RING_VALUE = 0x46,             /*!< get focus ring value command */

    //append zoom command
    PSDK_CAMERA_CMD_ID_GET_DIGITALZOOM_SPEC = 0x47,             /*!< get digital zoom specification command */

    //other command
    PSDK_CAMERA_CMD_ID_SUPPORT_STATE = 0xFF,                    /*!< get camera function support state command */
} E_PsdkCameraCmd;

/**
 * @}
 */

/** @defgroup Camera_Related Camera Related
 * @{
 */

/**
 * @brief Camera work mode.
 */
typedef enum {
    PSDK_CAMERA_CAMERA_MODE_SHOOT_PHOTO = 0,    /*!< Shoot photo mode. */
    PSDK_CAMERA_CAMERA_MODE_RECORD_VIDEO = 1,   /*!< Record video mode. */
} E_PsdkCameraCameraMode;

/**
 * @brief Camera shoot photo action.
 */
typedef enum {
    PSDK_CAMERA_SHOOT_PHOTO_ACTION_STOP = 0,    /*!< Stop shoot photo for stopping interval photographing. */
    PSDK_CAMERA_SHOOT_PHOTO_ACTION_START = 1,   /*!< Start shoot photo. */
} E_PsdkCameraShootPhotoAction;

/**
 * @brief Camera shoot photo mode.
 */
typedef enum {
    PSDK_CAMERA_SHOOT_PHOTO_MODE_SINGLE = 1,    /*!< Single photographing mode. */
    PSDK_CAMERA_SHOOT_PHOTO_MODE_BURST = 4,     /*!< Burst photographing mode. */
    PSDK_CAMERA_SHOOT_PHOTO_MODE_INTERVAL = 6,  /*!< Interval photographing mode. */
} E_PsdkCameraShootPhotoMode;

/**
 * @brief Camera record video action.
 */
typedef enum {
    PSDK_CAMERA_RECORD_VIDEO_ACTION_STOP = 0,   /*!< Stop record video. */
    PSDK_CAMERA_RECORD_VIDEO_ACTION_START = 1,  /*!< Start record video. */
} E_PsdkCameraRecordVideoAction;

/**
 * @brief Photo number of burst photographing.
 */
typedef enum {
    PSDK_CAMERA_BURST_PARAM_2 = 2,              /*!< Photo number of burst photographing: 2. */
    PSDK_CAMERA_BURST_PARAM_3 = 3,              /*!< Photo number of burst photographing: 3. */
    PSDK_CAMERA_BURST_PARAM_5 = 5,              /*!< Photo number of burst photographing: 5. */
    PSDK_CAMERA_BURST_PARAM_7 = 7,              /*!< Photo number of burst photographing: 7. */
    PSDK_CAMERA_BURST_PARAM_10 = 10,            /*!< Photo number of burst photographing: 10. */
} E_PsdkCameraBurstParam;

/**
 * @brief Time interval of interval photographing.
 * @details Unit: s.
 */
typedef enum {
    PSDK_CAMERA_INTERVAL_PARAM_1S = 1,          /*!< Time interval of interval photographing: 1s. */
    PSDK_CAMERA_INTERVAL_PARAM_3S = 3,          /*!< Time interval of interval photographing: 3s. */
    PSDK_CAMERA_INTERVAL_PARAM_5S = 5,          /*!< Time interval of interval photographing: 5s. */
    PSDK_CAMERA_INTERVAL_PARAM_7S = 7,          /*!< Time interval of interval photographing: 7s. */
    PSDK_CAMERA_INTERVAL_PARAM_10S = 10,        /*!< Time interval of interval photographing: 10s. */
    PSDK_CAMERA_INTERVAL_PARAM_15S = 15,        /*!< Time interval of interval photographing: 15s. */
    PSDK_CAMERA_INTERVAL_PARAM_20S = 20,        /*!< Time interval of interval photographing: 20s. */
    PSDK_CAMERA_INTERVAL_PARAM_30S = 30,        /*!< Time interval of interval photographing: 30s. */
} E_PsdkCameraIntervalParam;

/**
 * @brief Camera focus mode.
 */
typedef enum {
    PSDK_CAMERA_FOCUS_MODE_MANUAL = 0,          /*!< Manual focus mode. */
    PSDK_CAMERA_FOCUS_MODE_AUTO = 1,            /*!< Auto focus mode. */
} E_PsdkCameraFocusMode;

/**
 * @brief Camera metering mode.
 */
typedef enum {
    PSDK_CAMERA_METERING_MODE_CENTER = 0,       /*!< Center metering mode. */
    PSDK_CAMERA_METERING_MODE_AVERAGE = 1,      /*!< Average metering mode. */
    PSDK_CAMERA_METERING_MODE_SPOT = 2,         /*!< Spot metering mode. */
} E_PsdkCameraMeteringMode;

/**
 * @brief Camera zoom mode.
 */
typedef enum {
    PSDK_CAMERA_ZOOM_OUT = 0,   /*!< Lens will zoom out. The focal length decreases,
                                        and field of view becomes wider and magnification is lower. */
    PSDK_CAMERA_ZOOM_IN = 1,    /*!< Lens will zoom in. The focal length increases,
                                        and field of view becomes narrower and magnification is higher. */
} E_PsdkCameraZoomDirection;

/**
 * @brief Camera zoom speed.
 */
typedef enum {
    PSDK_CAMERA_ZOOM_SPEED_SLOWEST = 72,            /*!< Slowest speed zoom. */
    PSDK_CAMERA_ZOOM_SPEED_SLOW = 73,               /*!< Slow speed zoom. */
    PSDK_CAMERA_ZOOM_SPEED_MODERATELY_SLOW = 74,   /*!< Moderately slow speed zoom. */
    PSDK_CAMERA_ZOOM_SPEED_NORMAL = 75,             /*!< Normal speed zoom. */
    PSDK_CAMERA_ZOOM_SPEED_MODERATELY_FAST = 76,   /*!< Moderately fast speed zoom. */
    PSDK_CAMERA_ZOOM_SPEED_FAST = 77,                /*!< Fast speed zoom. */
    PSDK_CAMERA_ZOOM_SPEED_FASTEST = 78,            /*!< Fastest speed zoom. */
} E_PsdkCameraZoomSpeed;

/**
 * @}
 */

/** @addtogroup Camera_Command_Related
 * @{
 */

#pragma pack(1)

//PSDK_CAMERA_CMD_ID_SET_MODE
/**
 * @brief Set camera work mode command request data structure.
 */
typedef struct {
    uint8_t cameraMode; /*!< This parameter can be any value of ::E_PsdkCameraCameraMode. */
} T_PsdkCameraSetModeReq;

/**
 * @brief Set camera work mode command ack data structure.
 */
typedef struct {
    uint8_t ackCode;    /*!< Specifies PSDK command ack code.
                             This parameter can be any value of ::E_PsdkCmdAckCode */
} T_PsdkCameraSetModeAck;

//PSDK_CAMERA_CMD_ID_GET_MODE
/**
 * @brief Get camera work mode command request data structure.
 */
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkCameraGetModeReq;

/**
 * @brief Get camera work mode command ack data structure.
 */
typedef struct {
    uint8_t ackCode;    /*!< Specifies PSDK command ack code.
                             This parameter can be any value of ::E_PsdkCmdAckCode */
    uint8_t cameraMode; /*!< This parameter can be any value of ::E_PsdkCameraCameraMode. */
} T_PsdkCameraGetModeAck;

//PSDK_CAMERA_CMD_ID_SHOOT_PHOTO
/**
 * @brief Shoot photo command request data structure.
 */
typedef struct {
    uint8_t shootPhotoAction; /*!< This parameter can be any value of ::E_PsdkCameraShootPhotoAction. */
} T_PsdkCameraShootPhotoReq;

/**
 * @brief Shoot photo command ack data structure.
 */
typedef struct {
    uint8_t ackCode;    /*!< Specifies PSDK command ack code.
                             This parameter can be any value of ::E_PsdkCmdAckCode */
} T_PsdkCameraShootPhotoAck;

//PSDK_CAMERA_CMD_ID_GET_SHOOT_PHOTO_STATE
/**
 * @brief Get shoot photo state command request data structure.
 */
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkCameraGetShootPhotoStateReq;

/**
 * @brief Get shoot photo state command ack data structure.
 */
typedef struct {
    uint8_t ackCode;                    /*!< Specifies PSDK command ack code.
                                             This parameter can be any value of ::E_PsdkCmdAckCode */
    uint8_t isShootingSinglePhoto  : 1; /*!< This parameter is boolean type. */
    uint8_t isShootingIntervalPhoto : 1;/*!< This parameter is boolean type. */
    uint8_t isShootingBurstPhoto : 1;   /*!< This parameter is boolean type. */
    uint8_t isStoringPhoto : 1;         /*!< This parameter is boolean type. */
    uint8_t reserved : 4;
} T_PsdkCameraGetShootPhotoStateAck;

//PSDK_CAMERA_CMD_ID_SET_SHOOT_PHOTO_MODE
/**
 * @brief Set shoot photo mode command request data structure.
 */
typedef struct {
    uint8_t shootPhotoMode; /*!< This parameter can be any value of ::E_PsdkCameraShootPhotoMode. */
    uint8_t burstCount;     /*!< This parameter can be any value of ::E_PsdkCameraBurstParam. */
    uint8_t intervalCount;  /*!< Specifies photo count of interval photographing.
                                 @note 255 means continue capture. */
    uint16_t intervalTime;  /*!< This parameter can be any value of ::E_PsdkCameraIntervalParam, unit: s. */
} T_PsdkCameraSetShootPhotoModeReq;

/**
 * @brief Set shoot photo mode command ack data structure.
 */
typedef struct {
    uint8_t ackCode;    /*!< Specifies PSDK command ack code.
                             This parameter can be any value of ::E_PsdkCmdAckCode */
} T_PsdkCameraSetShootPhotoModeAck;

//PSDK_CAMERA_CMD_ID_GET_SHOOT_PHOTO_MODE
/**
 * @brief Get shoot photo mode command request data structure.
 */
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkCameraGetShootPhotoModeReq;

/**
 * @brief Get shoot photo mode command ack data structure.
 */
typedef struct {
    uint8_t ackCode;        /*!< Specifies PSDK command ack code.
                                 This parameter can be any value of ::E_PsdkCmdAckCode */
    uint8_t shootPhotoMode; /*!< This parameter can be any value of ::E_PsdkCameraShootPhotoMode. */
    uint8_t burstCount;     /*!< This parameter can be any value of ::E_PsdkCameraBurstParam. */
    uint8_t intervalCount;  /*!< Specifies photo count of interval photographing.
                                 @note 255 means continue capture. */
    uint16_t intervalTime;  /*!< This parameter can be any value of ::E_PsdkCameraIntervalParam, unit: s. */
} T_PsdkCameraGetShootPhotoModeAck;

//PSDK_CAMERA_CMD_ID_RECORD_VIDEO
/**
 * @brief Record video action command request data structure.
 */
typedef struct {
    uint8_t recordVideoAction;  /*!< This parameter can be any value of ::E_PsdkCameraRecordVideoAction. */
} T_PsdkCameraRecordVideoReq;

/**
 * @brief Record video action command ack data structure.
 */
typedef struct {
    uint8_t ackCode;    /*!< Specifies PSDK command ack code.
                             This parameter can be any value of ::E_PsdkCmdAckCode */
} T_PsdkCameraRecordVideoAck;

//PSDK_CAMERA_CMD_ID_GET_RECORD_VIDEO_STATE
/**
 * @brief Get record video state command request data structure.
 */
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkCameraGetRecordVideoStateReq;

/**
 * @brief Get record video state command ack data structure.
 */
typedef struct {
    uint8_t ackCode;                        /*!< Specifies PSDK command ack code.
                                                 This parameter can be any value of ::E_PsdkCmdAckCode */
    uint8_t isRecording;                    /*!< This parameter is boolean type. */
    uint16_t currentRecordingTimeInSeconds; /*!< The duration of currently recorded video, unit: s. */
} T_PsdkCameraGetRecordVideoStateAck;

//PSDK_CAMERA_CMD_ID_GET_SDCARD_PARAM
/**
 * @brief Get SD card parameter command request data structure.
 */
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkCameraGetSDCardStateReq;

/**
 * @brief Get SD card parameter command ack data structure.
 */
typedef struct {
    uint8_t ackCode;            /*!< Specifies PSDK command ack code.
                                     This parameter can be any value of ::E_PsdkCmdAckCode */
    uint8_t isInserted : 1;     /*!< Specifies if the SD card is inserted in the camera.
                                     This parameter is boolean type. */
    uint8_t isVerified : 1;     /*!< Specifies if the SD card is verified as genuine.
                                     This parameter is boolean type. */

    uint8_t isInitializing : 1; /*!< This parameter is boolean type. */
    uint8_t isReadOnly : 1;     /*!< This parameter is boolean type. */
    uint8_t isFormatting : 1;   /*!< This parameter is boolean type. */
    uint8_t isFull : 1;         /*!< This parameter is boolean type. */
    uint8_t isInvalidFormat : 1;/*!< This parameter is boolean type. */
    uint8_t hasError : 1;       /*!< This parameter is boolean type. */
    uint8_t reserved;

    uint32_t totalSpaceInMB;    /*!< SD card total capacity, unit: MB. */
    uint32_t remainSpaceInMB;   /*!< SD card remaining capacity, unit: MB. */
    uint32_t availableCaptureCount;             /*!< Available shots, unit: s. */
    uint32_t availableRecordingTimeInSeconds;   /*!< Available video recording time, unit: s. */
} T_PsdkCameraGetSDCardStateAck;

//PSDK_CAMERA_CMD_ID_FORMAT_SDCARD
/**
 * @brief Format SD card command request data structure.
 */
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkCameraFormatSDCardReq;

/**
 * @brief Get record video state command ack data structure.
 */
typedef struct {
    uint8_t ackCode;    /*!< Specifies PSDK command ack code.
                             This parameter can be any value of ::E_PsdkCmdAckCode */
    uint8_t reserved;
} T_PsdkCameraFormatSDCardAck;

//PSDK_CAMERA_CMD_ID_SET_SPOT_METERING
/**
 * @brief Set spot metering zone command request data structure.
 */
typedef struct {
    uint8_t col : 4;    /*!< Specifies column coordinate. This parameter is between 0 and 11. */
    uint8_t row : 4;    /*!< Specifies row coordinate. This parameter is between 0 and 7. */
} T_PsdkCameraSetSpotMeteringReq;

/**
 * @brief Set spot metering zone command ack data structure.
 */
typedef struct {
    uint8_t ackCode;    /*!< Specifies PSDK command ack code.
                             This parameter can be any value of ::E_PsdkCmdAckCode */
} T_PsdkCameraSetSpotMeteringAck;

//PSDK_CAMERA_CMD_ID_GET_SPOT_METERING
/**
 * @brief Get spot metering zone command request data structure.
 */
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkCameraGetSpotMeteringReq;

/**
 * @brief Get spot metering zone command ack data structure.
 */
typedef struct {
    uint8_t ackCode;
    uint8_t col : 4;    /*!< Specifies column coordinate. This parameter is between 0 and 11. */
    uint8_t row : 4;    /*!< Specifies row coordinate. This parameter is between 0 and 7. */
} T_PsdkCameraGetSpotMeteringAck;

//PSDK_CAMERA_CMD_ID_SET_METERING_MODE
/**
 * @brief Set metering mode command request data structure.
 */
typedef struct {
    uint8_t meteringMode;   /*!< This parameter can be any value of ::E_PsdkCameraMeteringMode. */
} T_PsdkCameraSetMeteringModeReq;

/**
 * @brief Set metering mode command ack data structure.
 */
typedef struct {
    uint8_t ackCode;    /*!< Specifies PSDK command ack code.
                             This parameter can be any value of ::E_PsdkCmdAckCode */
} T_PsdkCameraSetMeteringModeAck;

//PSDK_CAMERA_CMD_ID_GET_METERING_MODE
/**
 * @brief Get metering mode command request data structure.
 */
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkCameraGetMeteringModeReq;

/**
 * @brief Get metering mode command ack data structure.
 */
typedef struct {
    uint8_t ackCode;        /*!< Specifies PSDK command ack code.
                                 This parameter can be any value of ::E_PsdkCmdAckCode */
    uint8_t meteringMode;   /*!< This parameter can be any value of ::E_PsdkCameraMeteringMode. */
} T_PsdkCameraGetMeteringModeAck;

//PSDK_CAMERA_CMD_ID_SET_FOCUS_MODE
/**
 * @brief Set focus mode command request data structure.
 */
typedef struct {
    uint8_t focusMode;  /*!< This parameter can be any value of ::E_PsdkCameraFocusMode. */
} T_PsdkCameraSetFocusModeReq;

/**
 * @brief Set focus mode command ack data structure.
 */
typedef struct {
    uint8_t ackCode;    /*!< Specifies PSDK command ack code.
                             This parameter can be any value of ::E_PsdkCmdAckCode */
} T_PsdkCameraSetFocusModeAck;

//PSDK_CAMERA_CMD_ID_GET_FOCUS_MODE
/**
 * @brief Get focus mode command request data structure.
 */
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkCameraGetFocusModeReq;

/**
 * @brief Get focus mode command ack data structure.
 */
typedef struct {
    uint8_t ackCode;    /*!< Specifies PSDK command ack code.
                             This parameter can be any value of ::E_PsdkCmdAckCode */
    uint8_t focusMode;  /*!< This parameter can be any value of ::E_PsdkCameraFocusMode. */
} T_PsdkCameraGetFocusModeAck;

//PSDK_CAMERA_CMD_ID_SET_FOCUS_ZONE
/**
 * @brief Set focus zone command request data structure.
 */
typedef struct {
    psdk_f32_t focusX;  /*!< Specifies horizontal zone coordinate. This parameter is between 0 and 1.
                             The point [0.0, 0.0] represents the top-left angle of the screen.*/
    psdk_f32_t focusY;  /*!< Specifies vertical zone coordinate. This parameter is between 0 and 1. */
} T_PsdkCameraSetFocusZoneReq;

/**
 * @brief Set focus zone command ack data structure.
 */
typedef struct {
    uint8_t ackCode;    /*!< Specifies PSDK command ack code.
                             This parameter can be any value of ::E_PsdkCmdAckCode */
} T_PsdkCameraSetFocusZoneAck;

//PSDK_CAMERA_CMD_ID_GET_FOCUS_ZONE
/**
 * @brief Get focus zone command request data structure.
 */
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkCameraGetFocusZoneReq;

/**
 * @brief Get focus zone command ack data structure.
 */
typedef struct {
    uint8_t ackCode;    /*!< Specifies PSDK command ack code.
                             This parameter can be any value of ::E_PsdkCmdAckCode */
    psdk_f32_t focusX;  /*!< Specifies horizontal zone coordinate. This parameter is between 0 and 1. */
    psdk_f32_t focusY;  /*!< Specifies vertical zone coordinate. This parameter is between 0 and 1. */
} T_PsdkCameraGetFocusZoneAck;

//PSDK_CAMERA_CMD_ID_SET_DIGTALZOOM_FACTOR
/**
 * @brief Set digital zone factor command request data structure.
 */
typedef struct {
    psdk_f32_t factor;  /*!< This parameter is between 1.0 and T_PsdkCameraGetDigitalZoomSpecAck::maxDigitalZoomFactor. */
} T_PsdkCameraSetDigitalZoomFactorReq;

/**
 * @brief Set digital zone factor command ack data structure.
 */
typedef struct {
    uint8_t ackCode;    /*!< Specifies PSDK command ack code.
                             This parameter can be any value of ::E_PsdkCmdAckCode */
} T_PsdkCameraSetDigitalZoomFactorAck;

//PSDK_CAMERA_CMD_ID_GET_DIGTALZOOM_FACTOR
/**
 * @brief Get digital zone factor command request data structure.
 */
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkCameraGetDigitalZoomFactorReq;

/**
 * @brief Get digital zone factor command ack data structure.
 */
typedef struct {
    uint8_t ackCode;    /*!< Specifies PSDK command ack code.
                             This parameter can be any value of ::E_PsdkCmdAckCode */
    psdk_f32_t factor;  /*!< This parameter is between 1.0 and T_PsdkCameraGetDigitalZoomSpecAck::maxDigitalZoomFactor. */
} T_PsdkCameraGetDigitalZoomFactorAck;

//PSDK_CAMERA_CMD_ID_GET_OPTICALZOOM_SPEC
/**
 * @brief Get optical zoom specification command request data structure.
 */
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkCameraGetOpticalZoomSpecReq;

/**
 * @brief Get optical zoom specification command ack data structure.
 */
typedef struct {
    uint8_t ackCode;            /*!< Specifies PSDK command ack code.
                                     This parameter can be any value of ::E_PsdkCmdAckCode */
    uint16_t maxFocalLength;    /*!< The maximum focal length of the lens, unit: 0.1mm. */
    uint16_t minFocalLength;    /*!< The minimum focal length of the lens, unit: 0.1mm. */
    uint16_t focalLengthStep;   /*!< The minimum interval of focal length change, unit: 0.1mm. */
} T_PsdkCameraGetOpticalZoomSpecAck;

//PSDK_CAMERA_CMD_ID_SET_OPTICALZOOM_FOCAL_LENGTH
/**
 * @brief Set optical zoom focal length command request data structure.
 */
typedef struct {
    uint16_t focalLength;    /*!< Focal length of zoom lens, unit: 0.1mm. */
} T_PsdkCameraSetOpticalZoomFocalLengthReq;

/**
 * @brief Set optical zoom focal length command ack data structure.
 */
typedef struct {
    uint8_t ackCode;    /*!< Specifies PSDK command ack code.
                             This parameter can be any value of ::E_PsdkCmdAckCode */
} T_PsdkCameraSetOpticalZoomFocalLengthAck;

//PSDK_CAMERA_CMD_ID_GET_OPTICALZOOM_FOCAL_LENGTH
/**
 * @brief Get optical zoom focal length command request data structure.
 */
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkCameraGetOpticalZoomFocalLengthReq;

/**
 * @brief Get optical zoom focal length command ack data structure.
 */
typedef struct {
    uint8_t ackCode;        /*!< Specifies PSDK command ack code.
                                 This parameter can be any value of ::E_PsdkCmdAckCode */
    uint16_t focalLength;   /*!< Focal length of zoom lens, unit: 0.1mm. */
} T_PsdkCameraGetOpticalZoomFocalLengthAck;

//PSDK_CAMERA_CMD_ID_GET_OPTICALZOOM_FACTOR
/**
 * @brief Get optical zoom fator command request data structure.
 */
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkCameraGetOpticalZoomFactorReq;

/**
 * @brief Get optical zoom fator command ack data structure.
 */
typedef struct {
    uint8_t ackCode;    /*!< Specifies PSDK command ack code.
                             This parameter can be any value of ::E_PsdkCmdAckCode */
    psdk_f32_t factor;  /*!< This parameter is between 1.0 and 30.0. */
} T_PsdkCameraGetOpticalZoomFactorAck;

//PSDK_CAMERA_CMD_ID_START_CONTINUOUS_OPTICAL_ZOOM
/**
 * @brief Start continuous optical zoom command request data structure.
 */
typedef struct {
    uint8_t zoomSpeed;      /*!< This parameter can be any value of ::E_PsdkCameraZoomSpeed. */
    uint8_t zoomDirection;  /*!< This parameter can be any value of ::E_PsdkCameraZoomDirection. */
} T_PsdkCameraStartContinuousOpticalZoomReq;

/**
 * @brief Start continuous optical zoom command ack data structure.
 */
typedef struct {
    uint8_t ackCode;    /*!< Specifies PSDK command ack code.
                             This parameter can be any value of ::E_PsdkCmdAckCode */
} T_PsdkCameraStartContinuousOpticalZoomAck;

//PSDK_CAMERA_CMD_ID_STOP_CONTINUOUS_OPTICAL_ZOOM
/**
 * @brief Stop continuous optical zoom command request data structure.
 */
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkCameraStopContinuousOpticalZoomReq;

/**
 * @brief Stop continuous optical zoom command ack data structure.
 */
typedef struct {
    uint8_t ackCode;    /*!< Specifies PSDK command ack code.
                             This parameter can be any value of ::E_PsdkCmdAckCode */
} T_PsdkCameraStopContinuousOpticalZoomAck;

//PSDK_CAMERA_CMD_ID_SET_FOCUS_ASSISTANT_SETTING
/**
 * @brief Set focus assistant setting command request data structure.
 */
typedef struct {
    uint8_t isEnabledAF:1;  /*!< Specifies if the lens focus assistant is enabled for auto Focusing.
                                 This parameter is boolean type. */
    uint8_t isEnabledMF:1;  /*!< Specifies if the lens focus assistant is enabled for Manual Focusing.
                                 This parameter is boolean type. */
    uint8_t reserved:6;
} T_PsdkCameraSetFocusAssistantSettingsReq;

/**
 * @brief Set focus assistant setting command ack data structure.
 */
typedef struct {
    uint8_t ackCode;    /*!< Specifies PSDK command ack code.
                             This parameter can be any value of ::E_PsdkCmdAckCode */
} T_PsdkCameraSetFocusAssistantSettingsAck;

//PSDK_CAMERA_CMD_ID_GET_FOCUS_ASSISTANT_SETTING
/**
 * @brief Get focus assistant setting command request data structure.
 */
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkCameraGetFocusAssistantSettingsReq;

/**
 * @brief Get focus assistant setting command ack data structure.
 */
typedef struct {
    uint8_t ackCode;        /*!< Specifies PSDK command ack code.
                                 This parameter can be any value of ::E_PsdkCmdAckCode */
    uint8_t isEnabledAF:1;  /*!< Specifies if the lens focus assistant is enabled for auto Focusing.
                                 This parameter is boolean type. */
    uint8_t isEnabledMF:1;  /*!< Specifies if the lens focus assistant is enabled for Manual Focusing.
                                 This parameter is boolean type. */
    uint8_t reserved:6;
} T_PsdkCameraGetFocusAssistantSettingsAck;

//PSDK_CAMERA_CMD_ID_GET_FOCUS_RING_VALUE_UPPER_BOUND
/**
 * @brief Get focus ring value upper bound command request data structure.
 */
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkCameraGetFocusRingValueUpperBoundReq;

/**
 * @brief Get focus ring value upper bound command ack data structure.
 */
typedef struct {
    uint8_t ackCode;                    /*!< Specifies PSDK command ack code.
                                             This parameter can be any value of ::E_PsdkCmdAckCode */
    uint16_t focusRingValueUpperBound;  /*!< Specifies lens focusing ring's max value. */
} T_PsdkCameraGetFocusRingValueUpperBoundAck;

//PSDK_CAMERA_CMD_ID_SET_FOCUS_RING_VALUE
/**
 * @brief Set focus ring value command request data structure.
 */
typedef struct {
    uint16_t focusRingValue;
} T_PsdkCameraSetFocusRingValueReq;

/**
 * @brief Set focus ring value command ack data structure.
 */
typedef struct {
    uint8_t ackCode;    /*!< Specifies PSDK command ack code.
                             This parameter can be any value of ::E_PsdkCmdAckCode */
} T_PsdkCameraSetFocusRingValueAck;

//PSDK_CAMERA_CMD_ID_GET_FOCUS_RING_VALUE
/**
 * @brief Get focus ring value command request data structure.
 */
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkCameraGetFocusRingValueReq;

/**
 * @brief Get focus ring value command ack data structure.
 */
typedef struct {
    uint8_t ackCode;            /*!< Specifies PSDK command ack code.
                                     This parameter can be any value of ::E_PsdkCmdAckCode */
    uint16_t focusRingValue;
} T_PsdkCameraGetFocusRingValueAck;

//PSDK_CAMERA_CMD_ID_GET_DIGITALZOOM_SPEC
/**
 * @brief Get digital zoom specification command request data structure.
 */
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkCameraGetDigitalZoomSpecReq;

/**
 * @brief Get digital zoom specification command ack data structure.
 */
typedef struct {
    uint8_t ackCode;                    /*!< Specifies PSDK command ack code.
                                             This parameter can be any value of ::E_PsdkCmdAckCode */
    psdk_f32_t maxDigitalZoomFactor;    /*!< Specifies max digital zoom factor. */
} T_PsdkCameraGetDigitalZoomSpecAck;

//PSDK_CAMERA_CMD_ID_SUPPORT_STATE
/**
 * @brief Get camera function support state command request data structure.
 */
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkCameraSupportStateReq;

/**
 * @brief Get camera function support state command ack data structure.
 */
typedef struct {
    uint8_t ackCode;                            /*!< Specifies PSDK command ack code.
                                                     This parameter can be any value of ::E_PsdkCmdAckCode */
    uint8_t isCameraCmdSetSupport : 1;          /*!< Specifies if camera commands is supported. */
    uint8_t isDigitalZoomSupported : 1;         /*!< Specifies if digital zoom is supported. */
    uint8_t isOpticalZoomSupported : 1;         /*!< Specifies if optical zoom is supported. */
    uint8_t isAdjustableFocalPointSupported : 1;/*!< Specifies if camera focal is adjustable. */
    uint8_t isExposureMeteringSupported : 1;    /*!< Specifies if exposure metering is supported. */
    uint8_t reserved : 3;
} T_PsdkCameraSupportStateAck;

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

#endif //PSDK_CMD_CAMERA_H
