/**
 ******************************************************************************
 * @file    sys.c
 * @version V1.0.0
 * @date    2017/11/10
 * @brief   The file defines some interface functions in system level.
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
#include "sys.h"
#include "stm32f10x_rcc.h"
#include "misc.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define TICK_MAX_DELAY      0xFFFFFFFFU

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
static __IO uint32_t uwTick;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static void Wrap_NVIC_SetPriority(IRQn_Type IRQn, uint32_t PreemptPriority, uint32_t SubPriority)
{
  uint32_t prioritygroup = 0x00U;
  
  prioritygroup = NVIC_GetPriorityGrouping();
  
  NVIC_SetPriority(IRQn, NVIC_EncodePriority(prioritygroup, PreemptPriority, SubPriority));
}

static void NVIC_Configuration(void)
{
//    /* Set the Vector Table base location at 0x08000000 */
//    /* 0x8000000 - 0x08004000 is bootloader */
//    NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0000);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    
    Wrap_NVIC_SetPriority(SVCall_IRQn, 0, 0);
    Wrap_NVIC_SetPriority(PendSV_IRQn, 15, 0);
    Wrap_NVIC_SetPriority(SysTick_IRQn, 15, 0);
}

static void SysTick_Configuration(void)
{
    RCC_ClocksTypeDef  rcc_clocks;
    uint32_t         cnts;

    RCC_GetClocksFreq(&rcc_clocks);

    cnts = (uint32_t)rcc_clocks.HCLK_Frequency / 1000;

    SysTick_Config(cnts);
}

/* Exported functions --------------------------------------------------------*/
void Sys_Init(void)
{
    NVIC_Configuration();
    SysTick_Configuration();
}

#if !PSDK_ARCH_USE_OS
void Sys_IncTick(void)
{
    uwTick++;
}

uint32_t Sys_GetTick(void)
{
    return uwTick;
}

void Sys_Delay(__IO uint32_t Delay)
{
    uint32_t tickstart = Sys_GetTick();
    uint32_t wait = Delay;

    /* Add a period to guarantee minimum wait */
    if (wait < TICK_MAX_DELAY) {
        wait++;
    }

    while((Sys_GetTick() - tickstart) < wait) {
    }
}
#endif
