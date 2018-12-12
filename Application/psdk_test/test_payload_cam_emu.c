/**
 ******************************************************************************
 * @file    test_payload_cam_emu.c
 * @version V1.3.0
 * @date    2018/09/19
 * @brief   The file define PSDK camera command callback functions for demo board.
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
//#include <os_util.h>
#include <psdk_cmdset_define/psdk_cmdset_camera.h>
#include "test_payload_cam_emu.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define EMU_SINGLE_TIME_COST        500

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

//camera mode
static uint8_t s_cameraMode = PSDK_CAMERA_CAMERA_MODE_SHOOT_PHOTO;

//photography related parameters
static uint8_t photographyMode = PSDK_CAMERA_SHOOT_PHOTO_MODE_SINGLE;
static uint8_t burstCount = PSDK_CAMERA_BURST_PARAM_3;
static uint8_t intervalCount = 255;
static uint16_t intervalTime = PSDK_CAMERA_INTERVAL_PARAM_5S;   //unit:s
static uint8_t photographyIsOnInterval = 0;
static uint8_t isShootingSinglePhoto = 0; // boolean type
static uint8_t isShootingBurstPhoto = 0;
static uint8_t isStoringPhoto = 0;
static uint32_t ShotStTimeMs = 0;

//record video related parameters
static uint8_t recordingState = 0;
static uint32_t recordingStTimeMs = 0;

//SD card parameters
static uint8_t insertState = 1;
static uint32_t capacity = 4096;              //uint: MB
static uint32_t remainCapacity = 2048;        //unit: MB
static uint32_t remainShots = 100;
static uint32_t remainRecordTime = 6000;      //unit: s

//metering related parameters
static uint8_t meteringMode = PSDK_CAMERA_METERING_MODE_SPOT;
static uint8_t meteringCol = 6;    // 0 ~ 11
static uint8_t meteringRow = 4;    // 0 ~ 7

//focus related parameters
static uint8_t focusMode = PSDK_CAMERA_FOCUS_MODE_AUTO;
static psdk_f32_t focusX = 0.5;  // 0 ~ 1
static psdk_f32_t focusY = 0.5;  // 0 ~ 1
static uint8_t isEnableMF = 1;
static uint8_t isEnableAF = 1;
static uint16_t focusRingValueUpperBound = 1000;
static uint16_t focusRingValue = 500;

//zoom related parameters
static uint16_t maxFocalLength = 410;    //unit: 0.1mm
static uint16_t minFocalLength = 120;    //unit: 0.1mm
static uint16_t focalLengthStep = 10;   //unit: 0.1mm
static uint16_t currentFocalLength = 120;
static psdk_f32_t digitalFactor = 1.0;  //1.0 to 2.0
static psdk_f32_t opticalFactor = 1.0;  //1.0 to 30.0
static E_PsdkCameraZoomDirection zoomDirection;
static E_PsdkCameraZoomSpeed zoomSpeed;
static uint8_t isZooming = 0;

/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

//============================= Base function ===========================================================//
/**
 * @brief Set camera work mode callback function.
 * @param req Command request structure, please refer to ::T_PsdkCameraSetModeReq for details.
 * @param ack Command ack structure, please refer to ::T_PsdkCameraSetModeAck for details.
 * @return None.
 */
void CamEmu_SetCameraMode(const T_PsdkCameraSetModeReq *req, T_PsdkCameraSetModeAck *ack)
{
    PSDK_LOG_DEBUG("Set Camera Work Mode");

    s_cameraMode = req->cameraMode;

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

/**
 * @brief Get camera work mode callback function.
 * @param req Command request structure, please refer to ::T_PsdkCameraGetModeReq for details.
 * @param ack Command ack structure, please refer to ::T_PsdkCameraGetModeAck for details.
 * @return None.
 */
void CamEmu_GetCameraMode(const T_PsdkCameraGetModeReq *req, T_PsdkCameraGetModeAck *ack)
{
//    PSDK_LOG_DEBUG("Get Camera Work Mode");

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
    ack->cameraMode = s_cameraMode;
}

/**
 * @brief Shoot photo callback function.
 * @param req Command request structure, please refer to ::T_PsdkCameraShootPhotoReq for details.
 * @param ack Command ack structure, please refer to ::T_PsdkCameraShootPhotoAck for details.
 * @return None.
 */
void CamEmu_Photography(const T_PsdkCameraShootPhotoReq *req, T_PsdkCameraShootPhotoAck *ack)
{
    PSDK_LOG_DEBUG("ShootPhoto");

    //photography process
    if (req->shootPhotoAction == PSDK_CAMERA_SHOOT_PHOTO_ACTION_START) {
        ShotStTimeMs = OS_GET_TIME_MS;

        if (photographyMode == PSDK_CAMERA_SHOOT_PHOTO_MODE_INTERVAL) {
            isShootingSinglePhoto = 1;
            photographyIsOnInterval = 1;
        } else if (photographyMode == PSDK_CAMERA_SHOOT_PHOTO_MODE_SINGLE) {
            isShootingSinglePhoto = 1;
        } else if (photographyMode == PSDK_CAMERA_SHOOT_PHOTO_MODE_BURST) {
            isShootingBurstPhoto = 1;
        }
    } else if (req->shootPhotoAction == PSDK_CAMERA_SHOOT_PHOTO_ACTION_STOP) {
        photographyIsOnInterval = 0;
        isShootingSinglePhoto = 0;
        isShootingBurstPhoto = 0;
        isStoringPhoto = 0;
    }

    //ack
    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

/**
 * @brief Get shoot photo state callback function.
 * @param req Command request structure, please refer to ::T_PsdkCameraGetShootPhotoStateReq for details.
 * @param ack Command ack structure, please refer to ::T_PsdkCameraGetShootPhotoStateAck for details.
 * @return None.
 */
void CamEmu_GetPhotographyState(const T_PsdkCameraGetShootPhotoStateReq *req, T_PsdkCameraGetShootPhotoStateAck *ack)
{
//    PSDK_LOG_DEBUG("Get ShootPhoto State");

    //emulate phtography state
    if (photographyIsOnInterval == 1) {
        //interval
        uint32_t tmp = (OS_GET_TIME_MS - ShotStTimeMs) % (intervalTime * 1000);
        if (tmp <= EMU_SINGLE_TIME_COST) {
            isShootingSinglePhoto = 1;
        } else {
            isShootingSinglePhoto = 0;
        }
    } else {
        //other
        if (isShootingSinglePhoto == 1) {
            if (OS_GET_TIME_MS - ShotStTimeMs > EMU_SINGLE_TIME_COST) {
                isShootingSinglePhoto = 0;
            }
        } else if (isShootingBurstPhoto == 1) {
            if (OS_GET_TIME_MS - ShotStTimeMs > EMU_SINGLE_TIME_COST * burstCount) {
                isShootingBurstPhoto = 0;
            }
        }
    }

    //ack
    ack->ackCode = PSDK_CMD_ACK_CODE_OK;

    ack->isShootingIntervalPhoto = photographyIsOnInterval;
    ack->isShootingSinglePhoto = isShootingSinglePhoto;
    ack->isShootingBurstPhoto = isShootingBurstPhoto;
    ack->isStoringPhoto = isStoringPhoto;

}

/**
 * @brief Set shoot photo mode callback function.
 * @param req Command request structure, please refer to ::T_PsdkCameraSetShootPhotoModeReq for details.
 * @param ack Command ack structure, please refer to ::T_PsdkCameraSetShootPhotoModeAck for details.
 * @return None.
 */
void CamEmu_SetPhotographyMode(const T_PsdkCameraSetShootPhotoModeReq *req, T_PsdkCameraSetShootPhotoModeAck *ack)
{
    PSDK_LOG_DEBUG("Set ShootPhoto Mode");
    ack->ackCode = PSDK_CMD_ACK_CODE_OK;

    photographyMode = req->shootPhotoMode;
    burstCount = req->burstCount;
    intervalCount = req->intervalCount;
    intervalTime = req->intervalTime;
}

/**
 * @brief Get shoot photo callback function.
 * @param req Command request structure, please refer to ::T_PsdkCameraGetShootPhotoModeReq for details.
 * @param ack Command ack structure, please refer to ::T_PsdkCameraGetShootPhotoModeAck for details.
 * @return None.
 */
void CamEmu_GetPhotographyMode(const T_PsdkCameraGetShootPhotoModeReq *req, T_PsdkCameraGetShootPhotoModeAck *ack)
{
//    PSDK_LOG_DEBUG("Get ShootPhoto Mode");
    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
    ack->shootPhotoMode = photographyMode;
    ack->burstCount = burstCount;
    ack->intervalCount = intervalCount;
    ack->intervalTime = intervalTime;
}

/**
 * @brief Record video callback function.
 * @param req Command request structure, please refer to ::T_PsdkCameraRecordVideoReq for details.
 * @param ack Command ack structure, please refer to ::T_PsdkCameraRecordVideoAck for details.
 * @return None.
 */
void CamEmu_SetRecording(const T_PsdkCameraRecordVideoReq *req, T_PsdkCameraRecordVideoAck *ack)
{
    PSDK_LOG_DEBUG("Set Recording");

    //recording process
    if (req->recordVideoAction == PSDK_CAMERA_RECORD_VIDEO_ACTION_START) {
        recordingState = 1;
        recordingStTimeMs = OS_GET_TIME_MS;
    } else {
        recordingState = 0;
    }

    //ack
    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

/**
 * @brief Get record video state callback function.
 * @param req Command request structure, please refer to ::T_PsdkCameraGetRecordVideoStateReq for details.
 * @param ack Command ack structure, please refer to ::T_PsdkCameraGetRecordVideoStateAck for details.
 * @return None.
 */
void CamEmu_GetRecordingState(const T_PsdkCameraGetRecordVideoStateReq *req, T_PsdkCameraGetRecordVideoStateAck *ack)
{
//    PSDK_LOG_DEBUG("Get Recording State");

    ack->isRecording = recordingState;
    ack->currentRecordingTimeInSeconds = (uint16_t) ((OS_GET_TIME_MS - recordingStTimeMs) / 1000);

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

/**
 * @brief Get SD card state callback function.
 * @param req Command request structure, please refer to ::T_PsdkCameraGetSDCardStateReq for details.
 * @param ack Command ack structure, please refer to ::T_PsdkCameraGetSDCardStateAck for details.
 * @return None.
 */
void CamEmu_GetSdcardParam(const T_PsdkCameraGetSDCardStateReq *req, T_PsdkCameraGetSDCardStateAck *ack)
{
//    PSDK_LOG_DEBUG("Get Sd card Param");

    ack->isInserted = insertState;
    ack->isVerified = 1;

    ack->isInitializing = 0;
    ack->isReadOnly = 0;
    ack->isFormatting = 0;
    ack->isFull = 0;
    ack->isInvalidFormat = 0;
    ack->hasError = 0;

    ack->totalSpaceInMB = capacity;
    ack->remainSpaceInMB = remainCapacity;
    ack->availableRecordingTimeInSeconds = remainRecordTime;
    ack->availableCaptureCount = remainShots;

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

/**
 * @brief Format SD card callback function.
 * @param req Command request structure, please refer to ::T_PsdkCameraFormatSDCardReq for details.
 * @param ack Command ack structure, please refer to ::T_PsdkCameraFormatSDCardAck for details.
 * @return None.
 */
void CamEmu_FormatSdcard(const T_PsdkCameraFormatSDCardReq *req, T_PsdkCameraFormatSDCardAck *ack)
{
    PSDK_LOG_DEBUG("Format Sd card");

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

//============================= Metering ===========================================================//
/**
 * @brief Set metering mode callback function.
 * @param req Command request structure, please refer to ::T_PsdkCameraSetMeteringModeReq for details.
 * @param ack Command ack structure, please refer to ::T_PsdkCameraSetMeteringModeAck for details.
 * @return None.
 */
void CamEmu_SetMeteringMode(const T_PsdkCameraSetMeteringModeReq *req, T_PsdkCameraSetMeteringModeAck *ack)
{
    PSDK_LOG_DEBUG("Set Metering Mode");

    //set metering mode
    meteringMode = req->meteringMode;

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

/**
 * @brief Get metering mode callback function.
 * @param req Command request structure, please refer to ::T_PsdkCameraGetMeteringModeReq for details.
 * @param ack Command ack structure, please refer to ::T_PsdkCameraGetMeteringModeAck for details.
 * @return None.
 */
void CamEmu_GetMeteringMode(const T_PsdkCameraGetMeteringModeReq *req, T_PsdkCameraGetMeteringModeAck *ack)
{
//    PSDK_LOG_DEBUG("Get Metering Mode");

    ack->meteringMode = meteringMode;

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

/**
 * @brief Set spot metering zone callback function.
 * @param req Command request structure, please refer to ::T_PsdkCameraSetSpotMeteringReq for details.
 * @param ack Command ack structure, please refer to ::T_PsdkCameraSetSpotMeteringAck for details.
 * @return None.
 */
void CamEmu_SetSpotMetering(const T_PsdkCameraSetSpotMeteringReq *req, T_PsdkCameraSetSpotMeteringAck *ack)
{
    PSDK_LOG_DEBUG("Set Spot Metering");

    //set SpotMetering
    meteringCol = req->col;
    meteringRow = req->row;

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

/**
 * @brief Get spot metering zone callback function.
 * @param req Command request structure, please refer to ::T_PsdkCameraGetSpotMeteringReq for details.
 * @param ack Command ack structure, please refer to ::T_PsdkCameraGetSpotMeteringAck for details.
 * @return None.
 */
void CamEmu_GetSpotMetering(const T_PsdkCameraGetSpotMeteringReq *req, T_PsdkCameraGetSpotMeteringAck *ack)
{
//    PSDK_LOG_DEBUG("Get Spot Metering");

    //get spot metering
    ack->col = meteringCol;
    ack->row = meteringRow;

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

//============================= focus ===========================================================//
//focus function
/**
 * @brief Set focus mode callback function.
 * @param req Command request structure, please refer to ::T_PsdkCameraSetFocusModeReq for details.
 * @param ack Command ack structure, please refer to ::T_PsdkCameraSetFocusModeAck for details.
 * @return None.
 */
void CamEmu_SetFocusMode(const T_PsdkCameraSetFocusModeReq *req, T_PsdkCameraSetFocusModeAck *ack)
{
    PSDK_LOG_DEBUG("Set Focus Mode");

    //set focus mode
    focusMode = req->focusMode;

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

/**
 * @brief Get focus mode callback function.
 * @param req Command request structure, please refer to ::T_PsdkCameraGetFocusModeReq for details.
 * @param ack Command ack structure, please refer to ::T_PsdkCameraGetFocusModeAck for details.
 * @return None.
 */
void CamEmu_GetFocusMode(const T_PsdkCameraGetFocusModeReq *req, T_PsdkCameraGetFocusModeAck *ack)
{
//    PSDK_LOG_DEBUG("Get Focus Zone");

    //get focus mode
    ack->focusMode = focusMode;

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

/**
 * @brief Set focus zone callback function.
 * @param req Command request structure, please refer to ::T_PsdkCameraSetFocusZoneReq for details.
 * @param ack Command ack structure, please refer to ::T_PsdkCameraSetFocusZoneAck for details.
 * @return None.
 */
void CamEmu_SetFocusZone(const T_PsdkCameraSetFocusZoneReq *req, T_PsdkCameraSetFocusZoneAck *ack)
{
    PSDK_LOG_DEBUG("Set Focus Zone");

    //set focus zone
    focusX = req->focusX;
    focusY = req->focusY;

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

/**
 * @brief Get focus zone callback function.
 * @param req Command request structure, please refer to ::T_PsdkCameraGetFocusZoneReq for details.
 * @param ack Command ack structure, please refer to ::T_PsdkCameraGetFocusZoneAck for details.
 * @return None.
 */
void CamEmu_GetFocusZone(const T_PsdkCameraGetFocusZoneReq *req, T_PsdkCameraGetFocusZoneAck *ack)
{
//    PSDK_LOG_DEBUG("Get Focus Zone");

    //get focus zone
    ack->focusX = focusX;
    ack->focusY = focusY;

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

/**
 * @brief Set focus assistant settings callback function.
 * @param req Command request structure, please refer to ::T_PsdkCameraSetFocusAssistantSettingsReq for details.
 * @param ack Command ack structure, please refer to ::T_PsdkCameraSetFocusAssistantSettingsAck for details.
 * @return None.
 */
void CamEmu_SetFocusAssistantSettings(const T_PsdkCameraSetFocusAssistantSettingsReq *req,
                                      T_PsdkCameraSetFocusAssistantSettingsAck *ack)
{
    PSDK_LOG_DEBUG("Set Focus Assistant Setting");
    isEnableMF = req->isEnabledMF;
    isEnableAF = req->isEnabledAF;

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

/**
 * @brief Get focus assistant settings callback function.
 * @param req Command request structure, please refer to ::T_PsdkCameraGetFocusAssistantSettingsReq for details.
 * @param ack Command ack structure, please refer to ::T_PsdkCameraGetFocusAssistantSettingsAck for details.
 * @return None.
 */
void CamEmu_GetFocusAssistantSettings(const T_PsdkCameraGetFocusAssistantSettingsReq *req,
                                      T_PsdkCameraGetFocusAssistantSettingsAck *ack)
{
//    PSDK_LOG_DEBUG("Get Focus Assistant Setting");

    ack->isEnabledMF = isEnableMF;
    ack->isEnabledAF = isEnableAF;

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

/**
 * @brief Get focus ring value upper bound callback function.
 * @param req Command request structure, please refer to ::T_PsdkCameraGetFocusRingValueUpperBoundReq for details.
 * @param ack Command ack structure, please refer to ::T_PsdkCameraGetFocusRingValueUpperBoundAck for details.
 * @return None.
 */
void CamEmu_GetFocusRingValueUpperBound(const T_PsdkCameraGetFocusRingValueUpperBoundReq *req,
                                        T_PsdkCameraGetFocusRingValueUpperBoundAck *ack)
{
//    PSDK_LOG_DEBUG("Get Focus Ring Value Bound");

    ack->focusRingValueUpperBound = focusRingValueUpperBound;

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

/**
 * @brief Set focus ring value callback function.
 * @param req Command request structure, please refer to ::T_PsdkCameraSetFocusRingValueReq for details.
 * @param ack Command ack structure, please refer to ::T_PsdkCameraSetFocusRingValueAck for details.
 * @return None.
 */
void CamEmu_SetFocusRingValue(const T_PsdkCameraSetFocusRingValueReq *req, T_PsdkCameraSetFocusRingValueAck *ack)
{
    PSDK_LOG_DEBUG("Set Focus Ring Value");

    focusRingValue = req->focusRingValue;

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

/**
 * @brief Get focus ring value callback function.
 * @param req Command request structure, please refer to ::T_PsdkCameraGetFocusRingValueReq for details.
 * @param ack Command ack structure, please refer to ::T_PsdkCameraGetFocusRingValueAck for details.
 * @return None.
 */
void CamEmu_GetFocusRingValue(const T_PsdkCameraGetFocusRingValueReq *req, T_PsdkCameraGetFocusRingValueAck *ack)
{
//    PSDK_LOG_DEBUG("Get Focus Ring Value");

    ack->focusRingValue = focusRingValue;

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

//============================= zoom ===========================================================//
//zoom function
/**
 * @brief Get digital zoom specification callback function.
 * @param req Command request structure, please refer to ::T_PsdkCameraGetDigitalZoomSpecReq for details.
 * @param ack Command ack structure, please refer to ::T_PsdkCameraGetDigitalZoomSpecAck for details.
 * @return None.
 */
void CamEmu_GetDigitalZoomSpec(const T_PsdkCameraGetDigitalZoomSpecReq *req, T_PsdkCameraGetDigitalZoomSpecAck *ack)
{
    ack->maxDigitalZoomFactor = 12.0;

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

/**
 * @brief Set digital zoom factor callback function.
 * @param req Command request structure, please refer to ::T_PsdkCameraSetDigitalZoomFactorReq for details.
 * @param ack Command ack structure, please refer to ::T_PsdkCameraSetDigitalZoomFactorAck for details.
 * @return None.
 */
void
CamEmu_SetDigitalZoomFactor(const T_PsdkCameraSetDigitalZoomFactorReq *req, T_PsdkCameraSetDigitalZoomFactorAck *ack)
{
    PSDK_LOG_DEBUG("Set Digital Zoom Factor");

    digitalFactor = req->factor;

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

/**
 * @brief Get digital zoom factor callback function.
 * @param req Command request structure, please refer to ::T_PsdkCameraGetDigitalZoomFactorReq for details.
 * @param ack Command ack structure, please refer to ::T_PsdkCameraGetDigitalZoomFactorAck for details.
 * @return None.
 */
void
CamEmu_GetDigitalZoomFactor(const T_PsdkCameraGetDigitalZoomFactorReq *req, T_PsdkCameraGetDigitalZoomFactorAck *ack)
{
//    PSDK_LOG_DEBUG("Get Digital Zoom Factor");

    ack->factor = digitalFactor;

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

/**
 * @brief Get optical zoom specification callback function.
 * @param req Command request structure, please refer to ::T_PsdkCameraGetOpticalZoomSpecReq for details.
 * @param ack Command ack structure, please refer to ::T_PsdkCameraGetOpticalZoomSpecAck for details.
 * @return None.
 */
void CamEmu_GetOpticalZoomSpec(const T_PsdkCameraGetOpticalZoomSpecReq *req, T_PsdkCameraGetOpticalZoomSpecAck *ack)
{
//    PSDK_LOG_DEBUG("GetOpticalZoomSpec");

    ack->maxFocalLength = maxFocalLength;
    ack->minFocalLength = minFocalLength;
    ack->focalLengthStep = focalLengthStep;

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

/**
 * @brief Set optical zoom focal length callback function.
 * @param req Command request structure, please refer to ::T_PsdkCameraSetOpticalZoomFocalLengthReq for details.
 * @param ack Command ack structure, please refer to ::T_PsdkCameraSetOpticalZoomFocalLengthAck for details.
 * @return None.
 */
void
CamEmu_SetOpticalZoomFocalLength(const T_PsdkCameraSetOpticalZoomFocalLengthReq *req,
                                 T_PsdkCameraSetOpticalZoomFocalLengthAck *ack)
{
    PSDK_LOG_DEBUG("SetOpticalZoomFocalLength");

    currentFocalLength = req->focalLength;

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

/**
 * @brief Get optical zoom focal length callback function.
 * @param req Command request structure, please refer to ::T_PsdkCameraGetOpticalZoomFocalLengthReq for details.
 * @param ack Command ack structure, please refer to ::T_PsdkCameraGetOpticalZoomFocalLengthAck for details.
 * @return None.
 */
void CamEmu_GetOpticalZoomFocalLength(const T_PsdkCameraGetOpticalZoomFocalLengthReq *req,
                                      T_PsdkCameraGetOpticalZoomFocalLengthAck *ack)
{
//    PSDK_LOG_DEBUG("GetOpticalZoomFocalLength");

    if (isZooming) {
        int tempFocalLength = currentFocalLength;

        if (zoomDirection == PSDK_CAMERA_ZOOM_IN) {
            tempFocalLength += (zoomSpeed - 71) * 5;
        } else {
            tempFocalLength -= (zoomSpeed - 71) * 5;
        }

        if (tempFocalLength > maxFocalLength) {
            tempFocalLength = maxFocalLength;
        }

        if (tempFocalLength < minFocalLength) {
            tempFocalLength = minFocalLength;
        }

        currentFocalLength = (uint16_t) tempFocalLength;
    }

    ack->focalLength = currentFocalLength;
    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

/**
 * @brief Get optical zoom factor callback function.
 * @param req Command request structure, please refer to ::T_PsdkCameraGetOpticalZoomFactorReq for details.
 * @param ack Command ack structure, please refer to ::T_PsdkCameraGetOpticalZoomFactorAck for details.
 * @return None.
 */
void
CamEmu_GetOpticalZoomFactor(const T_PsdkCameraGetOpticalZoomFactorReq *req, T_PsdkCameraGetOpticalZoomFactorAck *ack)
{
//    PSDK_LOG_DEBUG("GetOpticalZoomFactor");

    opticalFactor = (psdk_f32_t) ((currentFocalLength - minFocalLength) / 10 + 1.0);
    ack->factor = opticalFactor;

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

/**
 * @brief Start continuous optical zoom callback function.
 * @param req Command request structure, please refer to ::T_PsdkCameraStartContinuousOpticalZoomReq for details.
 * @param ack Command ack structure, please refer to ::T_PsdkCameraStartContinuousOpticalZoomAck for details.
 * @return None.
 */
void CamEmu_StartContinuousOpticalZoom(const T_PsdkCameraStartContinuousOpticalZoomReq *req,
                                       T_PsdkCameraStartContinuousOpticalZoomAck *ack)
{
    PSDK_LOG_DEBUG("Start Continuous Zoom");
    isZooming = 1;
    zoomDirection = (E_PsdkCameraZoomDirection) req->zoomDirection;
    zoomSpeed = (E_PsdkCameraZoomSpeed) req->zoomSpeed;

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

/**
 * @brief Stop continuous optical zoom callback function.
 * @param req Command request structure, please refer to ::T_PsdkCameraStopContinuousOpticalZoomReq for details.
 * @param ack Command ack structure, please refer to ::T_PsdkCameraStopContinuousOpticalZoomAck for details.
 * @return None.
 */
void CamEmu_StopContinuousOpticalZoom(const T_PsdkCameraStopContinuousOpticalZoomReq *req,
                                      T_PsdkCameraStopContinuousOpticalZoomAck *ack)
{
    PSDK_LOG_DEBUG("Stop Continuous Zoom");
    isZooming = 0;

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

//camera command callback funtion list
const T_PsdkCameraHandler g_testCameraHandler = {
        .SetMode = CamEmu_SetCameraMode,
        .GetMode = CamEmu_GetCameraMode,

        .ShootPhoto = CamEmu_Photography,
        .GetShootPhotoState = CamEmu_GetPhotographyState,

        .SetShootPhotoMode = CamEmu_SetPhotographyMode,
        .GetShootPhotoMode = CamEmu_GetPhotographyMode,

        .RecordVideo = CamEmu_SetRecording,
        .GetRecordVideoState = CamEmu_GetRecordingState,

        .GetSDCardState = CamEmu_GetSdcardParam,
        .FormatSDCard = CamEmu_FormatSdcard,

        //Exposure metering
        .isExposureMeteringSupported = 1,
        .SetMeteringMode = CamEmu_SetMeteringMode,
        .GetMeteringMode = CamEmu_GetMeteringMode,
        .SetSpotMetering = CamEmu_SetSpotMetering,
        .GetSpotMetering = CamEmu_GetSpotMetering,

        //focus
        .isAdjustableFocalPointSupported = 1,
        .SetFocusMode = CamEmu_SetFocusMode,
        .GetFocusMode = CamEmu_GetFocusMode,
        .SetFocusZone = CamEmu_SetFocusZone,
        .GetFocusZone = CamEmu_GetFocusZone,
        .SetFocusAssistantSettings = CamEmu_SetFocusAssistantSettings,
        .GetFocusAssistantSettings = CamEmu_GetFocusAssistantSettings,
        .GetFocusRingValueUpperBound = CamEmu_GetFocusRingValueUpperBound,
        .SetFocusRingValue = CamEmu_SetFocusRingValue,
        .GetFocusRingValue = CamEmu_GetFocusRingValue,

        //digital zoom
        .isDigitalZoomSupported = 0, //not support digital zoom
        .GetDigitalZoomSpec = NULL,  //if not support, callback function can be null
        .SetDigitalZoomFactor = NULL,
        .GetDigitalZoomFactor = NULL,

        //optical zoom
        .isOpticalZoomSupported = 1,
        .GetOpticalZoomSpec = CamEmu_GetOpticalZoomSpec,
        .SetOpticalZoomFocalLength = CamEmu_SetOpticalZoomFocalLength,
        .GetOpticalZoomFocalLength = CamEmu_GetOpticalZoomFocalLength,
        .GetOpticalZoomFactor = CamEmu_GetOpticalZoomFactor,
        .StartContinuousOpticalZoom = CamEmu_StartContinuousOpticalZoom,
        .StopContinuousOpticalZoom = CamEmu_StopContinuousOpticalZoom,
};

/****************** (C) COPYRIGHT DJI Innovations *****END OF FILE****/
