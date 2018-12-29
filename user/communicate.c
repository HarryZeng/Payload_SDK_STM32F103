
#include "communicate.h"
#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_usart.h"
#include "misc.h"
/*

0xA5 0x85 P1L P1H P2L P2H P3L P3H LED_State 0x0D 0x0A

Pitch PWM1  P1H<<8+P1L
Roll  PWM2  P2H<<8+P2L
Yaw   PWM3  P3H<<8+P3L
LED-On/Off  LED_State    1->On  0->Off

*/

u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
u16 USART_RX_STA=0;       //接收状态标记	 
u8 rxFlag=0;
u8 finishFlah=0;
int16_t rxCounter=0;
int16_t rxCounterf=0;

char USART_TX_BUF[]={0xa5,0x85,0xdc,0x05,0xdc,0x05,0xdc,0x05,0x00,0x0d,0x0a};


void CommunicateUSART_Config(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
	
		Communicate_USART_GPIO_APBxClkCmd(Communicate_USART_GPIO_CLK, ENABLE);

		Communicate_USART_APBxClkCmd(Communicate_USART_CLK, ENABLE);

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
		
		GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);
		
		GPIO_InitStructure.GPIO_Pin = Communicate_USART_TX_GPIO_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(Communicate_USART_TX_GPIO_PORT, &GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Pin = Communicate_USART_RX_GPIO_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(Communicate_USART_RX_GPIO_PORT, &GPIO_InitStructure);

		 //USART 初始化设置

		USART_InitStructure.USART_BaudRate = Communicate_USART_BAUDRATE;//串口波特率
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
		USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
		USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

		USART_Init(Communicate_USARTx, &USART_InitStructure); //初始化串口1
		USART_ITConfig(Communicate_USARTx, USART_IT_RXNE, ENABLE);//开启串口接受中断
		USART_Cmd(Communicate_USARTx, ENABLE);                    //使能串口1 
}


void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
		USART_SendData(pUSARTx,ch);
		while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}


void CommunicateUsart_SendString( USART_TypeDef * pUSARTx, char *str,int16_t length)
{
		unsigned int k=0;
		do 
		{
			Usart_SendByte( pUSARTx, *(str + k) );
			k++;
		} //while (*(str + k)!='\0');
		while(length--);
		
		while (USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET) 
		{
			
		}
}


//void USART1_IRQHandler(void)
//{
//		uint8_t ucTemp;
//		if (USART_GetITStatus(Communicate_USARTx,USART_IT_RXNE)!=RESET) 
//		{
//				ucTemp = USART_ReceiveData(Communicate_USARTx );
//				rxCounter++;
//				if(rxFlag == 2)
//				{
//					USART_RX_BUF[USART_RX_STA++]=ucTemp ;
//					if(USART_RX_STA>=CommandLenth)
//					{
//						rxCounterf++;
//						finishFlah = 1;
//						rxFlag = 0;
//						USART_RX_STA = 0;
//					}
//				}
//				/*报头 接收 判断*/
//				else if(ucTemp == 0xA5 && rxFlag == 0)
//				{
//					rxFlag = 1;
//					USART_RX_BUF[USART_RX_STA++]=ucTemp ;
//				}
//				else if(ucTemp == 0x85 && rxFlag ==1 )
//				{
//					rxFlag = 2;
//					USART_RX_BUF[USART_RX_STA++]=ucTemp ;
//				}
//		}
//}





