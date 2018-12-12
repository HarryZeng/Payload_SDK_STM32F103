/**
 ******************************************************************************
 * @file    psdk_arch_sys.h
 * @version V1.0.0
 * @date    2017/08/10
 * @brief   This file is a template containing the PSDK system wrapper function prototypes.
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
#ifndef PSDK_ARCH_SYS_H
#define PSDK_ARCH_SYS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "psdk_typedef.h"

/** @addtogroup PSDK
 * @{
 */

/** @addtogroup PSDK_Platform_Wrapper
 * @{
 */

/* Exported constants --------------------------------------------------------*/

/** @defgroup Exported_Constants Exported Constants
 * @{
 */

#define PSDK_ARCH_USE_OS            1   /*!< Specifies whether user's application use operating system;
                                               1 represents use operating system, 0 represents not use operating system. */

/**
 * @}
 */

/* Exported macros -----------------------------------------------------------*/

/** @defgroup Exported_Macros Exported Macros
 * @{
 */

/** @defgroup DBG_Printf_Function Log Print Function
 * @{
 */

/**
 * @brief Set printf function for log.
 * @note If operating system is used, the function must be thread safe.
 */
#define PSDK_DBG_PRINTF             printf

/**
 * @}
 */

/** @defgroup Memory_Handle_Function Memory Handle Function
 * @{
 */

/**
 * @brief Set memory malloc function.
 * @note If operating system is used, the function must be thread safe.
 */
#define PSDK_MEM_MALLOC             malloc

/**
 * @brief Set memory free function.
 * @note If operating system is used, the function must be thread safe.
 */
#define PSDK_MEM_FREE               free

/**
 * @}
 */

/** @defgroup Mutex_ID_Type Mutex ID Type
 * @{
 */

#if PSDK_ARCH_USE_OS
#define PSDK_MUTEX_T                uint32_t    /*!< Specifies mutex ID data type. */
#endif

/**
 * @}
 */

/**
 * @}
 */

/* Exported types ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @defgroup Exported_Functions Exported Functions
 * @{
 */

#if PSDK_ARCH_USE_OS
E_PsdkStat PsdkSys_MutexNew(PSDK_MUTEX_T *mutex);
E_PsdkStat PsdkSys_MutexDestroy(PSDK_MUTEX_T *mutex);
E_PsdkStat PsdkSys_MutexLock(PSDK_MUTEX_T *mutex);
E_PsdkStat PsdkSys_MutexUnlock(PSDK_MUTEX_T *mutex);
#endif

/**
 * @}
 */

/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif //PSDK_ARCH_SYS_H

/************************ (C) COPYRIGHT DJI Innovations *******END OF FILE******/
