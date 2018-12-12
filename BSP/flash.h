/**
 ******************************************************************************
 * @file    flash.h
 * @version V1.0.0
 * @date    2017/11/10
 * @brief   This is the header file for "flash.c".
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
/* Includes ------------------------------------------------------------------*/
#include "stdint.h"
#include <string.h>
#include "stm32f10x.h"
#include "stm32f10x_flash.h"
#include "stm32f10x_gpio.h"
#include "dji_typedef.h"

/* Exported constants --------------------------------------------------------*/

#define FLASH_SIZE                     (0x100000)  /* //flash size:1024 KBytes */

//flash sector address
#define ADDR_FLASH_SECTOR_0            ((uint32_t)0x08000000)    //sector 0 start address, 16 Kbytes
#define ADDR_FLASH_SECTOR_1            ((uint32_t)0x08004000)    //sector 1 start address, 16 Kbytes
#define ADDR_FLASH_SECTOR_2            ((uint32_t)0x08008000)    //sector 2 start address, 16 Kbytes
#define ADDR_FLASH_SECTOR_3            ((uint32_t)0x0800C000)    //sector 3 start address, 16 Kbytes
#define ADDR_FLASH_SECTOR_4            ((uint32_t)0x08010000)    //sector 4 start address, 64 Kbytes
#define ADDR_FLASH_SECTOR_5            ((uint32_t)0x08020000)    //sector 5 start address, 128 Kbytes
#define ADDR_FLASH_SECTOR_6            ((uint32_t)0x08040000)    //sector 6 start address, 128 Kbytes
#define ADDR_FLASH_SECTOR_7            ((uint32_t)0x08060000)    //sector 7 start address, 128 Kbytes
#define ADDR_FLASH_SECTOR_8            ((uint32_t)0x08080000)    //sector 8 start address, 128 Kbytes
#define ADDR_FLASH_SECTOR_9            ((uint32_t)0x080A0000)    //sector 9 start address, 128 Kbytes
#define ADDR_FLASH_SECTOR_10           ((uint32_t)0x080C0000)    //sector 10 start address,128 Kbytes
#define ADDR_FLASH_SECTOR_11           ((uint32_t)0x080E0000)    //sector 11 start address,128 Kbytes

#define FLASH_SETTING_START_ADDR       ADDR_FLASH_SECTOR_10
#define FLASH_SETTING_END_ADDR         (ADDR_FLASH_SECTOR_11 - 1)

#define PARAM_FLASH_SIZE               2048
#define FLASH_IMAGE_SIZE               (FLASH_APP_END_ADDR - FLASH_APP_START_ADDR)

/* Exported macros -----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

INTERFACE int flash_read_data(uint32_t addr, uint8_t *buf, uint32_t len);
INTERFACE int flash_write_byte(uint32_t addr, uint8_t data);
INTERFACE int flash_write_word(uint32_t addr, uint32_t data);
INTERFACE int flash_wirte_data(uint32_t *addr, const uint32_t *data, uint16_t len);

INTERFACE int flash_read_user_settings(uint8_t * setting);
INTERFACE int flash_write_user_settings(uint8_t *setting);
INTERFACE int flash_erase(uint32_t startAddr,uint32_t endAddr);

INTERFACE uint32_t flash_read_settings(void);
INTERFACE void flash_wirte_settings(uint32_t setting);

/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
