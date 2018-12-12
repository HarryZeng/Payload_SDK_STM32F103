/**
 ******************************************************************************
 * @file    app_config.h
 * @version V1.3.0
 * @date    2018/09/19
 * @brief   The file define some load application related configurations.
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
#ifndef DEMO_RTOS_RTTHREAD_APP_CONFIG_H
#define DEMO_RTOS_RTTHREAD_APP_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define PSDK_CHANNEL_UART            0
#define PSDK_CHANNEL_CAN             1
#define PSDK_UART_REC_BUF_LEN       1024
#define PSDK_CAN_RX_REC_BUF_LEN     100

/* Exported macros -----------------------------------------------------------*/
#define PSDK_DEMO_CHANNEL_USE       PSDK_CHANNEL_UART
#define PSDK_UART_NUM                UART_NUM_2

/* Exported types ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif //DEMO_RTOS_RTTHREAD_APP_CONFIG_H

/************************ (C) COPYRIGHT DJI Innovations *******END OF FILE******/
