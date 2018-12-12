/**
 ******************************************************************************
 * @file    app_infor.c
 * @version V1.3.0
 * @date    2018/09/19
 * @brief   The file specifies payload application information.
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
#ifndef __APP_INFO_H__
#define __APP_INFO_H__

/* Includes ------------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

// ATTENTION: User must goto developer.dji.com to create your own payload sdk application, get payload sdk application
// information then fill in the application information here.
//#define USER_APP_NAME               "pao_tou"
//#define USER_APP_ID                 "0123456789"
//#define USER_APP_KEY                "0000000000"
//#define USER_DEVELOPER_ACCOUNT     "PengZhen"

#define USER_APP_NAME               "laba"
#define USER_APP_ID                 "56616"
#define USER_APP_KEY                "09455d4e9e38231c7cc54da2d46458d"
#define USER_DEVELOPER_ACCOUNT      "pengzhen@zkrtuav.com"

// ATTENTION: If need to upgrade SKYPORT adapter's firmware to a fixed version, please specify the version number here and
// SKYPORT_FW_FIX_VER_NEED macro below.
// When user use DJI Assistant to upgrade SKYPORT adapter firmware, DJI Assistant will suggest you upgrade to the fixed version
// if the fixed version here exists in server. Otherwise, DJI Assistant will suggest you upgrade to the latest version.

// Macro used to define whether upgrade SKYPORT adapter's firmware to fixed version is needed.
// 1 represents need, 0 represents not need.
#define SKYPORT_FW_FIX_VER_NEED 0

// For example, you can write like this representing upgrading SKYPORT adapter's firmware to version 01.00.08.91:
#if SKYPORT_FW_FIX_VER_NEED
 #define SKYPORT_FW_FIX_VER_MAJOR  1
 #define SKYPORT_FW_FIX_VER_MINOR  0
 #define SKYPORT_FW_FIX_VER_MODIFY 8
 #define SKYPORT_FW_FIX_VER_DEBUG  91
#endif

// ATTENTION: If need to set alias for load application, please specify it here and PSDK_APP_ALIAS_NEED macro below.
// Note: Application alias length must be less than 32.

// Macro used to define whether PSDK application alias is needed.
// 1 represents need, 0 represents not need.
#define PSDK_APP_ALIAS_NEED     0

// For example, define an application alias as "PSDK_ALIAS_APPNAME":
#if PSDK_APP_ALIAS_NEED
 #define PSDK_APP_ALIAS  "PSDK_ALIAS_APPNAME"
#endif

/* Exported macros -----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

#endif
