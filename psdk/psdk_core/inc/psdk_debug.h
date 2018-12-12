/**
 ******************************************************************************
 * @file    psdk_debug.h
 * @version V0.0.0
 * @date    2017/11/10
 * @brief   Defines and functions used to debug load application program.
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
#ifndef PSDK_DEBUG_H
#define PSDK_DEBUG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "psdk_typedef.h"
#include "psdk_arch_sys.h"

/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/

//debug config
#define PSDK_USE_LOG            PSDK_TRUE

//assert config
#define PSDK_USE_FULL_ASSERT    PSDK_TRUE

//Define various grade log information print.
#if PSDK_USE_LOG
#ifndef PSDK_DBG_PRINTF
#error "if use psdk log , you need define PSDK_DBG_PRINTF function macro !!!"
#endif
#define PSDK_LOG(fmt, ...)          PSDK_DBG_PRINTF(fmt, ##__VA_ARGS__)
#define PSDK_LOG_DEBUG(fmt, ...)    PSDK_DBG_PRINTF("[Debug]" fmt, ##__VA_ARGS__)
#define PSDK_LOG_INFO(fmt, ...)     PSDK_DBG_PRINTF("[Info]" fmt, ##__VA_ARGS__)
#define PSDK_LOG_WARN(fmt, ...)     PSDK_DBG_PRINTF("[Warn]" fmt, ##__VA_ARGS__)
#define PSDK_LOG_ERROR(fmt, ...)    PSDK_DBG_PRINTF("[Error]" fmt, ##__VA_ARGS__)
#else
#define PSDK_LOG(fmt,...)
#define PSDK_LOG_DEBUG(fmt,...)
#define PSDK_LOG_INFO(fmt,...)
#define PSDK_LOG_WARN(fmt,...)
#define PSDK_LOG_ERROR(fmt,...)
#endif

/* Exported types ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#if PSDK_USE_FULL_ASSERT
void PsdkDebug_AssertFailed(uint8_t *file, uint32_t line);

#define PSDK_ASSERT(expr)                                               \
    if(!(expr)) {                                                       \
        PsdkDebug_AssertFailed((uint8_t *)__FILE__, __LINE__);          \
    }
#else
#define PSDK_ASSERT(expr) ((void)0)
#endif

/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif //PSDK_DEBUG_H

/************************ (C) COPYRIGHT DJI Innovations *******END OF FILE******/
