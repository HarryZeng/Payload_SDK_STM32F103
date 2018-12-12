/**
 ******************************************************************************
 * @file    main.c
 * @version V1.3.0
 * @date    2018/09/19
 * @brief   Main file.
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
#include <psdk.h>
#include "sys.h"
#include "application.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
#if PSDK_ARCH_USE_OS
osThreadId runIndicateTaskHandle;
osThreadId processRecDataTaskHandle;
osThreadId psdkTestTaskHandle;
#endif

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None.
  * @retval None.
  */
int main(void)
{
#if !PSDK_ARCH_USE_OS
    uint32_t tempTick = 0;
    uint32_t lastTick_runIndicate = 0;
    uint32_t lastTick_test = 0;
#endif

    /* Init */
    Sys_Init();

    application_init();

#if PSDK_ARCH_USE_OS
    /* definition of Threads  */
    osThreadDef(n_indicateTask, RunIndicateTask, osPriorityNormal, 0, 128);
    osThreadDef(n_psdkRecTask, ProcessPsdkRecTask, osPriorityNormal, 0, 1024);
    osThreadDef(n_psdkTestTask, PsdkTestTask, osPriorityAboveNormal, 0, 1024);

    /* Start threads */
    runIndicateTaskHandle = osThreadCreate(osThread(n_indicateTask), NULL);
    processRecDataTaskHandle = osThreadCreate(osThread(n_psdkRecTask), NULL);
    psdkTestTaskHandle = osThreadCreate(osThread(n_psdkTestTask), NULL);

    /* Start scheduler */
    osKernelStart();

    /*Taken by the scheduler */
    for (;;);
#else
    for(;;) {
        PsdkProcessRec();
        PsdkComInfSw();

        tempTick = Sys_GetTick();
        if((tempTick - lastTick_runIndicate) >= 500) {
            lastTick_runIndicate = tempTick;
            PsdkRunIndicate();
        }

        if((tempTick - lastTick_test) >= 1000) {
            lastTick_test = tempTick;
            PsdkTest();
        }
    }
#endif
}
