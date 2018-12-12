/**
 ******************************************************************************
 * @file    psdk_proto.h
 * @version V0.0.0
 * @date    2017/11/9
 * @brief   PSDK protocol related defines, structures and function declaration.
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
#ifndef PSDK_PROTO_H
#define PSDK_PROTO_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <psdk_typedef.h>
#include "psdk_proto_common.h"
#include "psdk_arch_sys.h"
#include "psdk_proto_parse.h"

#ifdef PAYLOAD_SDK_INTERNAL
#include <cmsis_os.h>
#endif

/* Exported constants --------------------------------------------------------*/
#define PSDK_PROT_MAX_SUPPORT_CMD_SET    16

/* Exported macros -----------------------------------------------------------*/
#define PSDK_PROT_CMD_ITEM(set, id, func) {.cmdSet = set, .cmdId = id, .pFunc = func}

/* Exported types ------------------------------------------------------------*/
//PSDK send data callback function type
typedef E_PsdkStat (*PsdkSendCallbackFunc)(const uint8_t *pSendData, uint16_t dataLen);

//PSDK protocol information of PSDK data package.
typedef struct _PsdkProtInfo {
    uint8_t packetType;
    uint8_t ackReq;
    uint8_t encType;
    uint16_t seqNum;
    uint8_t cmdSet;
    uint8_t cmdID;
    uint16_t dataLen;
} T_PsdkProtInfo;

struct _PsdkProt;

//The structure define PSDK protocol command item, including command set, command ID and command process function.
typedef struct _PsdkProtCmdItem {
    uint8_t cmdSet;
    uint8_t cmdId;
    E_PsdkStat (*pFunc)(struct _PsdkProt *protHandle, const T_PsdkProtInfo *inProtInfo, const uint8_t *inProtData);
} T_PsdkProtCmdItem;

//PSDK protocol command set handle structure, defining command set, command item and command count.
typedef struct {
    uint8_t cmdSet;
    const T_PsdkProtCmdItem *cmdList;
    uint16_t cmdCount;
} T_PsdkProtCmdSetHandle;

//PSDK protocol base configuration.
typedef struct _PsdkProtInitConf {
    uint8_t protKey[32];
    uint16_t keyBitSize; /*!< this value can be 128, 192, or 256. */
} T_PsdkProtInitConf;

//PSDK protocol handle structure.
typedef struct _PsdkProt {
    T_PsdkProtInitConf conf;

    //receive data process
    T_PsdkProtParse protParse;
    uint8_t protPlainDataBuf[PSDK_PROT_MAX_DATA_LEN];

    //send
    uint16_t sendSeqNum;

#if PSDK_ARCH_USE_OS
    PSDK_MUTEX_T mutexSend;
#endif

    uint8_t sendFrameBuf[PSDK_PROT_MAX_FRAME_LEN];

    //send callback
    PsdkSendCallbackFunc sendCallback;

    //cmd handle
    T_PsdkProtCmdSetHandle cmdSetHandleList[PSDK_PROT_MAX_SUPPORT_CMD_SET];
    uint16_t regCmdSetCount;

#ifdef PAYLOAD_SDK_INTERNAL
    uint8_t isWaitAck;
    T_PsdkProtInfo sendCmdInfo;

    T_PsdkProtInfo ackInfo;
    uint8_t ackData[PSDK_PROT_MAX_DATA_LEN];

    osSemaphoreId waitAckSemaphore;
    osMutexId sendGetAckMutex;
#endif

} T_PsdkProt;

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
E_PsdkStat PsdkProto_Init(T_PsdkProt *protHandle, const T_PsdkProtInitConf *conf);
E_PsdkStat PsdkProto_DeInit(T_PsdkProt *protHandle);

E_PsdkStat PsdkProto_ProcessReceiveData(T_PsdkProt *protHandle, const uint8_t *pData, uint16_t len);
E_PsdkStat PsdkProto_RegSendDataFunc(T_PsdkProt *protHandle, PsdkSendCallbackFunc callbackFunc);

uint16_t PsdkProt_GetCurrentSendSeq(T_PsdkProt *protHandle);
E_PsdkStat PsdkProto_RegCmdSetHandler(T_PsdkProt *protHandle, T_PsdkProtCmdSetHandle *cmdSetHandle);

E_PsdkStat PsdkProto_Send(T_PsdkProt *protHandle, const T_PsdkProtInfo *protInfo, const uint8_t *protData);
E_PsdkStat
PsdkProto_SendAckData(T_PsdkProt *protHandle, const T_PsdkProtInfo *cmdInfo, uint8_t *ackData, uint16_t ackDataLen);

#ifdef PAYLOAD_SDK_INTERNAL
E_PsdkStat PsdkProto_SendGetAck(T_PsdkProt *protHandle, const T_PsdkProtInfo *cmdInfo, const uint8_t *cmdData,
                                T_PsdkProtInfo *ackInfo, uint8_t *ackData, uint32_t timeout);
#endif

/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif //PSDK_PROTO_H

/************************ (C) COPYRIGHT DJI Innovations *******END OF FILE******/
