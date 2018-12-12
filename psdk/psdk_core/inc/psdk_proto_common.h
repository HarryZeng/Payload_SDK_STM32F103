/**
 ******************************************************************************
 * @file    psdk_proto_common.h
 * @version V0.0.0
 * @date    2017/8/10
 * @brief   This file use to define PSDK protocol frame.
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
#ifndef PSDK_PROTO_COMMON_H
#define PSDK_PROTO_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <psdk_typedef.h>

/* Exported constants --------------------------------------------------------*/
//PSDK data packet initial byte, fixed as 0xAA
#define PSDK_PROT_SOF                   0xAA

//PSDK protocol version
#define PSDK_PROT_VERSION               0

//data packet type define
#define PSDK_PROT_PACKET_TYPE_CMD       0
#define PSDK_PROT_PACKET_TYPE_ACK       1

//ack request type define
#define PSDK_PROT_ACK_REQ_NONEED        0
#define PSDK_PROT_ACK_REQ_AFTER_EXE     1


//enc type define
#define PSDK_PROT_ENC_NONE              0
#define PSDK_PROT_ENC_AES               1

//PSDK data packet data field address offset relative to first byte of data packet
#define PSDK_PROT_DATA_OFFSET           12

//PSDK protocol data packet data field max length
#define PSDK_PROT_MAX_DATA_LEN          256

/* Exported macros -----------------------------------------------------------*/
#define PSDK_PROT_MAX_FRAME_LEN         (sizeof(T_PsdkProtFrameHeader) + PSDK_PROT_MAX_DATA_LEN + 4)
#define PSDK_PROT_MIN_FRAME_LEN         (sizeof(T_PsdkProtFrameHeader) + 4)

//frame function
#define PSDK_PROT_GET_FRAME_LEN(frame)      (((T_PsdkProtFrameHeader *) frame)->lenAndVer.lenAndVer.length)
#define PSDK_PROT_GET_FRAME_CRC32(frame)    (((uint8_t *) frame + ((T_PsdkProtFrameHeader *) frame)->lenAndVer.lenAndVer.length - 4))
#define PSDK_PROT_GET_FRAME_DATAPTR(frame)  (frame + sizeof(T_PsdkProtFrameHeader))

/* Exported types ------------------------------------------------------------*/
#pragma pack(1)

//frame = frameheader + framedata + crc32
//SDK protocol frame header structure.
typedef struct _PsdkProtFrameHeader {
    uint8_t sof;

    union {
        struct {
            uint16_t length     : 10;
            uint16_t version    : 6;
        } lenAndVer;
        uint16_t infoData;
    } lenAndVer;

    union {
        struct {
            uint8_t ackReq      : 5;
            uint8_t packetType  : 1;
            uint8_t reserved    : 2;
        } cmdType;
        uint8_t infoData;
    } cmdType;

    union {
        struct {
            uint8_t padding     : 5;
            uint8_t encType     : 3;
        } paddingAndEnc;
        uint8_t infoData;
    } paddingAndEnc;

    uint8_t reserve;

    uint8_t cmdSet;
    uint8_t cmdID;

    uint16_t seqNum;
    uint16_t crc16;
} T_PsdkProtFrameHeader;

#pragma pack()

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif //PSDK_PROTO_COMMON_H

/************************ (C) COPYRIGHT DJI Innovations *******END OF FILE******/
