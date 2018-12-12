/**
 ******************************************************************************
 * @file    led_button_switch.h
 * @version V1.0.0
 * @date    2017/11/10
 * @brief   This is the header file for "led_button_switch.c".
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
#ifndef DEMO_RTOS_RTTHREAD_LED_BUTTON_SWITCH_H
#define DEMO_RTOS_RTTHREAD_LED_BUTTON_SWITCH_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <dji_typedef.h>

/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef enum {
    LED1_GREEN = 0,
    LED2_RED,
    LED3_BLUE,
} E_LED;

typedef enum {
    LED_OPT_ON = 0,
    LED_OPT_OFF,
    LED_OPT_TOGGLE,
} E_LEDOption;

typedef enum {
    BUTTON1 = 0,
    BUTTON2,
} E_Button;

typedef void (*ButtonPressCallbackFunc)(E_Button button);

//LED1
#define LED1_RCC    RCC_APB2Periph_GPIOB
#define LED1_PORT   GPIOB
#define LED1_PIN    GPIO_Pin_5



#define LED1_T  GPIO_WriteBit(LED1_PORT, LED1_PIN, (BitAction)!GPIO_ReadOutputDataBit(LED1_PORT, LED1_PIN))
#define LED1_S  GPIO_WriteBit(LED1_PORT, LED1_PIN, Bit_SET)
#define LED1_R  GPIO_WriteBit(LED1_PORT, LED1_PIN, Bit_RESET)



/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void LED_Init(void);
void LED_Control(E_LED led, E_LEDOption ledOption);

void UART_SW_Init(void);
void UART_SW_On(void);
void UART_SW_Off(void);

void CAN_SW_Init(void);
void CAN_SW_On(void);
void CAN_SW_Off(void);

void Button_Init(void);
void Button_StartUpdate(void);

/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif //DEMO_RTOS_RTTHREAD_LED_BUTTON_SWITCH_H

/************************ (C) COPYRIGHT DJI Innovations *******END OF FILE******/
