/**
 ******************************************************************************
 * @file    psdk_typedef.h
 * @version V0.0.0
 * @date    2017/11/9
 * @brief   PSDK type define file.
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
#ifndef PSDK_TYPEDEF_H
#define PSDK_TYPEDEF_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/* Exported constants --------------------------------------------------------*/
#define PSDK_TRUE       1
#define PSDK_FALSE      0

/* Exported macros -----------------------------------------------------------*/
#define PSDK_EMPTY_STRUCT    uint8_t empty;

/* Exported types ------------------------------------------------------------*/

//float type define
typedef double  psdk_f64_t;
typedef float   psdk_f32_t;

//boolean type define
typedef uint8_t psdk_bool;

//function process state type define
typedef enum {
    PSDK_STAT_OK                 = 0,
    PSDK_STAT_ERR_ALLOC          = 1,
    PSDK_STAT_ERR_TIMEOUT        = 2,
    PSDK_STAT_ERR_NOT_FOUND      = 3,
    PSDK_STAT_ERR_OUT_OF_RANGE   = 4,
    PSDK_STAT_ERR_PARAM          = 5,
    PSDK_STAT_NO_NEED_ACK        = 6,
    PSDK_STAT_SYS_ERR = 7,

    PSDK_STAT_ERR                = 0xFF,
}E_PsdkStat;

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

//define compiler specific symbols
#if defined (__ICCARM__)
#elif defined (__CC_ARM)
#pragma anon_unions
#elif defined (__GNUC__)
#elif defined (__TASKING__)
#endif

#ifdef __cplusplus
}
#endif

#endif //PSDK_TYPEDEF_H
