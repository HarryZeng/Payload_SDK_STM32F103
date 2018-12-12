/**
 ******************************************************************************
 * @file    psdk_cmdset_payload_state.h
 * @version V1.0.0
 * @date    2017/08/10
 * @brief   This file defines the payload state command set.
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
#ifndef PSDK_CMDSET_PAYLOAD_STATE_H
#define PSDK_CMDSET_PAYLOAD_STATE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <psdk_typedef.h>

/** @addtogroup PSDK
 * @{
 */

/** @addtogroup PSDK_Upper
 * @{
 */

/* Exported constants --------------------------------------------------------*/

/** @addtogroup Upper_Exported_Constants
 * @{
 */

/** @defgroup Payload_State_Related Payload State Related
 * @{
 */

#define PAYLOADSTATE_MAX_PINGDATA_SIZE          32  /*!< Specifies PING command request data max size. */
#define PAYLOADSTATE_MAX_PRODUCT_NAME_SIZE     32  /*!< Specifies product name max size. */
#define PAYLOADSTATE_MAX_PRODUCT_ID_SIZE       16  /*!< Specifies product ID max size. */
#define PAYLOADSTATE_MAX_DEV_ACCOUNT_SIZE      64  /*!< Specifies developer account max size. */

/**
 * @}
 */

/**
 * @}
 */

/* Exported macros -----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

/** @defgroup Upper_Exported_Types Exported Types
 * @{
 */

#pragma pack(1)

/**
 * @brief Payload State Command ID
 */
typedef enum {
    PSDK_PAYLOADSTATE_CMDID_IDENTITY_VERIFY = 0x01,     /*!< identity verify command */
    PSDK_PAYLOADSTATE_CMDID_SDK_VERSION = 0x02,         /*!< acquire PSDK version command */
    PSDK_PAYLOADSTATE_CMDID_LINK_HANDSHAKE = 0x03,      /*!< communication link hand-shake command */
    PSDK_PAYLOADSTATE_CMDID_PRODUCT_INFO = 0x04,        /*!< acquire PSDK product information command */
    PSDK_PAYLOADSTATE_CMDID_FIX_SKYPORT_VERSION = 0x05, /*!< acquire support version of skyport for PSDK command */
    PSDK_PAYLOADSTATE_CMDID_PRODUCT_ALIAS = 0x06,       /*!< acquire PSDK product alias command */
} E_PsdkPayLoadStateCmd;

// PSDK_PAYLOADSTATE_CMDID_IDENTITY_VERIFY
/**
 * @brief Identity verify command request data structure.
 */
typedef struct {
    uint8_t random[16]; /*!< Random character string. */
} T_LoadStateIdentityVerifyReq;

/**
 * @brief Identity verify command ack data structure.
 */
typedef struct {
    uint8_t ackCode;    /*!< Specifies PSDK command ack code.
                             This parameter can be any value of ::E_PsdkCmdAckCode. */
    uint8_t md5[16];    /*!< MD5 value calculated by payload. */
} T_LoadStateIdentityVerifyAck;

// PSDK_PAYLOADSTATE_CMDID_SDK_VERSION
/**
 * @brief Acquire PSDK version command ack data structure.
 */
typedef struct {
    uint8_t ackCode;                    /*!< Specifies PSDK command ack code.
                                             This parameter can be any value of ::E_PsdkCmdAckCode. */
    union {
        struct {
            uint32_t verDebug   : 8;
            uint32_t verModify  : 8;
            uint32_t verMinor   : 8;
            uint32_t verMajor   : 8;
        } ver;
        uint32_t data;
    } version;                          /*!< Specifies PSDK version number. */
} T_LoadStatePsdkVersionAck;

// PSDK_PAYLOADSTATE_CMDID_LINK_HANDSHAKE
/**
 * @brief PSDK communication link hand-shake command request data structure.
 */
typedef struct {
    uint8_t pingData[PAYLOADSTATE_MAX_PINGDATA_SIZE];    /*!< Specifies data used to detecting link state.
                                                                   @note The data length is between 1 and PAYLOADSTATE_MAX_PINGDATA_SIZE. */
} T_LoadStateLinkHandShakeReq;

/**
 * @brief PSDK communication link hand-shake command ack data structure.
 */
typedef struct {
    uint8_t ackCode;                                        /*!< Specifies PSDK command ack code.
                                                                 This parameter can be any value of ::E_PsdkCmdAckCode */
    uint8_t pingData[PAYLOADSTATE_MAX_PINGDATA_SIZE];   /*!< Specifies data used to detecting link state.
                                                                 @note The data length is between 1 and PAYLOADSTATE_MAX_PINGDATA_SIZE. */
} T_LoadStateLinkHandShakeAck;

// PSDK_PAYLOADSTATE_CMDID_PRODUCT_INFO
/**
 * @brief Acquire PSDK product information command ack data structure.
 */
typedef struct {
    uint8_t ackCode;                                              /*!< Specifies PSDK command ack code.
                                                                       This parameter can be any value of ::E_PsdkCmdAckCode */
    char productName[PAYLOADSTATE_MAX_PRODUCT_NAME_SIZE];    /*!< Specifies PSDK product name. */
    char productID[PAYLOADSTATE_MAX_PRODUCT_ID_SIZE];        /*!< Specifies PSDK product ID. */
    char developerAccount[PAYLOADSTATE_MAX_DEV_ACCOUNT_SIZE];/*!< Specifies PSDK developer account email. */
} T_LoadStateGetProductInfoAck;

/**
 * @brief Acquire support version of skyport for PSDK command request data structure.
 */
typedef struct {
    PSDK_EMPTY_STRUCT
} T_LoadStateGetSkyportVersionReq;

/**
 * @brief Acquire support version of skyport for PSDK command ack data structure.
 */
typedef struct {
    uint8_t ackCode;        /*!< Specifies PSDK command ack code.
                             This parameter can be any value of ::E_PsdkCmdAckCode */
    union {
        struct {
            uint32_t debugVer  : 8;
            uint32_t modifyVer : 8;
            uint32_t minorVer  : 8;
            uint32_t majorVer  : 8;
        } ver;
        uint32_t data;
    } version;             /*!< Specifies PSDK version. */
} T_LoadStateGetSkyportVersionAck;

/**
 * @brief Acquire PSDK product alias command request data structure.
 */
typedef struct {
    PSDK_EMPTY_STRUCT
} T_LoadStateGetProductAliasReq;

/**
 * @brief Acquire PSDK product alias command ack data structure.
 */
typedef struct {
    uint8_t ackCode;                                             /*!< Specifies PSDK command ack code.
                                                                      This parameter can be any value of ::E_PsdkCmdAckCode */
    char productName[PAYLOADSTATE_MAX_PRODUCT_NAME_SIZE];   /*!< Specifies PSDK product name. */
} T_LoadStateGetProductAliasAck;

#pragma pack()

/**
 * @}
 */

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif //PSDK_CMDSET_PAYLOAD_STATE_H

/************************ (C) COPYRIGHT DJI Innovations *******END OF FILE******/
