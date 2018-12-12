/**
 ********************************************************************
 * @file    psdk_payload_camera.c
 * @version V1.0.0
 * @date    2017/11/10
 * @brief   This file provides the API functions for handling the camera
 * commands from the mobile app (ground) via PSDK port.
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

/* Includes ------------------------------------------------------------------*/
#include <psdk_ack_code.h>
#include <psdk.h>
#include <psdk_cmdset_define/psdk_cmdset_camera.h>

/** @addtogroup PSDK
 * @{
 */

/** @defgroup PSDK_Camera PSDK Camera
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/** @defgroup Camera_Private_Macro Private Macro
 * @{
 */

/**
 * @brief Macro used to define camera command process function.
 */
#define MODLE_FUNC_CAMCMD(name) \
static E_PsdkStat \
CameraCmd_##name(struct _PsdkProt *protHandle, const T_PsdkProtInfo *inProtInfo, const uint8_t *inProtData)\
{\
    T_PsdkCamera##name##Ack ack;\
    ack.ackCode = PSDK_CMD_ACK_CODE_UNSUPPORT;\
    if (s_cameraHandler.name != NULL) {\
        s_cameraHandler.name((const T_PsdkCamera##name##Req *) inProtData, &ack);\
    }\
    PsdkProto_SendAckData(protHandle, inProtInfo, (uint8_t *) &ack, sizeof(T_PsdkCamera##name##Ack));\
    return PSDK_STAT_OK;\
}

/**
 * @brief Function name macro.
 */
#define CAMCMD(name)    CameraCmd_##name

/**
 * @}
 */

/* Private variables ---------------------------------------------------------*/

/** @defgroup Camera_Private_Variables Private Variables
 * @{
 */

/** @defgroup P_Variables_Camera_Related Camera Related
 * @{
 */

///camera command set support state
static uint8_t s_isSupportCamera = 0;

/**
 * @}
 */

/** @defgroup C_P_Variables_Callback_Related Callback Related
 * @{
 */

///camera command callback function list
static T_PsdkCameraHandler s_cameraHandler = {0};

/**
 * @}
 */

/**
 * @}
 */

/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup Camera_Private_Functions Private functions
 * @{
 */

/**
 * @brief Handle set camera work mode command.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
MODLE_FUNC_CAMCMD(SetMode)

/**
 * @brief Handle get camera work mode command.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
MODLE_FUNC_CAMCMD(GetMode)

/**
 * @brief Handle shoot photo command.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
MODLE_FUNC_CAMCMD(ShootPhoto)

/**
 * @brief Handle get shoot photo state command.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
MODLE_FUNC_CAMCMD(GetShootPhotoState)

/**
 * @brief Handle set shoot photo mode command.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
MODLE_FUNC_CAMCMD(SetShootPhotoMode)

/**
 * @brief Handle get shoot photo mode command.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
MODLE_FUNC_CAMCMD(GetShootPhotoMode)

/**
 * @brief Handle record video command.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
MODLE_FUNC_CAMCMD(RecordVideo)

/**
 * @brief Handle get record video state command.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
MODLE_FUNC_CAMCMD(GetRecordVideoState)

/**
 * @brief Handle get SD card state command.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
MODLE_FUNC_CAMCMD(GetSDCardState)

/**
 * @brief Handle format SD card command.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
MODLE_FUNC_CAMCMD(FormatSDCard)

/**
 * @brief Handle set metering mode command.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
MODLE_FUNC_CAMCMD(SetMeteringMode)

/**
 * @brief Handle get metering mode command.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
MODLE_FUNC_CAMCMD(GetMeteringMode)

/**
 * @brief Handle set spot metering parameters command.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
MODLE_FUNC_CAMCMD(SetSpotMetering)

/**
 * @brief Handle get spot metering parameters command.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
MODLE_FUNC_CAMCMD(GetSpotMetering)

/**
 * @brief Handle set focus mode command.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
MODLE_FUNC_CAMCMD(SetFocusMode)

/**
 * @brief Handle get focus mode command.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
MODLE_FUNC_CAMCMD(GetFocusMode)

/**
 * @brief Handle set focus zone command.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
MODLE_FUNC_CAMCMD(SetFocusZone)

/**
 * @brief Handle get focus zone command.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
MODLE_FUNC_CAMCMD(GetFocusZone)

//zoom
/**
 * @brief Handle get digital zoom specification command.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
MODLE_FUNC_CAMCMD(GetDigitalZoomSpec)

/**
 * @brief Handle set digital zoom factor command.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
MODLE_FUNC_CAMCMD(SetDigitalZoomFactor)

/**
 * @brief Handle get digital zoom factor command.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
MODLE_FUNC_CAMCMD(GetDigitalZoomFactor)

/**
 * @brief Handle Get Optical Zoom specification command.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
MODLE_FUNC_CAMCMD(GetOpticalZoomSpec)

/**
 * @brief Handle Set Optical Zoom Focal Length command.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
MODLE_FUNC_CAMCMD(SetOpticalZoomFocalLength)

/**
 * @brief Handle get Optical Zoom Focal Length command.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
MODLE_FUNC_CAMCMD(GetOpticalZoomFocalLength)

/**
 * @brief Handle Get Optical Zoom Factor command.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
MODLE_FUNC_CAMCMD(GetOpticalZoomFactor)

/**
 * @brief Handle Start Continuous Optical Zoom command.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
MODLE_FUNC_CAMCMD(StartContinuousOpticalZoom)

/**
 * @brief Handle Stop Continuous Optical Zoom command.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
MODLE_FUNC_CAMCMD(StopContinuousOpticalZoom)

/**
 * @brief Handle Set Focus Assistant Setting command.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
MODLE_FUNC_CAMCMD(SetFocusAssistantSettings)

/**
 * @brief Handle get Focus Assistant Setting command.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
MODLE_FUNC_CAMCMD(GetFocusAssistantSettings)

/**
 * @brief Handle Get Focus Ring Value Upper Bound command.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
MODLE_FUNC_CAMCMD(GetFocusRingValueUpperBound)

/**
 * @brief Handle Set Focus Ring Value command.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
MODLE_FUNC_CAMCMD(SetFocusRingValue)

/**
 * @brief Handle Get Focus Ring Value command.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
MODLE_FUNC_CAMCMD(GetFocusRingValue)

//support state
/**
 * @brief Handle Get Camera Command Set Support State command.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
static E_PsdkStat
CameraCmd_SupportState(struct _PsdkProt *protHandle, const T_PsdkProtInfo *inProtInfo, const uint8_t *inProtData)
{
    T_PsdkCameraSupportStateAck ack;
    ack.ackCode = PSDK_CMD_ACK_CODE_OK;
    ack.isCameraCmdSetSupport = s_isSupportCamera;
    ack.isOpticalZoomSupported = s_cameraHandler.isOpticalZoomSupported;
    ack.isDigitalZoomSupported = s_cameraHandler.isDigitalZoomSupported;
    ack.isAdjustableFocalPointSupported = s_cameraHandler.isAdjustableFocalPointSupported;
    ack.isExposureMeteringSupported = s_cameraHandler.isExposureMeteringSupported;

    PsdkProto_SendAckData(protHandle, inProtInfo, (uint8_t *) &ack, sizeof(T_PsdkCameraSupportStateAck));

    return PSDK_STAT_OK;
}

/**
 * @}
 */

/** @addtogroup Camera_Private_Variables
 * @{
 */

/** @addtogroup P_Variables_Camera_Related
 * @{
 */

/**
 * @brief Camera commands process function list.
 */
static const T_PsdkProtCmdItem s_PayloadCameraCmdList[] =
        {
                //support state
                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_SUPPORT_STATE, CAMCMD(SupportState)),

                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_SET_MODE, CAMCMD(SetMode)),
                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_GET_MODE, CAMCMD(GetMode)),

                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_SHOOT_PHOTO, CAMCMD(ShootPhoto)),
                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_GET_SHOOT_PHOTO_STATE, CAMCMD(GetShootPhotoState)),

                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_SET_SHOOT_PHOTO_MODE, CAMCMD(SetShootPhotoMode)),
                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_GET_SHOOT_PHOTO_MODE, CAMCMD(GetShootPhotoMode)),

                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_RECORD_VIDEO, CAMCMD(RecordVideo)),
                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_GET_RECORD_VIDEO_STATE, CAMCMD(GetRecordVideoState)),

                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_GET_SDCARD_PARAM, CAMCMD(GetSDCardState)),
                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_FORMAT_SDCARD, CAMCMD(FormatSDCard)),

                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_SET_METERING_MODE, CAMCMD(SetMeteringMode)),
                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_GET_METERING_MODE, CAMCMD(GetMeteringMode)),

                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_SET_SPOT_METERING, CAMCMD(SetSpotMetering)),
                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_GET_SPOT_METERING, CAMCMD(GetSpotMetering)),

                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_SET_FOCUS_MODE, CAMCMD(SetFocusMode)),
                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_GET_FOCUS_MODE, CAMCMD(GetFocusMode)),

                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_SET_FOCUS_ZONE, CAMCMD(SetFocusZone)),
                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_GET_FOCUS_ZONE, CAMCMD(GetFocusZone)),
                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_SET_FOCUS_ASSISTANT_SETTING, CAMCMD(SetFocusAssistantSettings)),
                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_GET_FOCUS_ASSISTANT_SETTING, CAMCMD(GetFocusAssistantSettings)),
                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_GET_FOCUS_RING_VALUE_UPPER_BOUND, CAMCMD(GetFocusRingValueUpperBound)),
                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_SET_FOCUS_RING_VALUE, CAMCMD(SetFocusRingValue)),
                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_GET_FOCUS_RING_VALUE, CAMCMD(GetFocusRingValue)),

                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_GET_DIGITALZOOM_SPEC, CAMCMD(GetDigitalZoomSpec)),
                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_SET_DIGTALZOOM_FACTOR, CAMCMD(SetDigitalZoomFactor)),
                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_GET_DIGTALZOOM_FACTOR, CAMCMD(GetDigitalZoomFactor)),

                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_GET_OPTICALZOOM_SPEC, CAMCMD(GetOpticalZoomSpec)),
                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_SET_OPTICALZOOM_FOCAL_LENGTH, CAMCMD(SetOpticalZoomFocalLength)),
                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_GET_OPTICALZOOM_FOCAL_LENGTH, CAMCMD(GetOpticalZoomFocalLength)),
                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_GET_OPTICALZOOM_FACTOR, CAMCMD(GetOpticalZoomFactor)),
                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_START_CONTINUOUS_OPTICAL_ZOOM, CAMCMD(StartContinuousOpticalZoom)),
                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_CAMERA, PSDK_CAMERA_CMD_ID_STOP_CONTINUOUS_OPTICAL_ZOOM, CAMCMD(StopContinuousOpticalZoom)),
        };

/**
 * @}
 */

/**
 * @}
 */

/* Exported functions --------------------------------------------------------*/

/** @defgroup Camera_Exported_Functions Exported Functions
 * @{
 */

/**
 * @brief Initialize PSDK camera commands handling.
 * @details Initialise camera command support state and mount camera command process functions
 *            and register camera command set callback functions.
 * @param psdkUpper Pointer to the top level PSDK structure.
 * @param cameraHandler Pointer to camera command set callback function list.
 * @return PSDK function process state.
 */
E_PsdkStat PsdkCamera_Init(T_PsdkUpper *psdkUpper, const T_PsdkCameraHandler *cameraHandler)
{
    T_PsdkProtCmdSetHandle cmdSetHandle;

    s_cameraHandler = *cameraHandler;

    cmdSetHandle.cmdSet = PSDK_CMDSET_CAMERA;
    cmdSetHandle.cmdList = s_PayloadCameraCmdList;
    cmdSetHandle.cmdCount = sizeof(s_PayloadCameraCmdList) / sizeof(T_PsdkProtCmdItem);

    //support camera
    s_isSupportCamera = 1;

    return PsdkProto_RegCmdSetHandler(&(psdkUpper->protHandle), &cmdSetHandle);
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

/****************** (C) COPYRIGHT DJI Innovations *****END OF FILE****/
