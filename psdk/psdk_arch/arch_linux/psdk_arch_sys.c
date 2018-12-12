/**
 ******************************************************************************
 * @file    psdk_arch_sys.c
 * @version V0.0.0
 * @date    2017/8/25
 * @brief   This file provides PSDK system wrapper functions for linux.
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
E_PsdkStat PsdkSys_MutexNew(PSDK_MUTEX_T *mutex)
{
    int res;

    res = pthread_mutex_init(mutex, NULL);
    if (res != 0) {
        return PSDK_STAT_ERR;
    }

    return PSDK_STAT_OK;
}

E_PsdkStat PsdkSys_MutexDestroy(PSDK_MUTEX_T *mutex)
{
    PSDK_ASSERT(mutex != NULL);

    int res;

    res = pthread_mutex_destroy(mutex);
    if (res != 0) {
        return PSDK_STAT_ERR;
    }
    return PSDK_STAT_OK;
}

E_PsdkStat PsdkSys_MutexLock(PSDK_MUTEX_T *mutex)
{
    PSDK_ASSERT(mutex != NULL);

    int res;

    res = pthread_mutex_lock(mutex);
    if (res != 0) {
        return PSDK_STAT_ERR;
    }
    return PSDK_STAT_OK;
}

E_PsdkStat PsdkSys_MutexUnlock(PSDK_MUTEX_T *mutex)
{
    PSDK_ASSERT(mutex != NULL);

    int res = pthread_mutex_unlock(mutex);

    if (res != 0) {
        return PSDK_STAT_ERR;
    }
    return PSDK_STAT_OK;
}
#endif

/************************ (C) COPYRIGHT DJI Innovations *******END OF FILE******/