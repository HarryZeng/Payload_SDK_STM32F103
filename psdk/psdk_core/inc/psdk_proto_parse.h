/**
 ******************************************************************************
 * @file    psdk_proto_parse.h
 * @version V0.0.0
 * @date    2017/11/9
 * @brief   PSDK protocol parse related defines and function declaration.
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
#ifndef PSDK_PROTO_PARSE_H
#define PSDK_PROTO_PARSE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "psdk_proto_common.h"

/* Exported constants --------------------------------------------------------*/

/** @defgroup PsdkProtParse_ErrorCode
 * @brief PSDK protocol data packet parse error type define.
 * @{
 */

#define ERRCODE_PSDK_PROT_PARSE_NO_FRAME         1
#define ERRC0DE_PSDK_PROT_PARSE_FRAME_LENGTH     2
#define ERRCODE_PSDK_PROT_PARSE_CRC16            3
#define ERRCODE_PSDK_PROT_PARSE_CRC32            4

/**
 * @}
 */

/* Exported macros -----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

//The structure is used for PSDK protocol data packet parse.
typedef struct {
    uint8_t parseBuffer[PSDK_PROT_MAX_FRAME_LEN];
    uint16_t parseIndex;
} T_PsdkProtParse;

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
void PsdkProtParse_Init(T_PsdkProtParse *protParse);
int PsdkProtParse_AddByte(T_PsdkProtParse *protParse, uint8_t byteData, uint8_t **pParseFrame);

/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif //PSDK_PROTO_PARSE_H

/************************ (C) COPYRIGHT DJI Innovations *******END OF FILE******/
