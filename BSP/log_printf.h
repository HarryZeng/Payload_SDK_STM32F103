/**
 ******************************************************************************
 * @file    log_printf.h
 * @version V1.0.0
 * @date    2017/11/10
 * @brief   This is the header file for "log_printf.c".
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
#ifndef __LOG_PRINTF_H
#define __LOG_PRINTF_H

/* Includes ------------------------------------------------------------------*/
#include <dji_typedef.h>
#include "uart.h"

/* Exported constants --------------------------------------------------------*/
#define LOG_STR_LEN_MAX             128

/* Exported macros -----------------------------------------------------------*/
extern void UART_Printf(const char *fmt, ...);

#define LOG(fmt, ...)       UART_Printf("[%s]" fmt "\r\n",__FUNCTION__,##__VA_ARGS__)
#define LOG_DEBUG(fmt, ...) UART_Printf("[Debug][%s]" fmt "\r\n", __FUNCTION__, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...)  UART_Printf("[INFO][%s]" fmt "\r\n", __FUNCTION__, ##__VA_ARGS__)
#define LOG_WARN(fmt, ...)  UART_Printf("[WARN][%s]" fmt "\r\n", __FUNCTION__, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) UART_Printf("[ERROR][%s]" fmt "\r\n", __FUNCTION__, ##__VA_ARGS__)

/* Exported types ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void LOG_Init(void);

#endif

/************************** (C) COPYRIGHT DJI Innovations************ END OF FILE ***/
