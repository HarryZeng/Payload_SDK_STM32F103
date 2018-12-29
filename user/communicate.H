/**
 ******************************************************************************
 * @file    uart.h
 * @version V1.0.0
 * @date    2017/11/10
 * @brief   This is the header file for "uart.c".
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
 * If you receive this source code without DJI抯 authorization, you may not
 * further disseminate the information, and you must immediately remove the
 * source code and notify DJI of its removal. DJI reserves the right to pursue
 * legal actions against you for any loss(es) or damage(s) caused by your
 * failure to do so.
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __COMMUNICATE_H__
#define __COMMUNICATE_H__

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
 #define Communicate_USARTx 									USART1
 #define Communicate_USART_CLK 								RCC_APB2Periph_USART1
 #define Communicate_USART_APBxClkCmd 				RCC_APB2PeriphClockCmd
 #define Communicate_USART_BAUDRATE 					115200 
 // USART GPIO 
 #define Communicate_USART_GPIO_CLK 					(RCC_APB2Periph_GPIOB)
 #define Communicate_USART_GPIO_APBxClkCmd 		RCC_APB2PeriphClockCmd 

 #define Communicate_USART_TX_GPIO_PORT 			GPIOB
 #define Communicate_USART_TX_GPIO_PIN 				GPIO_Pin_6
 #define Communicate_USART_RX_GPIO_PORT 			GPIOB
 #define Communicate_USART_RX_GPIO_PIN 				GPIO_Pin_7

 #define Communicate_USART_IRQ 								USART1_IRQn
 #define Communicate_USART_IRQHandler 				USART1_IRQHandler



#define USART_REC_LEN  			200  	//定义最大接收字节数 200
#define CommandLenth   11
extern u8 finishFlah;			
extern u8  USART_RX_BUF[USART_REC_LEN]; 	//接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA;         					//接收状态标记	
extern char USART_TX_BUF[];

extern u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
extern u16 USART_RX_STA;       //接收状态标记	 
extern u8 rxFlag;
extern int16_t rxCounter;
extern int16_t rxCounterf;
void CommunicateUSART_Config(void);	 
void CommunicateUsart_SendString( USART_TypeDef * pUSARTx, char *str,int16_t length);


/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

#endif
