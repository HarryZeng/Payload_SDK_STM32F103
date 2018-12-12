/**
 ******************************************************************************
 * @file    flash.c
 * @version V1.0.0
 * @date    2017/11/10
 * @brief   The file defines flash operating functions, including read, write and erase flash etc.
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
#include "flash.h"
//#include "../STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_flash.h"
#include "stm32f10x_flash.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

//buffer used to store user parameters
static uint8_t s_paramBuffer[PARAM_FLASH_SIZE];

///* Exported variables --------------------------------------------------------*/
///* Private function prototypes -----------------------------------------------*/
///* Private functions ---------------------------------------------------------*/
//static uint16_t flash_get_sector_num(uint32_t addr)
//{
//    if (addr < ADDR_FLASH_SECTOR_1)
//        return FLASH_Sector_0;
//    else if (addr < ADDR_FLASH_SECTOR_2)
//        return FLASH_Sector_1;
//    else if (addr < ADDR_FLASH_SECTOR_3)
//        return FLASH_Sector_2;
//    else if (addr < ADDR_FLASH_SECTOR_4)
//        return FLASH_Sector_3;
//    else if (addr < ADDR_FLASH_SECTOR_5)
//        return FLASH_Sector_4;
//    else if (addr < ADDR_FLASH_SECTOR_6)
//        return FLASH_Sector_5;
//    else if (addr < ADDR_FLASH_SECTOR_7)
//        return FLASH_Sector_6;
//    else if (addr < ADDR_FLASH_SECTOR_8)
//        return FLASH_Sector_7;
//    else if (addr < ADDR_FLASH_SECTOR_9)
//        return FLASH_Sector_8;
//    else if (addr < ADDR_FLASH_SECTOR_10)
//        return FLASH_Sector_9;
//    else if (addr < ADDR_FLASH_SECTOR_11)
//        return FLASH_Sector_10;

//    return FLASH_Sector_11;
//}

//static uint32_t flash_read_word(uint32_t addr)
//{
//    return *(uint32_t *) addr;
//}

///* Exported functions --------------------------------------------------------*/
//INTERFACE int flash_read_data(uint32_t addr, uint8_t *buf, uint32_t len)
//{
//    memcpy(buf,(void*)addr,len);

//    return RTN_SUCCESS;
//}

//INTERFACE int flash_write_byte(uint32_t addr, uint8_t data)
//{
//    FLASH_Status status = FLASH_COMPLETE;

//    FLASH_Unlock();
//    /* Clear pending flags (if any) */
//    FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR
//        |FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);

//    status = FLASH_ProgramByte(addr, data);
//    if (status != FLASH_COMPLETE)
//    {
//        FLASH_Lock();
//        return RTN_FAILURE;
//    }
//    else
//    {
//        FLASH_Lock();
//        return RTN_SUCCESS;
//    }
//}

//INTERFACE int flash_write_word(uint32_t addr, uint32_t data)
//{
//    FLASH_Status status = FLASH_COMPLETE;

//    FLASH_Unlock();
//    /* Clear pending flags (if any) */
//    FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR
//        |FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);

//    status = FLASH_ProgramWord(addr, data);
//    if (status != FLASH_COMPLETE)
//    {
//        FLASH_Lock();
//        return RTN_FAILURE;
//    }
//    else
//    {
//        FLASH_Lock();
//        return RTN_SUCCESS;
//    }
//}

//INTERFACE int flash_wirte_data(uint32_t *addr, const uint32_t *data, uint16_t len)
//{
//    uint32_t target_addr = *addr;
//    uint16_t i = 0;
//    for (i = 0; i < len; i +=4)
//    {
//        flash_write_word(target_addr, *data);
//        if (*(uint32_t*)target_addr != *data)
//        {
//            return RTN_FAILURE;
//        }
//        target_addr += 4;
//        data += 1;
//    }
//    *addr = target_addr;

//    return RTN_SUCCESS;
//}

//INTERFACE int flash_erase(uint32_t startAddr,uint32_t endAddr)
//{
//    uint32_t addrErase;

//    FLASH_Status status=FLASH_COMPLETE;
//    //if(startAddr < FLASH_APP_START_ADDR || startAddr % 4 )
//    //    return RTN_FAILURE;
//    FLASH_Unlock();
//    /* Clear pending flags (if any) */
//    FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |
//    FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);

//    FLASH_DataCacheCmd(DISABLE);

//    addrErase = startAddr;
//    while(addrErase < endAddr)
//    {
//        if(flash_read_word(addrErase) != 0xffffffff)
//        {
//            status = FLASH_EraseSector(flash_get_sector_num(addrErase),VoltageRange_3);
//            if(status != FLASH_COMPLETE)
//            {
//                goto out_failure;
//            }
//        }
//        addrErase += 4;
//    }

//    FLASH_DataCacheCmd(ENABLE);
//    FLASH_Lock();
//    return RTN_SUCCESS;

//out_failure:
//    FLASH_DataCacheCmd(ENABLE);
//    FLASH_Lock();
//    return RTN_FAILURE;
//}

//INTERFACE int flash_read_user_settings(uint8_t * setting)
//{
//    int rtNum;

//    rtNum = flash_read_data(FLASH_SETTING_START_ADDR, setting, 4);

//    return rtNum;
//}

//INTERFACE int flash_write_user_settings(uint8_t *setting)
//{
//    uint16_t i;
//    uint32_t target_addr = FLASH_SETTING_START_ADDR;
//    uint32_t *data;

//    FLASH_Unlock();

//    FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |
//              FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);

//    memcpy(s_paramBuffer, (const void *)FLASH_SETTING_START_ADDR, PARAM_FLASH_SIZE);
//    flash_erase(FLASH_SETTING_START_ADDR, FLASH_SETTING_END_ADDR);
//    memcpy(s_paramBuffer, setting, 4);

//    data = (uint32_t*)s_paramBuffer;

//    for (i = 0; i < PARAM_FLASH_SIZE; i += 4)
//    {
//        flash_write_word(target_addr, *data);
//        if (*(uint32_t*)target_addr != *data)
//        {
//            FLASH_Lock();
//            return RTN_FAILURE;
//        }
//        target_addr += 4;
//        data += 1;
//    }
//    FLASH_Lock();

//    return RTN_SUCCESS;
//}

//INTERFACE uint32_t flash_read_settings(void)
//{
//    uint8_t settings[4];
//    uint32_t result = 0;

//    flash_read_user_settings(settings);
//    memcpy(&result, &settings, sizeof(settings));

//    return result;
//}

//INTERFACE void flash_wirte_settings(uint32_t setting)
//{
//    uint8_t temp[4];

//    memcpy(&temp, &setting, sizeof(setting));
//    flash_write_user_settings(temp);
//}
