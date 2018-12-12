/**
 *********************************************************************
 * @file    psdk_payload_camera.h
 * @version V1.0.0
 * @date    2017/11/10
 * @brief   This is the header file for "psdk_payload_camera.c", defining the
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
#ifndef PSDK_PAYLOAD_CAMERA_H
#define PSDK_PAYLOAD_CAMERA_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "psdk_upper.h"
#include "psdk_cmdset.h"

/** @addtogroup PSDK
 * @{
 */

/** @addtogroup PSDK_Camera
 * @{
 */

/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

/** @addtogroup Camera_Exported_Types
 * @{
 */

/** @defgroup Camera_Callback_Related Callback Related
 * @{
 */

/**
 * @brief Function list for handling camera commands.
 * @details This structure type is used to define a list that
 * includes all the callback functions related camera function:
 * 1. Camera base functions
 * 2. Exposure metering functions
 * 3. Focus functions
 * 4. Zoom functions
 */
typedef struct {
    //======== Camera Base function ==========//
    ///Set camera mode callback function.
    void (*SetMode)               (const T_PsdkCameraSetModeReq *req, T_PsdkCameraSetModeAck *ack);
    ///Get camera mode callback function.
    void (*GetMode)               (const T_PsdkCameraGetModeReq *req, T_PsdkCameraGetModeAck *ack);

    ///Shoot photo callback function.
    void (*ShootPhoto)                  (const T_PsdkCameraShootPhotoReq *req, T_PsdkCameraShootPhotoAck *ack);
    ///Get shoot photo state callback function.
    void (*GetShootPhotoState)          (const T_PsdkCameraGetShootPhotoStateReq *req, T_PsdkCameraGetShootPhotoStateAck *ack);

    ///Set shoot photo mode callback function.
    void (*SetShootPhotoMode)           (const T_PsdkCameraSetShootPhotoModeReq *req, T_PsdkCameraSetShootPhotoModeAck *ack);
    ///Get shoot photo mode callback function.
    void (*GetShootPhotoMode)           (const T_PsdkCameraGetShootPhotoModeReq *req, T_PsdkCameraGetShootPhotoModeAck *ack);

    ///Record video callback function.
    void (*RecordVideo)                 (const T_PsdkCameraRecordVideoReq *req, T_PsdkCameraRecordVideoAck *ack);
    ///Get record video state callback function.
    void (*GetRecordVideoState)         (const T_PsdkCameraGetRecordVideoStateReq *req, T_PsdkCameraGetRecordVideoStateAck *ack);

    ///Get SD card state callback function.
    void (*GetSDCardState)              (const T_PsdkCameraGetSDCardStateReq *req, T_PsdkCameraGetSDCardStateAck *ack);
    ///Format SD card callback function.
    void (*FormatSDCard)                (const T_PsdkCameraFormatSDCardReq *req, T_PsdkCameraFormatSDCardAck *ack);
    //===== End of Camera Base function =======//

    //========== Exposure Metering ============//
    ///Specifies whether load support exposure metering.
    uint8_t isExposureMeteringSupported;
    ///Set metering mode callback function.
    void (*SetMeteringMode)             (const T_PsdkCameraSetMeteringModeReq *req, T_PsdkCameraSetMeteringModeAck *ack);
    ///Get metering mode callback function.
    void (*GetMeteringMode)             (const T_PsdkCameraGetMeteringModeReq *req, T_PsdkCameraGetMeteringModeAck *ack);
    ///Set spot metering callback function.
    void (*SetSpotMetering)             (const T_PsdkCameraSetSpotMeteringReq *req, T_PsdkCameraSetSpotMeteringAck *ack);
    ///Get spot metering callback function.
    void (*GetSpotMetering)             (const T_PsdkCameraGetSpotMeteringReq *req, T_PsdkCameraGetSpotMeteringAck *ack);
    //========= End of Exposure Metering ======//

    //=============== Focus ===================//
    ///Specifies whether load support adjustable focal point.
    uint8_t isAdjustableFocalPointSupported;
    ///Set focus mode callback function.
    void (*SetFocusMode)                (const T_PsdkCameraSetFocusModeReq *req, T_PsdkCameraSetFocusModeAck *ack);
    ///Get focus mode callback function.
    void (*GetFocusMode)                (const T_PsdkCameraGetFocusModeReq *req, T_PsdkCameraGetFocusModeAck *ack);
    ///Set focus zone callback function.
    void (*SetFocusZone)                (const T_PsdkCameraSetFocusZoneReq *req, T_PsdkCameraSetFocusZoneAck *ack);
    ///Get focus zone callback function.
    void (*GetFocusZone)                (const T_PsdkCameraGetFocusZoneReq *req, T_PsdkCameraGetFocusZoneAck *ack);
    ///Set focus assistant settings callback function.
    void (*SetFocusAssistantSettings)   (const T_PsdkCameraSetFocusAssistantSettingsReq *req, T_PsdkCameraSetFocusAssistantSettingsAck *ack);
    ///Get focus assistant settings callback function.
    void (*GetFocusAssistantSettings)   (const T_PsdkCameraGetFocusAssistantSettingsReq *req, T_PsdkCameraGetFocusAssistantSettingsAck *ack);
    ///Get focus ring value upper bound callback function.
    void (*GetFocusRingValueUpperBound) (const T_PsdkCameraGetFocusRingValueUpperBoundReq *req, T_PsdkCameraGetFocusRingValueUpperBoundAck *ack);
    ///Set focus ring value callback function.
    void (*SetFocusRingValue)           (const T_PsdkCameraSetFocusRingValueReq *req, T_PsdkCameraSetFocusRingValueAck *ack);
    ///Get focus ring value callback function.
    void (*GetFocusRingValue)           (const T_PsdkCameraGetFocusRingValueReq *req, T_PsdkCameraGetFocusRingValueAck *ack);
    //============ End of Focus ===============//

    //=============== zoom ====================//
    ///Specifies whether load support digital zoom.
    uint8_t isDigitalZoomSupported;
    ///Get digital zoom specification callback function.
    void (*GetDigitalZoomSpec)          (const T_PsdkCameraGetDigitalZoomSpecReq *req, T_PsdkCameraGetDigitalZoomSpecAck *ack);
    ///Set digital zoom factor callback function.
    void (*SetDigitalZoomFactor)        (const T_PsdkCameraSetDigitalZoomFactorReq *req, T_PsdkCameraSetDigitalZoomFactorAck *ack);
    ///Get digital zoom factor callback function.
    void (*GetDigitalZoomFactor)        (const T_PsdkCameraGetDigitalZoomFactorReq *req, T_PsdkCameraGetDigitalZoomFactorAck *ack);

    uint8_t isOpticalZoomSupported;
    ///Get optical zoom specification callback function.
    void (*GetOpticalZoomSpec)          (const T_PsdkCameraGetOpticalZoomSpecReq *req, T_PsdkCameraGetOpticalZoomSpecAck *ack);
    ///Set optical zoom focal length callback function.
    void (*SetOpticalZoomFocalLength)   (const T_PsdkCameraSetOpticalZoomFocalLengthReq *req, T_PsdkCameraSetOpticalZoomFocalLengthAck *ack);
    ///Get optical zoom focal length callback function.
    void (*GetOpticalZoomFocalLength)   (const T_PsdkCameraGetOpticalZoomFocalLengthReq *req, T_PsdkCameraGetOpticalZoomFocalLengthAck *ack);
    ///Get optical zoom factor callback function.
    void (*GetOpticalZoomFactor)        (const T_PsdkCameraGetOpticalZoomFactorReq *req, T_PsdkCameraGetOpticalZoomFactorAck *ack);
    ///Start continuous optical zoom callback function.
    void (*StartContinuousOpticalZoom)  (const T_PsdkCameraStartContinuousOpticalZoomReq *req, T_PsdkCameraStartContinuousOpticalZoomAck *ack);
    ///Stop continuous optical zoom callback function.
    void (*StopContinuousOpticalZoom)   (const T_PsdkCameraStopContinuousOpticalZoomReq *req, T_PsdkCameraStopContinuousOpticalZoomAck *ack);
    //=========== End of zoom =================//
} T_PsdkCameraHandler;

/**
 * @}
 */

/**
 * @}
 */

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @addtogroup Camera_Exported_Functions
 * @{
 */

E_PsdkStat PsdkCamera_Init(T_PsdkUpper *psdkUpper, const T_PsdkCameraHandler *cameraHandler);

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

#endif //PSDK_PAYLOAD_CAMERA_H

/****************** (C) COPYRIGHT DJI Innovations *****END OF FILE****/
