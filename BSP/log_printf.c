/**
 ******************************************************************************
 * @file    log_printf.c
 * @version V1.0.0
 * @date    2017/11/10
 * @brief   The file defines low level log print function.
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
#include <stdio.h>
#include "log_printf.h"
#include <string.h>
#include <stdarg.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

//log print initialization flag
static uint8_t isLogInit = 0;

/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/**
 * @brief Log print initialize.
 * @param None.
 * @return None.
 */
void LOG_Init(void)
{
    UART_Init(UART_NUM_3, 115200);
    isLogInit = 1;
}

/**
 * @brief Low level log print function.
 * @param fmt Pointer to format string.
 * @param ... Parameters remaining.
 * @return None.
 */
void UART_Printf(const char *fmt, ...)
{
    if (isLogInit) {
        char buffer[LOG_STR_LEN_MAX];
        va_list args;
        va_start (args, fmt);
        vsnprintf(buffer, sizeof(buffer), fmt, args);
        UART_Write(UART_NUM_3, (uint8_t *)buffer, (uint16_t)(strlen(buffer) + 1));
        va_end(args);
    }
}

/************************** (C) COPYRIGHT DJI Innovations************ END OF FILE ***/
