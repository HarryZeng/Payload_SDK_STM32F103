/**
 ******************************************************************************
 * @file    psdk_crc.h
 * @version V0.0.0
 * @date    2017/11/10
 * @brief   CRC related defines and functions used by PSDK protocol.
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
#ifndef PSDK_CRC_H
#define PSDK_CRC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "psdk_typedef.h"

/* Exported constants --------------------------------------------------------*/
#define PSDK_CRC_POLY_8     0x31
#define PSDK_CRC_POLY_16    0x1021
#define PSDK_CRC_POLY_32    0x4C11DB7

#define PSDK_CRC_START_8    0x3D
#define PSDK_CRC_START_16   0x3FDE
#define PSDK_CRC_START_32   0xFFFFFFFF

/* Exported macros -----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
uint8_t PsdkCrc_Crc8(uint8_t const *pIn, uint16_t len);
uint16_t PsdkCrc_Crc16(uint8_t const *pIn, uint16_t len);
uint32_t PsdkCrc_Crc32(uint8_t const *pIn, uint16_t len);

/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif //PSDK_CRC_H

/************************ (C) COPYRIGHT DJI Innovations *******END OF FILE******/

