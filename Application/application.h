/**
 ******************************************************************************
 * @file    application.h
 * @version V1.3.0
 * @date    2018/09/19
 * @brief   This is the header file for "application.c".
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
#ifndef APPLICATION_H
#define APPLICATION_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "psdk_arch_sys.h"

/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if PSDK_ARCH_USE_OS
void RunIndicateTask(void const *parameter);
void PsdkTestTask(void const *parameter);
void ProcessPsdkRecTask(void const *parameter);
#else
void PsdkComInfSw(void);
void PsdkRunIndicate(void);
void PsdkMotorTest(void);
void PsdkBigLEDTest(void);
void PsdkProcessRec(void);
#endif

void application_init(void);

/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif //APPLICATION_H

/****************** (C) COPYRIGHT DJI Innovations *****END OF FILE****/

