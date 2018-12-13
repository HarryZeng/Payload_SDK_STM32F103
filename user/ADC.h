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
#ifndef __ADC_H__
#define __ADC_H__

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Exported macros -----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

extern float ADC_value;

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
void ADCinit(void);
uint16_t Get_Adc(void);
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

#endif
