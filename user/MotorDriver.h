/**
 ******************************************************************************
 * @file    uart.h
 * @version V1.0.0
 * @date    2017/11/10
 * @brief   This is the header file for "uart.c".
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
#ifndef __MORTODRIVER_H__
#define __MORTODRIVER_H__

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"


extern uint8_t  task_Run_flag;
extern uint8_t  Motor_Run_flag;
extern uint8_t  Motor_Direction_flag; //0 -> -, 1->+

/* Exported macros -----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

#define Motor_R_RCC    RCC_APB2Periph_GPIOA
#define Motor_R_PORT   GPIOA
#define Motor_R_PIN    GPIO_Pin_8

#define Motor_L_RCC    RCC_APB2Periph_GPIOA
#define Motor_L_PORT   GPIOA
#define Motor_L_PIN    GPIO_Pin_9


/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void TurnOFFMotro(void);
void TurnONMotro(void);
void MotorDriverGPIO_Init(void);
void TIM4_init(void);
void MotorControlFunc(void);
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

#endif
