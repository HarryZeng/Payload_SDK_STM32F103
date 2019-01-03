/**
 ******************************************************************************
 * @file    test_payload_gimbal_emu.c
 * @version V1.3.0
 * @date    2018/09/19
 * @brief   The file define PSDK gimbal command callback functions for demo board.
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
#include <psdk_cmdset_define/psdk_cmdset_gimbal.h>
#include "test_payload_gimbal_emu.h"
#include "led_button_switch.h"
#include "communicate.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

//gimbal mode
static uint8_t gimbalMode = PSDK_GIMBAL_GIMBAL_MODE_YAW_FOLLOW;

//reach yaw, roll, pitch axis limit angle
static uint8_t isYawLimit = 0;
static uint8_t isRollLimit = 0;
static uint8_t isPitchLimit = 0;

//pitch, roll, yaw axis angle
static int16_t pitch = 0;
static int16_t roll = 0;
static int16_t yaw = 0;

//pitch, roll, yaw axis angle speed
static int16_t pitchSpeed = 0;
static int16_t rollSpeed = 0;
static int16_t yawSpeed = 0;

//pitch, roll, yaw axis angle limit (unit: 0.1degree)
static const int16_t pitchMaxLimit = 300;
static const int16_t pitchMinLimit = -900;
static const int16_t rollMaxLimit = 450;
static const int16_t rollMinLimit = -450;
static const int16_t yawMaxLimit = 900;
static const int16_t yawMinLimit = -900;

/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/**
 * @brief Get gimbal parameters callback function.
 * @param req Command request structure, please refer to ::T_PsdkGimbalGetGimbalStateReq for details.
 * @param ack Command ack structure, please refer to ::T_PsdkGimbalGetGimbalStateAck for details.
 * @return None.
 */
void GimbalEmu_GetGimbalParam(const T_PsdkGimbalGetGimbalStateReq *req, T_PsdkGimbalGetGimbalStateAck *ack)
{
    //PSDK_LOG_DEBUG("Get Gimbal Param");

    //get gimbal param
    ack->gimbalMode = gimbalMode;
    ack->isMountedUpwards = 0;

    pitch += pitchSpeed * 0.1;
    roll += rollSpeed * 0.1;
    yaw += yawSpeed * 0.1;

    pitchSpeed = 0;
    rollSpeed = 0;
    yawSpeed = 0;

    pitch = pitch > pitchMaxLimit? pitchMaxLimit: pitch;
    pitch = pitch < pitchMinLimit? pitchMinLimit: pitch;
    roll = roll > rollMaxLimit? rollMaxLimit: roll;
    roll = roll < rollMinLimit? rollMinLimit: roll;
    yaw = yaw > yawMaxLimit? yawMaxLimit: yaw;
    yaw = yaw < yawMinLimit? yawMinLimit: yaw;

    if(pitch == pitchMaxLimit || pitch == pitchMinLimit) {
        isPitchLimit = 1;
    }
    if(roll == rollMaxLimit || roll == rollMinLimit) {
        isRollLimit = 1;
    }
    if(yaw == yawMaxLimit || yaw == yawMinLimit) {
        isYawLimit = 1;
    }

    ack->isPitchLimit = isPitchLimit;
    ack->isRollLimit = isRollLimit;
    ack->isYawLimit = isYawLimit;

    ack->pitch = pitch;
    ack->roll = roll;
    ack->yaw = yaw;

    //ack code
    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

/**
 * @brief Set gimbal mode callback function.
 * @param req Command request structure, please refer to ::T_PsdkGimbalSetGimbalModeReq for details.
 * @param ack Command ack structure, please refer to ::T_PsdkGimbalSetGimbalModeAck for details.
 * @return None.
 */
void GimbalEmu_SetGimbalMode(const T_PsdkGimbalSetGimbalModeReq *req, T_PsdkGimbalSetGimbalModeAck *ack)
{
    PSDK_LOG_DEBUG("Set Gimbal Mode");

    gimbalMode = req->gimbalMode;

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

/**
 * @brief Control gimbal return head callback function.
 * @param req Command request structure, please refer to ::T_PsdkGimbalReturnHeadReq for details.
 * @param ack Command ack structure, please refer to ::T_PsdkGimbalReturnHeadAck for details.
 * @return None.
 */
void GimbalEmu_ReturnHead(const T_PsdkGimbalReturnHeadReq *req, T_PsdkGimbalReturnHeadAck *ack)
{
    PSDK_LOG_DEBUG("Return Head");

    pitch = 0;
    roll = 0;
    yaw = 0;

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

/**
 * @brief Control gimbal speed callback function.
 * @param req Command request structure, please refer to ::T_PsdkGimbalControlSpeedReq for details.
 * @param ack Command ack structure, please refer to ::T_PsdkGimbalControlSpeedAck for details.
 * @return None.
 */
void GimbalEmu_ControlSpeed(const T_PsdkGimbalControlSpeedReq *req, T_PsdkGimbalControlSpeedAck *ack)
{
    PSDK_LOG_DEBUG("Control Speed  ");

    if (req->ctrlFlag == GIMBAL_ACTION) {
				
//        pitchSpeed = req->pitchSpeed;
//        rollSpeed = req->rollSpeed;
//        yawSpeed = req->yawSpeed;
			
        pitchSpeed = ((req->pitchSpeed*5)/18)+1500;
        rollSpeed = req->rollSpeed;
        yawSpeed = ((req->yawSpeed*5)/18)+1500;				
			
				
				PSDK_LOG_DEBUG("pitchSpeed:%4d  rollSpeed:%4d  yawSpeed:%4d",pitchSpeed,rollSpeed,yawSpeed);
				USART_TX_BUF[2] = pitchSpeed%256;
				USART_TX_BUF[3] = pitchSpeed/256;
				
				USART_TX_BUF[4] = rollSpeed%256;
				USART_TX_BUF[5] = rollSpeed/256;
				
				USART_TX_BUF[6] = yawSpeed%256;
				USART_TX_BUF[7] = yawSpeed/256;
			
    } else {
        pitchSpeed = 0;
        rollSpeed = 0;
        yawSpeed = 0;
				USART_TX_BUF[2] = 0xdc;
				USART_TX_BUF[3] = 0x05;
				
				USART_TX_BUF[4] = 0xdc;
				USART_TX_BUF[5] = 0x05;
				
				USART_TX_BUF[6] = 0xdc;
				USART_TX_BUF[7] = 0x05;
    }
		//PSDK_LOG_DEBUG("pitchSpeed:%4d  rollSpeed:%4d  yawSpeed:%4d",pitchSpeed,rollSpeed,yawSpeed);

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

/**
 * @brief Start gimbal calibration callback function.
 * @param req Command request structure, please refer to ::T_PsdkGimbalStartCalibrationReq for details.
 * @param ack Command ack structure, please refer to ::T_PsdkGimbalStartCalibrationAck for details.
 * @return None.
 */
void GimbalEmu_StartCalibration(const T_PsdkGimbalStartCalibrationReq *req, T_PsdkGimbalStartCalibrationAck *ack)
{
    PSDK_LOG_DEBUG("Gimbal Start Calibration");

    ack->ackCode = PSDK_CMD_ACK_CODE_OK;
}

//gimbal command callback function list
const T_PsdkGimbalHandler g_testGimbalHandler = {
        .GetGimbalState = GimbalEmu_GetGimbalParam,
        .SetGimbalMode = GimbalEmu_SetGimbalMode,
        .ReturnHead = GimbalEmu_ReturnHead,
        .ControlSpeed = GimbalEmu_ControlSpeed,
        .StartCalibration = GimbalEmu_StartCalibration,
};

/****************** (C) COPYRIGHT DJI Innovations *****END OF FILE****/
