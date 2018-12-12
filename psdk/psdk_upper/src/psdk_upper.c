/**
 ******************************************************************************
 * @file    psdk_upper.c
 * @version V1.0.0
 * @date    2017/11/10
 * @brief   This file provides the API functions for establishing PSDK communication
 * and authorization.
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
#include "psdk_upper.h"
#include <string.h>
#include <psdk.h>
#include <psdk_cmdset_define/psdk_cmdset_payload_state.h>
#include <psdk_upper.h>
#include "psdk_cmdset.h"

/** @addtogroup PSDK
 * @{
 */

/** @defgroup PSDK_Upper PSDK Upper
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/** @defgroup Upper_Private_Variables Private Variables
 * @{
 */

///Payload SDK application information, please refer to ::T_PsdkUserInfo for details.
static T_PsdkUserInfo s_userInfo = {0};
///Payload SDK APP alias, plaese refer to ::T_PsdkUserFixSkyport for details.
static T_PsdkUserFixSkyport s_fixSkyport = {0};
///Supported SkyPort FW version for Payload SDK, please refer to ::T_PsdkUserCustomInfo for details.
static T_PsdkUserCustomInfo s_customInfo = {0};

/**
 * @}
 */

/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup Upper_Private_Functions Private Functions
 * @{
 */

/**
 * @brief Put a string to buffer.
 * @param pBuff Pointer to the buffer
 * @param str Pointer to the string.
 * @param maxStrLen Size of data to be copied.
 * @return Pointer to next address of buffer.
 */
static uint8_t *Str_PutStrToBuff(uint8_t *pBuff, char *str, uint32_t maxStrLen)
{
    uint32_t len;
    if (strlen(str) > maxStrLen) {
        len = maxStrLen;
    } else {
        len = strlen(str);
    }

    memcpy(pBuff, str, len);

    return (pBuff + len);
}

/**
 * @brief Calculate a key used for data transmission.
 * @param userInfo Pointer to user information, including APP name, APP ID, etc.
 * @param pKey Pointer to transmission key store buffer.
 * @param pKeyBitSize Pointer to key bit number store buffer.
 * @return PSDK function process state.
 */
static E_PsdkStat PsdkProtoUpper_CalTransferKey(const T_PsdkUserInfo *userInfo, uint8_t *pKey,
                                                uint16_t *pKeyBitSize)
{
    MD5_CTX md5Ctx;
    uint16_t md5InputLen = (uint16_t) (strlen(userInfo->APP_Name) + strlen(userInfo->APP_Id) +
                                       strlen(userInfo->APP_Key) + strlen(userInfo->DeveloperAccount));
    uint8_t *md5InputData = PSDK_MEM_MALLOC(md5InputLen);
    uint8_t *pCal = md5InputData;

    if (md5InputData == NULL) {
        return PSDK_STAT_ERR_ALLOC;
    }

    //calc key
    memcpy(pCal, userInfo->APP_Name, strlen(userInfo->APP_Name));
    pCal += strlen(userInfo->APP_Name);

    memcpy(pCal, userInfo->APP_Id, strlen(userInfo->APP_Id));
    pCal += strlen(userInfo->APP_Id);

    memcpy(pCal, userInfo->APP_Key, strlen(userInfo->APP_Key));
    pCal += strlen(userInfo->APP_Key);

    memcpy(pCal, userInfo->DeveloperAccount, strlen(userInfo->DeveloperAccount));
    pCal += strlen(userInfo->DeveloperAccount);

    md5_init(&md5Ctx);
    md5_update(&md5Ctx, md5InputData, pCal - md5InputData);
    md5_final(&md5Ctx, pKey);
    *pKeyBitSize = 128;

    PSDK_MEM_FREE(md5InputData);

    return PSDK_STAT_OK;
}

/**
 * @brief Payload identity verify.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
static E_PsdkStat PsdkPayloadStateCmd_IdentityVerify(struct _PsdkProt *protHandle,
                                                     const T_PsdkProtInfo *inProtInfo, const uint8_t *inProtData)
{
    T_LoadStateIdentityVerifyReq *pReq = (T_LoadStateIdentityVerifyReq *) inProtData;
    T_LoadStateIdentityVerifyAck ack;
    uint16_t ackLen = sizeof(T_LoadStateIdentityVerifyAck);
    uint8_t calBuf[33 + 17];
    uint8_t *pCal;
    MD5_CTX md5;

    if (strlen((const char *) pReq->random) <= 12) {
        ack.ackCode = PSDK_CMD_ACK_CODE_ERROR;
        goto out;
    }

    //key + random = md5
    pCal = calBuf;
    pCal = Str_PutStrToBuff(pCal, s_userInfo.APP_Key, strlen(s_userInfo.APP_Key));
    pCal = Str_PutStrToBuff(pCal, (char *) pReq->random, 16);

    md5_init(&md5);
    md5_update(&md5, calBuf, pCal - calBuf);
    md5_final(&md5, ack.md5);
    ack.ackCode = PSDK_CMD_ACK_CODE_OK;

    out:
    return PsdkProto_SendAckData(protHandle, inProtInfo, (uint8_t *) &ack, ackLen);
}

/**
 * @brief Handle PSDK version acquire command.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
static E_PsdkStat PsdkPayloadStateCmd_GetVersion(struct _PsdkProt *protHandle,
                                                 const T_PsdkProtInfo *inProtInfo, const uint8_t *inProtData)
{
    T_LoadStatePsdkVersionAck ack;
    uint16_t ackLen = sizeof(T_LoadStatePsdkVersionAck);

    ack.ackCode = PSDK_CMD_ACK_CODE_OK;

    ack.version.ver.verDebug = PSDK_VERSION_DEBUG;
    ack.version.ver.verModify = PSDK_VERSION_MODIFY;
    ack.version.ver.verMinor = PSDK_VERSION_MINOR;
    ack.version.ver.verMajor = PSDK_VERSION_MAJOR;

    return PsdkProto_SendAckData(protHandle, inProtInfo, (uint8_t *) &ack, ackLen);
}

/**
 * @brief Handle communication link hand-shake command.
 * @details The command is used for checking whether the communication link between SKYPORT and payload is normal.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
static E_PsdkStat PsdkPayloadStateCmd_LinkHandShake(struct _PsdkProt *protHandle,
                                                    const T_PsdkProtInfo *inProtInfo, const uint8_t *inProtData)
{
    T_LoadStateLinkHandShakeAck ack;
    uint16_t ackLen = (uint16_t) (inProtInfo->dataLen + 1);

    ack.ackCode = PSDK_CMD_ACK_CODE_OK;
    memcpy(ack.pingData, inProtData, inProtInfo->dataLen);

    return PsdkProto_SendAckData(protHandle, inProtInfo, (uint8_t *) &ack, ackLen);
}

/**
 * @brief Handle product information acquire command.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
static E_PsdkStat PsdkPayloadStateCmd_GetPayloadProductInfo(struct _PsdkProt *protHandle,
                                                            const T_PsdkProtInfo *inProtInfo, const uint8_t *inProtData)
{
    T_LoadStateGetProductInfoAck ack;
    uint16_t ackLen = sizeof(T_LoadStateGetProductInfoAck);

    ack.ackCode = PSDK_CMD_ACK_CODE_OK;
    memcpy(ack.productName, s_userInfo.APP_Name, PAYLOADSTATE_MAX_PRODUCT_NAME_SIZE);
    memcpy(ack.productID, s_userInfo.APP_Id, PAYLOADSTATE_MAX_PRODUCT_ID_SIZE);
    memcpy(ack.developerAccount, s_userInfo.DeveloperAccount, PAYLOADSTATE_MAX_DEV_ACCOUNT_SIZE);

    return PsdkProto_SendAckData(protHandle, inProtInfo, (uint8_t *) &ack, ackLen);
}

/**
 * @brief Handle upgrade SKYPORT version acquire command.
 * @details Send the fixed SKYPORT FW version to SKYPORT.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
static E_PsdkStat PsdkPayloadStateCmd_GetSkyportVersionInfo(struct _PsdkProt *protHandle,
                                                            const T_PsdkProtInfo *inProtInfo, const uint8_t *inProtData)
{
    T_LoadStateGetSkyportVersionAck ack;
    uint16_t ackLen = sizeof(T_LoadStateGetSkyportVersionAck);

    ack.version.ver.debugVer = s_fixSkyport.verDebug;
    ack.version.ver.modifyVer = s_fixSkyport.verModify;
    ack.version.ver.minorVer = s_fixSkyport.verMinor;
    ack.version.ver.majorVer = s_fixSkyport.verMajor;

    ack.ackCode = PSDK_CMD_ACK_CODE_OK;
    return PsdkProto_SendAckData(protHandle, inProtInfo, (uint8_t *) &ack, ackLen);
}

/**
 * @brief Handle payload product alias acquire command.
 * @param protHandle Pointer to PSDK protocol handle.
 * @param inProtInfo Pointer to PSDK protocol information of data package.
 * @param inProtData Pointer to data field of package.
 * @return PSDK function process state.
 */
static E_PsdkStat PsdkPayloadStateCmd_GetPayloadProductAlias(struct _PsdkProt *protHandle,
                                                             const T_PsdkProtInfo *inProtInfo, const uint8_t *inProtData)
{
    T_LoadStateGetProductAliasAck ack;
    uint16_t ackLen = sizeof(T_LoadStateGetProductAliasAck);

    ack.ackCode = PSDK_CMD_ACK_CODE_OK;
    memcpy((char *) ack.productName, s_customInfo.ProductAlias, PAYLOADSTATE_MAX_PRODUCT_NAME_SIZE);

    return PsdkProto_SendAckData(protHandle, inProtInfo, (uint8_t *) &ack, ackLen);
}

/**
 * @}
 */

/** @defgroup Upper_Private_Variables Private Variables
 * @{
 */

/**
 * @brief Payload state commands process function list.
 */
static const T_PsdkProtCmdItem s_payloadStateProtCmdList[] =
        {
                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_PAYLOAD_STATE, PSDK_PAYLOADSTATE_CMDID_IDENTITY_VERIFY, PsdkPayloadStateCmd_IdentityVerify),
                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_PAYLOAD_STATE, PSDK_PAYLOADSTATE_CMDID_SDK_VERSION, PsdkPayloadStateCmd_GetVersion),
                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_PAYLOAD_STATE, PSDK_PAYLOADSTATE_CMDID_LINK_HANDSHAKE, PsdkPayloadStateCmd_LinkHandShake),
                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_PAYLOAD_STATE, PSDK_PAYLOADSTATE_CMDID_PRODUCT_INFO, PsdkPayloadStateCmd_GetPayloadProductInfo),
                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_PAYLOAD_STATE, PSDK_PAYLOADSTATE_CMDID_FIX_SKYPORT_VERSION, PsdkPayloadStateCmd_GetSkyportVersionInfo),
                PSDK_PROT_CMD_ITEM(PSDK_CMDSET_PAYLOAD_STATE, PSDK_PAYLOADSTATE_CMDID_PRODUCT_ALIAS, PsdkPayloadStateCmd_GetPayloadProductAlias),

        };
/**
 * @}
 */

/* Exported functions --------------------------------------------------------*/

/** @defgroup Upper_Exported_Functions Exported Functions
 * @{
 */

/**
 * @brief Initialize the PSDK in top-level.
 * @details The function complete initializing load application information, calculating PSDK data transmission key,
 *           PSDK protocol initialization, and mount payload state command set command process functions.
 * @param psdkUpper Pointer to the top-level PSDK structure.
 * @param userInfo Pointer to the user information structure.
 * @return PSDK function process state.
 */
E_PsdkStat PsdkUpper_Init(T_PsdkUpper *psdkUpper, const T_PsdkUserInfo *userInfo)
{
    E_PsdkStat psdkStat;
    T_PsdkProtInitConf protInitConf;
    T_PsdkProtCmdSetHandle protCmdSetHandle;

    s_userInfo = *userInfo;
    memcpy(s_customInfo.ProductAlias, userInfo->APP_Name, PAYLOADSTATE_MAX_PRODUCT_NAME_SIZE);

    psdkStat = PsdkProtoUpper_CalTransferKey(&s_userInfo, protInitConf.protKey, &protInitConf.keyBitSize);
    if (psdkStat != PSDK_STAT_OK) {
        return psdkStat;
    }

    psdkStat = PsdkProto_Init(&(psdkUpper->protHandle), &protInitConf);
    if (psdkStat != PSDK_STAT_OK) {
        return psdkStat;
    }

    protCmdSetHandle.cmdSet = PSDK_CMDSET_PAYLOAD_STATE;
    protCmdSetHandle.cmdList = s_payloadStateProtCmdList;
    protCmdSetHandle.cmdCount = sizeof(s_payloadStateProtCmdList) / sizeof(T_PsdkProtCmdItem);

    psdkStat = PsdkProto_RegCmdSetHandler(&(psdkUpper->protHandle), &protCmdSetHandle);
    if (psdkStat != PSDK_STAT_OK) {
        return psdkStat;
    }

    return PSDK_STAT_OK;
}

/**
 * @brief Set the version of FW that you want your SkyPort adapter to stay on, regardless of FW upgrades.
 * @details Using this API, you can fix the SkyPort FW version that works best with your app. Future firmware upgrades
 * will ensure that your SkyPort stays on the version you fix using this API.
 * @param fixSkyport Pointer to the user fixSkyport structure.
 * @return PSDK function process state.
 */
E_PsdkStat PsdkUpper_SetFixVersion(const T_PsdkUserFixSkyport *fixSkyport)
{
    s_fixSkyport = *fixSkyport;

    return PSDK_STAT_OK;
}

/**
 * @brief Set a string (part of the customInfo parameter) that will serve as your product alias of the PSDK in top-level.
 * @param customInfo Pointer to the user customInfo structure.
 * @return PSDK function process state.
 */
E_PsdkStat PsdkUpper_SetProductAlias(const T_PsdkUserCustomInfo *customInfo)
{
    s_customInfo = *customInfo;

    return PSDK_STAT_OK;
}

/**
 * @brief Process the stream from PSDK port.
 * @param psdkUpper Pointer to the top level PSDK data structure.
 * @param pData Pointer to the buffer that stores the received bytes.
 * @param len The length of the received data.
 * @return PSDK function process state.
 */
E_PsdkStat PsdkUpper_ProcessReceiveData(T_PsdkUpper *psdkUpper, const uint8_t *pData, uint16_t len)
{
    return PsdkProto_ProcessReceiveData(&(psdkUpper->protHandle), pData, len);
}

/**
 * @brief Register the send function for PSDK, which is externally provided by the user.
 * @param psdkUpper Pointer to the top-level PSDK data structure.
 * @param sendCallbackFunc Pointer to the external sender function.
 * @return An enum that represents a status of PSDK.
 */
E_PsdkStat PsdkUpper_RegSendFunction(T_PsdkUpper *psdkUpper, PsdkSendCallbackFunc sendCallbackFunc)
{
    return PsdkProto_RegSendDataFunc(&(psdkUpper->protHandle), sendCallbackFunc);
}

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT DJI Innovations *******END OF FILE******/
