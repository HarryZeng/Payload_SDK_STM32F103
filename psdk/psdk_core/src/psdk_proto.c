/**
 ******************************************************************************
 * @file    psdk_proto.c
 * @version V0.0.0
 * @date    2017/11/9
 * @brief   PSDK protocol data package handle functions definition.
 * @details The file includes functions which are used to initialize PSDK protocol handle structures,
 * process receiving data package, register command process functions and send PSDK data package, etc.
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
#include "psdk_proto.h"
#include "psdk_debug.h"
#include <string.h>
#include <psdk_upper.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
 * @brief Extract PSDK data packet information from PSDK frame.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param pFrame Pointer to PSDK frame.
 * @param pInfo Pointer to PSDK protocol information of data packet.
 * @param protData Pointer to data field of packet.
 * @return PSDK function process state.
 */
static E_PsdkStat
PsdkProto_FrameToInfoData(T_PsdkProt *protHandle, const uint8_t *pFrame, T_PsdkProtInfo *pInfo, uint8_t *protData)
{
    T_PsdkProtFrameHeader *pHeader = (T_PsdkProtFrameHeader *) pFrame;
    uint16_t frameDataLen = pHeader->lenAndVer.lenAndVer.length - sizeof(T_PsdkProtFrameHeader) - 4;

    pInfo->packetType = pHeader->cmdType.cmdType.packetType;
    pInfo->ackReq = pHeader->cmdType.cmdType.ackReq;
    pInfo->encType = pHeader->paddingAndEnc.paddingAndEnc.encType;

    pInfo->seqNum = pHeader->seqNum;

    pInfo->cmdSet = pHeader->cmdSet;
    pInfo->cmdID = pHeader->cmdID;
    pInfo->dataLen = frameDataLen - pHeader->paddingAndEnc.paddingAndEnc.padding;

    if (frameDataLen != 0) {
        if (pInfo->encType == PSDK_PROT_ENC_AES) {
            PsdkAes_Decrypt(PSDK_PROT_GET_FRAME_DATAPTR(pFrame), protData, frameDataLen, protHandle->conf.protKey,
                            protHandle->conf.keyBitSize);
        } else {
            memcpy(protData, PSDK_PROT_GET_FRAME_DATAPTR(pFrame), pInfo->dataLen);
        }
    }

    return PSDK_STAT_OK;
}

/**
 * @brief Load PSDK data packet information to PSDK frame.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param pFrame Pointer to PSDK frame.
 * @param pInfo Pointer to PSDK protocol information of data packet.
 * @param protData Pointer to data field of packet.
 * @return PSDK function process state.
 */
static E_PsdkStat
PsdkProto_InfoDataToFrame(T_PsdkProt *protHandle, uint8_t *pFrame, const T_PsdkProtInfo *pInfo, const uint8_t *protData)
{
    T_PsdkProtFrameHeader *pHeader = (T_PsdkProtFrameHeader *) pFrame;
    uint16_t packetDataLen, frameDataLen;
    uint8_t paddingLen;
    uint16_t frameLen;
    uint8_t *pTempData;

    packetDataLen = pInfo->dataLen;
    if (pInfo->encType == PSDK_PROT_ENC_NONE) {
        frameDataLen = packetDataLen;
        paddingLen = 0;
    } else if (pInfo->encType == PSDK_PROT_ENC_AES) {
        if (packetDataLen % 16 == 0) {
            frameDataLen = packetDataLen;
        } else {
            frameDataLen = (uint16_t) ((packetDataLen / 16 + 1) * 16);
        }
        paddingLen = (uint8_t) (frameDataLen - packetDataLen);
    } else {
        return PSDK_STAT_ERR;
    }

    frameLen = sizeof(T_PsdkProtFrameHeader) + frameDataLen + 4;

    pHeader->sof = PSDK_PROT_SOF;
    pHeader->lenAndVer.lenAndVer.length = frameLen;
    pHeader->lenAndVer.lenAndVer.version = PSDK_PROT_VERSION;
    pHeader->cmdType.cmdType.ackReq = pInfo->ackReq;
    pHeader->cmdType.cmdType.packetType = pInfo->packetType;
    pHeader->paddingAndEnc.paddingAndEnc.encType = pInfo->encType;
    pHeader->paddingAndEnc.paddingAndEnc.padding = paddingLen;
    pHeader->cmdSet = pInfo->cmdSet;
    pHeader->cmdID = pInfo->cmdID;
    pHeader->seqNum = pInfo->seqNum;
    pHeader->crc16 = PsdkCrc_Crc16(pFrame, sizeof(T_PsdkProtFrameHeader) - 2);

    if (frameDataLen != 0) {
        pTempData = PSDK_MEM_MALLOC(frameDataLen);
        if (!pTempData) {
            return PSDK_STAT_ERR_ALLOC;
        }

        memset(pTempData, 0, frameDataLen);
        memcpy(pTempData, protData, packetDataLen);
        if (pInfo->encType == PSDK_PROT_ENC_NONE) {
            memcpy(&pFrame[PSDK_PROT_DATA_OFFSET], pTempData, frameDataLen);
        } else if (pInfo->encType == PSDK_PROT_ENC_AES) {
            PsdkAes_Encrypt(pTempData, &pFrame[PSDK_PROT_DATA_OFFSET], frameDataLen, protHandle->conf.protKey,
                            protHandle->conf.keyBitSize);
        }
        PSDK_MEM_FREE(pTempData);
    }

    uint32_t crc32 = PsdkCrc_Crc32(pFrame, (uint16_t) (pHeader->lenAndVer.lenAndVer.length - 4));
    memcpy(&pFrame[pHeader->lenAndVer.lenAndVer.length - 4], (uint8_t *) &crc32, 4);

    return PSDK_STAT_OK;
}

/**
 * @brief Process PSDK data packet which has been parsed.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param protInfo Pointer to PSDK protocol information of data packet.
 * @param protData Pointer to data field of packet.
 * @return None.
 */
void PsdkProto_DealCmd(T_PsdkProt *protHandle, T_PsdkProtInfo *protInfo, uint8_t *protData)
{
    bool findHandleFlag;
    int i, j;

    findHandleFlag = false;

    for (i = 0; i < protHandle->regCmdSetCount; i++) {
        if (protHandle->cmdSetHandleList[i].cmdSet != (*protInfo).cmdSet) {
            continue;
        }

        for (j = 0; j < protHandle->cmdSetHandleList[i].cmdCount; j++) {
            if ((*protInfo).cmdID == protHandle->cmdSetHandleList[i].cmdList[j].cmdId
                && (*protInfo).cmdSet == protHandle->cmdSetHandleList[i].cmdList[j].cmdSet
                && protHandle->cmdSetHandleList[i].cmdList[j].pFunc != NULL) {

                findHandleFlag = true;

                //handle cmd
                if (protHandle->cmdSetHandleList[i].cmdList[j].pFunc(protHandle, protInfo,
                                                                     protData) != PSDK_STAT_OK) {
                    PSDK_LOG_WARN("Psdk Prot Handle: Cmd Failure, cmdset = 0x%02x, cmdid = 0x%02x",
                                  (*protInfo).cmdSet, (*protInfo).cmdID);
                }
                break;
            }
        }

        break;
    }

    if (findHandleFlag == false) {
        //unsupport cmd
        uint8_t ackCode = PSDK_CMD_ACK_CODE_UNSUPPORT;
        if (PsdkProto_SendAckData(protHandle, protInfo, &ackCode, 1) != PSDK_STAT_OK) {
            PSDK_LOG_WARN("Psdk Prot Handle: Send Ack Error!");
        }
    }
}

/**
 * @brief Process PSDK data packet which has not been parsed.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param pFrame Pointer to PSDK frame.
 * @return PSDK function process state.
 */
static E_PsdkStat PsdkProto_DealFrame(T_PsdkProt *protHandle, const uint8_t *pFrame)
{
    T_PsdkProtInfo protInfo;
    E_PsdkStat psdkStat;

    psdkStat = PsdkProto_FrameToInfoData(protHandle, pFrame, &protInfo, protHandle->protPlainDataBuf);
    if (psdkStat != PSDK_STAT_OK) {
        return psdkStat;
    }

    if (protInfo.packetType == PSDK_PROT_PACKET_TYPE_ACK) {
        //ack process
#ifdef PAYLOAD_SDK_INTERNAL
        if (protHandle->isWaitAck) {
            if (protInfo.cmdSet == protHandle->sendCmdInfo.cmdSet &&
                protInfo.cmdID == protHandle->sendCmdInfo.cmdID &&
                protInfo.seqNum == protHandle->sendCmdInfo.seqNum) {
                protHandle->ackInfo = protInfo;
                memcpy(protHandle->ackData, protHandle->protPlainDataBuf, protInfo.dataLen);
                osSemaphoreRelease(protHandle->waitAckSemaphore);
            }
        }
#endif

    } else if (protInfo.packetType == PSDK_PROT_PACKET_TYPE_CMD) {
        //cmd process
        PsdkProto_DealCmd(protHandle, &protInfo, protHandle->protPlainDataBuf);
    }

    return PSDK_STAT_OK;
}

/* Exported functions --------------------------------------------------------*/

/**
 * @brief PSDK protocol handle structure initialize.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param conf PSDK protocol related configuration.
 * @return PSDK function process state.
 */
E_PsdkStat PsdkProto_Init(T_PsdkProt *protHandle, const T_PsdkProtInitConf *conf)
{
#if PSDK_ARCH_USE_OS
    E_PsdkStat psdkStat;
#endif

    memcpy(&(protHandle->conf), conf, sizeof(T_PsdkProtInitConf));

    //receive
    PsdkProtParse_Init(&protHandle->protParse);
    memset(protHandle->protPlainDataBuf, 0x00, sizeof(protHandle->protPlainDataBuf));

    //send
    protHandle->sendSeqNum = 0;

#if PSDK_ARCH_USE_OS
    psdkStat = PsdkSys_MutexNew(&protHandle->mutexSend);
    if (psdkStat != PSDK_STAT_OK) {
        return psdkStat;
    }
#endif
    memset(protHandle->sendFrameBuf, 0x00, sizeof(protHandle->sendFrameBuf));

    protHandle->sendCallback = NULL;

    memset(protHandle->cmdSetHandleList, 0x00, sizeof(protHandle->cmdSetHandleList));
    protHandle->regCmdSetCount = 0;

#ifdef PAYLOAD_SDK_INTERNAL
    protHandle->isWaitAck = 0;

    osSemaphoreDef(WaitAckSem);
    protHandle->waitAckSemaphore = osSemaphoreCreate(osSemaphore(WaitAckSem), 1);
    if (protHandle->waitAckSemaphore == 0) {
        return PSDK_STAT_OK;
    }
    osSemaphoreWait(protHandle->waitAckSemaphore, osWaitForever);

    osMutexDef(SendGetAckMutex);
    protHandle->sendGetAckMutex = osMutexCreate(osMutex(SendGetAckMutex));
    if (protHandle->sendGetAckMutex == 0) {
        return PSDK_STAT_OK;
    }
#endif

    return PSDK_STAT_OK;
}

/**
 * @brief PSDK protocol handle structure deinitialize.
 * @param protHandle Pointer to PSDK protocol handle.
 * @return PSDK function process state.
 */
E_PsdkStat PsdkProto_DeInit(T_PsdkProt *protHandle)
{
#if PSDK_ARCH_USE_OS
    E_PsdkStat psdkStat;

    psdkStat = PsdkSys_MutexDestroy(&protHandle->mutexSend);
    if (psdkStat != PSDK_STAT_OK) {
        return psdkStat;
    }
#endif

#ifdef PAYLOAD_SDK_INTERNAL
    osSemaphoreDelete(protHandle->waitAckSemaphore);
    osMutexDelete(protHandle->sendGetAckMutex);
#endif

    return PSDK_STAT_OK;
}

/**
 * @brief Process received data from payload communication interface.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param pData Pointer to received data.
 * @param len Received data length.
 * @return PSDK function process state.
 */
E_PsdkStat PsdkProto_ProcessReceiveData(T_PsdkProt *protHandle, const uint8_t *pData, uint16_t len)
{
    int parseRes;
    uint8_t *pFrame;
    E_PsdkStat psdkStat;
    int i;

    for (i = 0; i < len; i++) {
        parseRes = PsdkProtParse_AddByte(&protHandle->protParse, pData[i], &pFrame);
        if (parseRes > 0) {
            //copy to tRec
            psdkStat = PsdkProto_DealFrame(protHandle, pFrame);
            if (psdkStat != PSDK_STAT_OK) {
                PSDK_LOG_WARN("Psdk Proto Deal : Error Deal Frame");
            }
        } else if (parseRes == -ERRC0DE_PSDK_PROT_PARSE_FRAME_LENGTH) {
            PSDK_LOG_WARN("Psdk Proto Deal : Error Frame Length");
        } else if (parseRes == -ERRCODE_PSDK_PROT_PARSE_CRC32) {
            PSDK_LOG_WARN("Psdk Proto Deal : Error Parse Crc32");
        } else if (parseRes == -ERRCODE_PSDK_PROT_PARSE_CRC16) {
            PSDK_LOG_WARN("Psdk Proto Deal : Error Parse Crc16");
        }
    }

    return PSDK_STAT_OK;
}

/**
 * @brief Register PSDK frame send callback function to PSDK protocol handle structure.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param callbackFunc Data send callback function.
 * @return PSDK function process state.
 */
E_PsdkStat PsdkProto_RegSendDataFunc(T_PsdkProt *protHandle, PsdkSendCallbackFunc callbackFunc)
{
    if (callbackFunc == NULL) {
        return PSDK_STAT_ERR_PARAM;
    }

    protHandle->sendCallback = callbackFunc;

    return PSDK_STAT_OK;
}

/**
 * @brief Get current sequence number of PSDK frame ot be sent.
 * @param protHandle Pointer to PSDK protocol handle.
 * @retval PSDK_STAT_ERR: Function execution error.
 *          not PSDK_STAT_ERR: PSDK frame sequence number requested.
 */
uint16_t PsdkProt_GetCurrentSendSeq(T_PsdkProt *protHandle)
{
    uint16_t seq;

#if PSDK_ARCH_USE_OS
    if (PsdkSys_MutexLock(&protHandle->mutexSend) != PSDK_STAT_OK) {
        return PSDK_STAT_ERR;
    }
#endif

    seq = protHandle->sendSeqNum;
    protHandle->sendSeqNum++;

#if PSDK_ARCH_USE_OS
    if (PsdkSys_MutexUnlock(&protHandle->mutexSend) != PSDK_STAT_OK) {
        return PSDK_STAT_ERR;
    }
#endif

    return seq;
}

/**
 * @brief Register PSDK command set handle structure to PSDK protocol handle structure.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param cmdSetHandle Pointer to PSDK command set handle structure.
 * @return PSDK function process state.
 */
E_PsdkStat PsdkProto_RegCmdSetHandler(T_PsdkProt *protHandle, T_PsdkProtCmdSetHandle *cmdSetHandle)
{
    int i;

    for (i = 0; i < protHandle->regCmdSetCount; i++) {
        if (protHandle->cmdSetHandleList[i].cmdSet == cmdSetHandle->cmdSet) {
            break;
        }
    }

    if (i == protHandle->regCmdSetCount) {
        if (protHandle->regCmdSetCount == PSDK_PROT_MAX_SUPPORT_CMD_SET) {
            return PSDK_STAT_ERR;
        } else {
            protHandle->cmdSetHandleList[i] = *cmdSetHandle;
            protHandle->regCmdSetCount++;
        }
    } else {
        protHandle->cmdSetHandleList[i] = *cmdSetHandle;
    }

    return PSDK_STAT_OK;
}

/**
 * @brief PSDK data send function according to protocol information and data to be sent.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param protInfo Pointer to PSDK protocol information of PSDK data packet.
 * @param protData Pointer to data to be sent.
 * @return PSDK function process state.
 */
E_PsdkStat PsdkProto_Send(T_PsdkProt *protHandle, const T_PsdkProtInfo *protInfo, const uint8_t *protData)
{
    E_PsdkStat psdkStat;

#if PSDK_ARCH_USE_OS
    if (PsdkSys_MutexLock(&protHandle->mutexSend) != PSDK_STAT_OK) {
        return PSDK_STAT_ERR;
    }
#endif

    psdkStat = PsdkProto_InfoDataToFrame(protHandle, protHandle->sendFrameBuf, protInfo, protData);
    if (psdkStat == PSDK_STAT_OK) {
        if (protHandle->sendCallback != NULL) {
            psdkStat = protHandle->sendCallback(protHandle->sendFrameBuf,
                                                PSDK_PROT_GET_FRAME_LEN(protHandle->sendFrameBuf));
        } else {
            psdkStat = PSDK_STAT_ERR;
        }
    }

#if PSDK_ARCH_USE_OS
    if (PsdkSys_MutexUnlock(&protHandle->mutexSend) != PSDK_STAT_OK) {
        return PSDK_STAT_ERR;
    }
#endif

    return psdkStat;
}

/**
 * @brief PSDK send ack data function.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param cmdInfo Pointer to PSDK protocol information of PSDK data packet.
 * @param ackData Pointer to ack data to be sent.
 * @param ackDataLen Ack data length.
 * @return PSDK function process state.
 */
E_PsdkStat PsdkProto_SendAckData(T_PsdkProt *protHandle, const T_PsdkProtInfo *cmdInfo, uint8_t *ackData, uint16_t ackDataLen)
{
    T_PsdkProtInfo ackProtInfo;

    ackProtInfo.packetType = PSDK_PROT_PACKET_TYPE_ACK;
    ackProtInfo.ackReq = PSDK_PROT_ACK_REQ_NONEED;
    ackProtInfo.encType = cmdInfo->encType;
    ackProtInfo.seqNum = cmdInfo->seqNum;
    ackProtInfo.cmdSet = cmdInfo->cmdSet;
    ackProtInfo.cmdID = cmdInfo->cmdID;
    ackProtInfo.dataLen = ackDataLen;

    return PsdkProto_Send(protHandle, &ackProtInfo, ackData);
}

#ifdef PAYLOAD_SDK_INTERNAL

/**
 * @brief PSDK send request data and get ack function.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param cmdInfo Pointer to PSDK protocol information of PSDK data packet.
 * @param cmdData Pointer to PSDK command request data.
 * @param ackInfo Pointer to PSDK ack data frame protocol information structure.
 * @param ackData Pointer to ack data to be sent.
 * @param timeout Max time used to wait PSDK ack.
 * @return PSDK function process state.
 */
E_PsdkStat PsdkProto_SendGetAck(T_PsdkProt *protHandle, const T_PsdkProtInfo *cmdInfo, const uint8_t *cmdData,
                                T_PsdkProtInfo *ackInfo, uint8_t *ackData, uint32_t timeout)
{
    E_PsdkStat psdkStat;

    psdkStat = PSDK_STAT_ERR;

    osMutexWait(protHandle->sendGetAckMutex, osWaitForever);
    protHandle->sendCmdInfo = *cmdInfo;
    protHandle->isWaitAck = 1;

    PsdkProto_Send(protHandle, cmdInfo, cmdData);
    if (osSemaphoreWait(protHandle->waitAckSemaphore, timeout) == osOK) {
        *ackInfo = protHandle->ackInfo;
        memcpy(ackData, protHandle->ackData, protHandle->ackInfo.dataLen);
        psdkStat = PSDK_STAT_OK;
    }
    protHandle->isWaitAck = 0;

    osMutexRelease(protHandle->sendGetAckMutex);
    return psdkStat;
}

#endif

/************************ (C) COPYRIGHT DJI Innovations *******END OF FILE******/
