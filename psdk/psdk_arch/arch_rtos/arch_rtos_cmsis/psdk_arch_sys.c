/**
 ******************************************************************************
 * @file    psdk_arch_sys.c
 * @version V0.0.0
 * @date    2017/8/25
 * @brief   
 * This file provides the PSDK wrapper functions for inter-thread communication
 * and resource sharing with mutexes under FreeRTOS and CMSIS-RTOS.
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
#include "psdk_arch_sys.h"
#include "psdk_debug.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

#if PSDK_ARCH_USE_OS

/**
 * @brief Declare the mutex container, initialize the mutex, and
 * create mutex ID.
 * @param mutex:  pointer to the created mutex ID.
 * @return an enum that represents a status of PSDK
 */
E_PsdkStat PsdkSys_MutexNew(PSDK_MUTEX_T *mutex)
{
    osMutexDef(PSDK_MUTEX);

    *mutex = osMutexCreate(osMutex(PSDK_MUTEX));
    if (*mutex == NULL) {
        return PSDK_STAT_ERR;
    }

    return PSDK_STAT_OK;
}

/**
 * @brief Delete the created mutex.
 * @param mutex:  pointer to the created mutex ID.
 * @return an enum that represents a status of PSDK
 */
E_PsdkStat PsdkSys_MutexDestroy(PSDK_MUTEX_T *mutex)
{
    if (osMutexDelete(*mutex) != osOK) {
        return PSDK_STAT_ERR;
    }

    return PSDK_STAT_OK;
}

/**
 * @brief Acquire and lock the mutex when peripheral access is required
 * @param mutex:  pointer to the created mutex ID.
 * @return an enum that represents a status of PSDK
 */
E_PsdkStat PsdkSys_MutexLock(PSDK_MUTEX_T *mutex)
{
    if (osMutexWait(*mutex, osWaitForever) != osOK) {
        return PSDK_STAT_ERR;
    }

    return PSDK_STAT_OK;
}

/**
 * @brief Unlock and release the mutex, when done with the peripheral access.
 * @param mutex:  pointer to the created mutex ID.
 * @return an enum that represents a status of PSDK
 */
E_PsdkStat PsdkSys_MutexUnlock(PSDK_MUTEX_T *mutex)
{
    if (osMutexRelease(*mutex) != osOK) {
        return PSDK_STAT_ERR;
    }

    return PSDK_STAT_OK;
}
#endif

/************************ (C) COPYRIGHT DJI Innovations *******END OF FILE******/
