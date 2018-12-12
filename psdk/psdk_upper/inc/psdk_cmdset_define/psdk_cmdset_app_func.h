/**
 ******************************************************************************
 * @file    psdk_cmdset_app_func.h
 * @version V1.0.0
 * @date    2017/11/9
 * @brief   This file defines the payload SDK App function command set.
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
#ifndef PSDK_CMDSET_APP_FUNC_H
#define PSDK_CMDSET_APP_FUNC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <psdk_typedef.h>
#include <psdk_core.h>

/** @addtogroup PSDK
 * @{
 */

/** @addtogroup PSDK_App_Function
 * @{
 */

/* Exported constants --------------------------------------------------------*/

/** @defgroup A_Func_Exported_Constants Exported constants
 * @{
 */

/** @defgroup Data_Length_Related Data Length Related
 * @{
 */

#define APPFUNC_APP_TO_LOAD_MAX_LEN                     32  /*!< Max size of data from mobile app to load */
#define APPFUNC_LOAD_TO_APP_MAX_LEN                     128 /*!< Max size of data from load to mobile app */
#define APPFUNC_FLOAT_WINDOW_MSG_MAX_SIZE              128  /*!< Max size of float window data from load to mobile app */

/**
 * @}
 */

/** @defgroup E_Constants_Widget_Related Widget Related
 * @{
 */

#define APPFUNC_MAX_WIDGET_NAME_SIZE                   32   /*!< Max size of widget name */
#define APPFUNC_LIST_MAX_ITEM_NUM                       10  /*!< Max list item number */
#define APPFUNC_LIST_MAX_ITEM_NAME_SIZE                16   /*!< Max size of list item name */
#define APPFUNC_INT_INPUT_BOX_PROMPT_CHAR_MAX_SIZE    32   /*!< Max size of additional prompt string of input box widget */
#define APPFUNC_WIDGET_VALUE_GROUP_MAX_ITEM_COUNT     15   /*!< Max item count of widget group, used when "Get Widget Value Group Data" command */
#define APPFUNC_WIDGET_SCALE_MIN_VALUE                  0   /*!< Scale widget min value */
#define APPFUNC_WIDGET_SCALE_MAX_VALUE                  100 /*!< Scale widget max value */

/**
 * @}
 */

/**
 * @}
 */

/* Exported macros -----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

/** @defgroup A_Func_Exported_Types Exported Types
 * @{
 */

/** @defgroup A_Func_Command_Related Command Related
 * @{
 */

/**
 * @brief App Function Command ID
 */
typedef enum {
    PSDK_APPFUNC_CMDID_TT_APP_TO_LOAD = 0x01,           /*!< Transparent data transmission from mobile app to load command */
    PSDK_APPFUNC_CMDID_TT_LOAD_TO_APP = 0x02,           /*!< Transparent data transmission from load to mobile app command */

    PSDK_APPFUNC_CMDID_PUSH_FLOATING_WINDOW_MSG = 0x03, /*!< Float window data transmission command */

    PSDK_APPFUNC_CMDID_GET_WIDGET_LIST_LENGTH = 0x04,   /*!< Get widget list length command, used to get total widget count. */
    PSDK_APPFUNC_CMDID_GET_WIDGET_LIST_VALUE = 0x05,    /*!< Get widget list data command, used to get widget attribute. */
    PSDK_APPFUNC_CMDID_GET_WIDGET_GROUP_COUNT = 0x06,   /*!< Get widget value group number command,
                                                                   @note max item count of widget group is #APPFUNC_WIDGET_VALUE_GROUP_MAX_ITEM_COUNT. */
    PSDK_APPFUNC_CMDID_GET_WIDGET_GROUP_VALUE = 0x07,   /*!< Get widget value group data command, used to get widget value data of a group.
                                                                   @note Max item count of widget group is #APPFUNC_WIDGET_VALUE_GROUP_MAX_ITEM_COUNT. */
    PSDK_APPFUNC_CMDID_SET_WIDGET_VALUE = 0x08,         /*!< Set widget value command */
} E_PsdkAppFuncCmd;

/**
 * @}
 */

/** @defgroup A_Func_Widget_Related Widget Related
 * @{
 */

/**
 * @brief Widget Type
 */
typedef enum {
    PSDK_APPFUNC_WIDGET_TYPE_BUTTON = 1,        /*!< button widget type value */
    PSDK_APPFUNC_WIDGET_TYPE_SWITCH = 2,        /*!< switch widget type value */
    PSDK_APPFUNC_WIDGET_TYPE_SCALE = 3,         /*!< scale widget type value */
    PSDK_APPFUNC_WIDGET_TYPE_LIST = 4,          /*!< list widget type value */
    PSDK_APPFUNC_WIDGET_TYPE_INT_INPUT_BOX = 5, /*!< input box widget type value */
} E_PsdkAppFuncWidgetType;

/**
 * @brief Button State
 */
typedef enum {
    PSDK_APPFUNC_BUTTON_VAL_PRESS_DOWN = 1, /*!< button press down state */
    PSDK_APPFUNC_BUTTON_VAL_RELEASE_UP = 0, /*!< button release up state */
} E_PsdkAppFuncButtonVal;

/**
 * @brief Switch State
 */
typedef enum {
    PSDK_APPFUNC_SWITCH_VAL_OFF = 0,    /*!< switch off state */
    PSDK_APPFUNC_SWITCH_VAL_ON = 1,     /*!< switch on state */
} E_PsdkAppFuncSwitchVal;

#pragma pack(1)

/**
 * @brief Widget Value Union
 */
typedef union {
    int32_t buttonVal;      /*!< Specifies button value.
                                 This parameter can be any value of ::E_PsdkAppFuncButtonVal
                                 @note This value have meaning only when set value.*/
    int32_t switchVal;      /*!< Specifies switch value.
                                 This parameter can be any value of ::E_PsdkAppFuncSwitchVal */
    int32_t scaleVal;       /*!< Specifies scale value.
                                 This parameter must be between #APPFUNC_WIDGET_SCALE_MIN_VALUE and  #APPFUNC_WIDGET_SCALE_MAX_VALUE */
    int32_t listVal;        /*!< Specifies the choose list item number.
                                 This parameter start at 0 */
    int32_t intInputBoxVal; /*!< Specifies the int input box value. */
    int32_t data;           /*!< Specifies the widget value. */
} U_AppFuncWidgetValue;

/**
* @brief Widget based parameters and value structure
*/
typedef struct {
    uint8_t widgetType;                 /*!< Specifies widget type.
                                             This parameter can be any value of ::E_PsdkAppFuncWidgetType */
    uint8_t widgetIndex;                /*!< Specifies widget index.
                                             @note The value is unique index for widget, starting at 0.
                                             DJI Pilot widget show sequence relay on the widgetIndex.*/
    U_AppFuncWidgetValue widgetValue;   /*!< Specifies widget value, please refer to ::U_AppFuncWidgetValue */
} T_PsdkAppFuncWidgetValueItem;

/**
 * @brief Widget property structure.
 */
typedef struct {
    uint8_t widgetType;             /*!< Specifies widget type.
                                         This parameter can be any value of ::E_PsdkAppFuncWidgetType */
    uint8_t widgetIndex;            /*!< Specifies widget index.
                                         @note The value is unique index for widget, starting at 0.
                                         DJI Pilot widget show sequence relay on the widgetIndex.*/
    uint8_t widgetName[APPFUNC_MAX_WIDGET_NAME_SIZE];
    /*!< Specifies widget name string.
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
            uint8_t listItemName[APPFUNC_LIST_MAX_ITEM_NUM][APPFUNC_LIST_MAX_ITEM_NAME_SIZE];
            /*!< Specifies list item names.
                 @note list item name max length is #APPFUNC_LIST_MAX_ITEM_NAME_SIZE */
        } listAttribute;            /*!< Specifies list widget attribute. */
        struct {
            uint8_t promptChar[APPFUNC_INT_INPUT_BOX_PROMPT_CHAR_MAX_SIZE];
            /*!< Specifies input box additional prompt string.
                 @note its max length is #APPFUNC_INT_INPUT_BOX_PROMPT_STR_MAX_SIZE */
        } intInputBoxAttribute;     /*!< Specifies input box widget attribute. */
    } widgetAttribute;
} T_PsdkAppFuncWidgetProperty;

/**
 * @}
 */

/** @addtogroup A_Func_Command_Related
 * @{
 */

// PSDK_APPFUNC_CMDID_TT_APP_TO_LOAD
/**
 * @brief Transparent data transmission from mobile app to load command request data structure.
 */
typedef struct {
    uint8_t data[APPFUNC_APP_TO_LOAD_MAX_LEN];  /*!< Specifies transmission data. */
} T_PsdkAppFuncTransAppToLoadReq;

/**
 * @brief Transparent data transmission from mobile app to load command ack data structure.
 */
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkAppFuncTransAppToLoadAck;

// PSDK_APPFUNC_CMDID_TT_LOAD_TO_APP
/**
 * @brief Transparent data transmission from load to mobile app command request data structure.
 */
typedef struct {
    uint8_t data[APPFUNC_LOAD_TO_APP_MAX_LEN];  /*!< Specifies transmission data. */
} T_PsdkAppFuncTransLoadToAppReq;

/**
 * @brief Transparent data transmission from load to mobile app command ack data structure.
 */
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkAppFuncTransLoadToAppAck;

//PSDK_APPFUNC_CMDID_PUSH_FLOATING_WINDOW_MSG
/**
 * @brief Float window message transmission command request data structure.
 */
typedef struct {
    uint8_t msg[APPFUNC_FLOAT_WINDOW_MSG_MAX_SIZE]; /*!< Specifies float window message. */
} T_PsdkAppFuncPushFloatWindowMsgReq;

/**
 * @brief Float window message transmission command ack data structure.
 */
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkAppFuncPushFloatWindowMsgAck;

//PSDK_APPFUNC_CMDID_GET_WIDGET_LIST_LENGTH
/**
 * @brief Get widget list length command request data structure.
 */
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkAppFuncGetWidgetListLengthReq;

/**
 * @brief Get widget list length command ack data structure.
 */
typedef struct {
    E_PsdkCmdAckCode ackCode;   /*!< Specifies PSDK command ack code.
                                     This parameter can be any value of ::E_PsdkCmdAckCode */
    uint8_t widgetListLength;   /*!< Specifies widget count of widget list. */
} T_PsdkAppFuncGetWidgetListLengthAck;

//PSDK_APPFUNC_CMDID_GET_WIDGET_LIST_VALUE
/**
 * @brief Get widget list data command request data structure.
 */
typedef struct {
    uint8_t widgetListSubscript;/*!< Specifies widget subscription. */
} T_PsdkAppFuncGetWidgetListValueReq;

/**
 * @brief Get widget list data command ack data structure.
 */
typedef struct {
    E_PsdkCmdAckCode ackCode;         /*!< Specifies PSDK command ack code.
                                           This parameter can be any value of ::E_PsdkCmdAckCode */
    T_PsdkAppFuncWidgetProperty prop; /*!< Specifies widget property, refer to ::T_PsdkAppFuncWidgetProperty */
} T_PsdkAppFuncGetWidgetListValueAck;

//PSDK_APPFUNC_CMDID_GET_WIDGET_GROUP_COUNT
/**
 * @brief Get widget value group number command request data structure.
 */
typedef struct {
    PSDK_EMPTY_STRUCT
} T_PsdkAppFuncGetWidgetGroupCountReq;

/**
 * @brief Get widget value group number command ack data structure.
 */
typedef struct {
    E_PsdkCmdAckCode ackCode;   /*!< Specifies PSDK command ack code.
                                     This parameter can be any value of ::E_PsdkCmdAckCode */
    uint8_t groupCount;         /*!< Specifies widget group count. */
} T_PsdkAppFuncGetWidgetGroupCountAck;

//PSDK_APPFUNC_CMDID_GET_WIDGET_GROUP_VALUE
/**
 * @brief Get widget value group data command request data structure.
 */
typedef struct {
    uint8_t groupNum;   /*!< Specifies group number requested, starting at 0 */
} T_PsdkAppFuncGetWidgetGroupValueReq;

/**
 * @brief Get widget value group data command ack data structure.
 */
typedef struct {
    E_PsdkCmdAckCode ackCode;   /*!< Specifies PSDK command ack code.
                                     This parameter can be any value of ::E_PsdkCmdAckCode */
    uint8_t widgetValueCount;   /*!< Specifies widget count of the group. */
    T_PsdkAppFuncWidgetValueItem widgetValue[APPFUNC_WIDGET_VALUE_GROUP_MAX_ITEM_COUNT];
                                /*!< Specifies widget value items of the group. */
} T_PsdkAppFuncGetWidgetGroupValueAck;

// PSDK_APPFUNC_CMDID_SET_WIDGET_VALUE
/**
 * @brief Set widget value command request data structure.
 */
typedef struct {
    T_PsdkAppFuncWidgetValueItem widgetValue;   /*!< Specifies widget value item set. */
} T_PsdkAppFuncSetWidgetValueReq;

/**
 * @brief Set widget value command ack data structure.
 */
typedef struct {
    E_PsdkCmdAckCode ackCode;   /*!< Specifies PSDK command ack code.
                                     This parameter can be any value of ::E_PsdkCmdAckCode */
} T_PsdkAppFuncSetWidgetValueAck;

#pragma pack()

/**
 * @}
 */

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

#endif //PSDK_CMDSET_APP_FUNC_H

/************************ (C) COPYRIGHT DJI Innovations *******END OF FILE******/

