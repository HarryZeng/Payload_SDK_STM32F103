/**
 ******************************************************************************
 * @file    psdk_app_func.h
 * @version V1.0.0
 * @date    2017/08/10
 * @brief   This is the header file for "psdk_app_func.c", defining the
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
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef PSDK_APP_FUNC_H
#define PSDK_APP_FUNC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <psdk_upper.h>
#include "psdk_cmdset.h"

/** @addtogroup PSDK
 * @{
 */

/** @addtogroup PSDK_App_Function
 * @{
 */

/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/

/** @defgroup A_Func_Exported_Macros Exported Macros
 * @{
 */

/**
 * @brief Define button widget.
 */
#define APPFUNC_DEF_BUTTON_WIDGET(index, nameStr)  \
{ \
    .widgetType = PSDK_APPFUNC_WIDGET_TYPE_BUTTON, \
    .widgetIndex = index, \
    .widgetName = nameStr, \
}

/**
 * @brief Define switch widget.
 */
#define APPFUNC_DEF_SWITCH_WIDGET(index, nameStr) \
{ \
    .widgetType = PSDK_APPFUNC_WIDGET_TYPE_SWITCH, \
    .widgetIndex = index, \
    .widgetName = nameStr, \
}

/**
 * @brief Define scale widget.
 */
#define APPFUNC_DEF_SCALE_WIDGET(index, nameStr) \
{ \
    .widgetType = PSDK_APPFUNC_WIDGET_TYPE_SCALE, \
    .widgetIndex = index, \
    .widgetName = nameStr, \
}

/**
 * @brief Define list widget.
 */
#define APPFUNC_DEF_LIST_WIDGET(index, nameStr, chooseCount, choose1Str, ...) \
{ \
    .widgetType = PSDK_APPFUNC_WIDGET_TYPE_LIST, \
    .widgetIndex = index, \
    .widgetName = nameStr, \
    .widgetAttribute.listAttribute.listItemNum = chooseCount, \
    .widgetAttribute.listAttribute.listItemName = {choose1Str,##__VA_ARGS__}, \
}

/**
 * @brief Define input box widget.
 */
#define APPFUNC_DEF_INT_INPUT_BOX_WIDGET(index, nameStr, promtStr) \
{ \
    .widgetType = PSDK_APPFUNC_WIDGET_TYPE_INT_INPUT_BOX, \
    .widgetIndex = index, \
    .widgetName = nameStr, \
    .widgetAttribute.intInputBoxAttribute.promptStr = promtStr, \
}

/**
 * @}
 */

/* Exported types ------------------------------------------------------------*/

/** @addtogroup A_Func_Exported_Types
 * @{
 */

/** @defgroup A_Func_Callback_Related Callback Related
 * @{
 */

typedef void (*ReceiveFromAppFunc)(const uint8_t *pData, uint16_t dataLen);
typedef E_PsdkStat (*GetWidgetValueFunc)(E_PsdkAppFuncWidgetType widgetType, uint8_t widgetIndex,
                                         U_AppFuncWidgetValue *pWidgetValue);
typedef E_PsdkStat (*SetWidgetValueFunc)(E_PsdkAppFuncWidgetType widgetType, uint8_t widgetIndex,
                                         const U_AppFuncWidgetValue *pWidgetValue);
/**
 * @}
 */

/** @addtogroup A_Func_Widget_Related
 * @{
 */

/**
 * @brief Widget detail information.
 */
typedef struct {
    E_PsdkAppFuncWidgetType widgetType; /*!< Specifies widget type.
                                             This parameter can be any value of ::E_PsdkAppFuncWidgetType */
    uint8_t widgetIndex;                /*!< Specifies widget index.
                                             @note The value is unique index for widget, starting at 0.
                                             DJI Pilot widget show sequence relay on the widgetIndex.*/
    const char *widgetName;             /*!< Pointer widget name string.
                                               @note Widget name max length is #APPFUNC_MAX_WIDGET_NAME_SIZE */
    union {
        struct {
            PSDK_EMPTY_STRUCT
        } buttonAttribute;          /*!< Specifies button widget attribute. */
        struct {
            PSDK_EMPTY_STRUCT
        } switchAttribute;          /*!< Specifies switch widget attribute. */
        struct {
            PSDK_EMPTY_STRUCT
        } scaleAttribute;           /*!< Specifies scale widget attribute. */
        struct {
            uint8_t listItemNum;    /*!< Specifies list item number */
            const char *listItemName[APPFUNC_LIST_MAX_ITEM_NUM];
                                    /*!< Array of pointer to list item names,
                                     *   @note list item name max length is #APPFUNC_LIST_MAX_ITEM_NAME_SIZE. */
        } listAttribute;            /*!< Specifies list widget attribute. */
        struct {
            //promptStr max length : APPFUNC_INT_INPUT_BOX_PROMPT_CHAR_MAX_SIZE (32)
            const char *promptStr; /*!< Pointer to input box additional prompt string. */
        } intInputBoxAttribute;     /*!< Specifies input box widget attribute. */
    } widgetAttribute;              /*!< Specifies widget attribute, refer to ::U_AppFuncWidgetAttribute for details. */
} T_PsdkAppFuncWidgetListItem;
/**
 * @}
 */

/**
 * @}
 */

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @addtogroup A_Func_Exported_Functions
 * @{
 */

E_PsdkStat PsdkAppFunc_Init(T_PsdkUpper *psdkUpper);
E_PsdkStat PsdkAppFunc_TransferToApp(T_PsdkUpper *psdkUpper, const uint8_t *pSendData, uint16_t needSendLen,
                                     uint16_t *pRealSendLen);
E_PsdkStat PsdkAppFunc_SetReceiveFromAppCallback(T_PsdkUpper *psdkUpper, ReceiveFromAppFunc func);
E_PsdkStat PsdkAppFunc_PushMsgToFloatingWindow(T_PsdkUpper *psdkUpper, const char *msg);
E_PsdkStat PsdkAppFunc_SetWidgetList(T_PsdkUpper *psdkUpper, const T_PsdkAppFuncWidgetListItem *widgetList,
                                     uint8_t widgetItemCount);
E_PsdkStat PsdkAppFunc_RegGetWidgetValueCallback(T_PsdkUpper *psdkUpper, GetWidgetValueFunc getWidgetValueFunc);
E_PsdkStat PsdkAppFunc_RegSetWidgetValueCallback(T_PsdkUpper *psdkUpper, SetWidgetValueFunc setWidgetValueFunc);

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

#endif //PSDK_APP_FUNC_H

/************************ (C) COPYRIGHT DJI Innovations *******END OF FILE******/
