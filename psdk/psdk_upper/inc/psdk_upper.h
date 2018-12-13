/**
 ********************************************************************
 * @file    psdk_upper.h
 * @version V1.0.0
 * @date    2017/08/10
 * @brief   This is the header file for "psdk_upper.c", defining the
 * structures and (exported) function prototypes.
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
 *********************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef PSDK_UPPER_H
#define PSDK_UPPER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <psdk_core.h>

/** @addtogroup PSDK
 * @{
 */

/** @addtogroup PSDK_Upper
 * @{
 */

/* Exported constants --------------------------------------------------------*/

/** @defgroup Upper_Exported_Constants Exported Constants
 * @{
 */

/** @defgroup CAN_ID CAN ID
 * @note Please unauthorized modify CAN ID.
 * @{
 */

#define PSDK_CAN_ID_SEND        0x0021  /*!< CAN ID used to send data. */
#define PSDK_CAN_ID_RECEIVE     0x0012  /*!< CAN ID used to receive data. */

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

/**
 * @brief This is the set of ID information of your application with PSDK.
 */
typedef struct {
    char APP_Name[33];          /*!< Specifies Payload SDK APP name. */
    char APP_Id[17];            /*!< Specifies Payload SDK APP ID. */
    char APP_Key[33];           /*!< Specifies Payload SDK APP key. */
    char DeveloperAccount[65];  /*!< Specifies developer account email. */
} T_PsdkUserInfo;

/**
 * @brief This structure is used to store a fixed SkyPort FW version for your application.
 * @details See ::PsdkUpper_SetFixVersion for more details on usage.
 */
typedef struct {
    uint8_t verMajor;
    uint8_t verMinor;
    uint8_t verModify;
    uint8_t verDebug;
} T_PsdkUserFixSkyport;

/**
 * @brief This structure is used for obtaining the alias of your product name.
 * Used for defining more descriptive names for your product.
 */
typedef struct {
    char ProductAlias[33];            /*!< Specifies Payload SDK APP alias. */
} T_PsdkUserCustomInfo;

/**
 * @brief This is a structure type for defining a top-level structure for the
 * integration of your application with PSDK.
 * @details This structure type is used to instantiates an object for all the
 * features that PSDK is capable of supporting.
 * Use this structure type to define a PSDK object in your code and you will
 * have access to the entire DJI PSDK API.
 */
typedef struct {
    T_PsdkProt protHandle;
} T_PsdkUpper;

/**
 * @}
 */

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

extern T_PsdkUpper s_psdkUpperHandle;

/** @addtogroup Upper_Exported_Functions
 * @{
 */

E_PsdkStat PsdkUpper_Init(T_PsdkUpper *psdkUpper, const T_PsdkUserInfo *userInfo);
E_PsdkStat PsdkUpper_SetFixVersion(const T_PsdkUserFixSkyport *fixSkyport);
E_PsdkStat PsdkUpper_SetProductAlias(const T_PsdkUserCustomInfo *customInfo);
E_PsdkStat PsdkUpper_ProcessReceiveData(T_PsdkUpper *psdkUpper, const uint8_t *pData, uint16_t len);
E_PsdkStat PsdkUpper_RegSendFunction(T_PsdkUpper *psdkUpper, PsdkSendCallbackFunc sendCallbackFunc);

/**
 * @}
 */

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

#endif //PSDK_UPPER_H

/************************ (C) COPYRIGHT DJI Innovations *******END OF FILE******/
