/**
 ******************************************************************************
 * @file    psdk_proto_parse.c
 * @version V0.0.0
 * @date    2017/11/9
 * @brief   PSDK protocol data package parse functions definition.
 * @details The file includes PSDK protocol data package parse structures initialize and data package parse functions, etc.
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
#include <psdk_proto_parse.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
 * @brief Process operating of PSDK frame parse error occurring.
 * @param protParse Pointer to PSDK frame parse structure.
 * @return None.
 */
static inline void PsdkProtParse_ErrorProcess(T_PsdkProtParse *protParse)
{
    protParse->parseIndex = 0;
}

/**
 * @brief Reset PSDK frame structure.
 * @param protParse Pointer to PSDK frame parse structure.
 * @return None.
 */
static inline void PsdkProtParse_Clear(T_PsdkProtParse *protParse)
{
    protParse->parseIndex = 0;
}

/* Exported functions --------------------------------------------------------*/

/**
 * @brief Initialize PSDK frame structure.
 * @param protParse Pointer to PSDK frame parse structure.
 * @return None.
 */
void PsdkProtParse_Init(T_PsdkProtParse *protParse)
{
    protParse->parseIndex = 0;
}

/**
 * @brief parse one byte
 * @param protParse protoParse Handler
 * @param byteData one byte data
 * @param pParseFrame if parse success, *pParseFrame point to the parse frame buffer
 * @return if return value > 0, parse success, return the frameLen of frame;
 *         if return value < 0, parse error, return -ErrorCode, ErrorCode @ref PsdkProtParse_ErrorCode.
 */
int PsdkProtParse_AddByte(T_PsdkProtParse *protParse, uint8_t byteData, uint8_t **pParseFrame)
{
    uint16_t frameLen;
    uint16_t frameVer;

    //find SOF
    if (protParse->parseIndex == 0) {
        if (byteData != PSDK_PROT_SOF) {
            return -ERRCODE_PSDK_PROT_PARSE_NO_FRAME;
        }
    }

    protParse->parseBuffer[protParse->parseIndex] = byteData;
    protParse->parseIndex++;

    if (protParse->parseIndex >= 3) {
        frameLen = ((T_PsdkProtFrameHeader *) (protParse->parseBuffer))->lenAndVer.lenAndVer.length;
        frameVer = ((T_PsdkProtFrameHeader *) (protParse->parseBuffer))->lenAndVer.lenAndVer.version;

        if (frameLen < PSDK_PROT_MIN_FRAME_LEN || frameLen > PSDK_PROT_MAX_FRAME_LEN || frameVer != 0) {
            PsdkProtParse_ErrorProcess(protParse);
            return -ERRC0DE_PSDK_PROT_PARSE_FRAME_LENGTH;
        }

        if (protParse->parseIndex == sizeof(T_PsdkProtFrameHeader)) {
            uint16_t calCrc16;
            calCrc16 = PsdkCrc_Crc16(protParse->parseBuffer, sizeof(T_PsdkProtFrameHeader) - 2);
            if (((T_PsdkProtFrameHeader *) (protParse->parseBuffer))->crc16 != calCrc16) {
                PsdkProtParse_ErrorProcess(protParse);
                return -ERRCODE_PSDK_PROT_PARSE_CRC16;
            }
        }

        if (protParse->parseIndex == frameLen) {
            uint32_t calCrc32;
            calCrc32 = PsdkCrc_Crc32(protParse->parseBuffer, (uint16_t) (frameLen - 4));
            if (*(uint32_t *) PSDK_PROT_GET_FRAME_CRC32(protParse->parseBuffer) != calCrc32) {
                PsdkProtParse_ErrorProcess(protParse);
                return -ERRCODE_PSDK_PROT_PARSE_CRC32;
            } else {
                *pParseFrame = protParse->parseBuffer;
                PsdkProtParse_Clear(protParse);
                return frameLen;
            }
        }

        if (protParse->parseIndex > frameLen) {
            PsdkProtParse_ErrorProcess(protParse);
            return -ERRC0DE_PSDK_PROT_PARSE_FRAME_LENGTH;
        }
    }

    return -ERRCODE_PSDK_PROT_PARSE_NO_FRAME;
}

/************************ (C) COPYRIGHT DJI Innovations *******END OF FILE******/
