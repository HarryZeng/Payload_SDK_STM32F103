/**
 ******************************************************************************
 * @file    uart.c
 * @version V1.0.0
 * @date    2017/11/10
 * @brief   The file define UART interface driver functions.
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
#include "psdk_arch_sys.h"
#include "uart.h"
#include "dji_ringbuffer.h"
//#include "stm32f4xx_rcc.h"
#include "stm32f10x_rcc.h"
//#include "stm32f4xx_gpio.h"
#include "stm32f10x_gpio.h"
#include "misc.h"
//#include "stm32f4xx_usart.h"
#include "stm32f10x_usart.h"

#if PSDK_ARCH_USE_OS
#include "cmsis_os.h"
#endif

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

//uart uart buffer size define
#define UART_READ_BUF_SIZE      512
#define UART_WRITE_BUF_SIZE     512

//uart uart priority define
#define UART1_IRQ_PRIO_PRE      3
#define UART1_IRQ_PRIO_SUB      0

#define UART2_IRQ_PRIO_PRE      3
#define UART2_IRQ_PRIO_SUB      0

#define UART3_IRQ_PRIO_PRE      3
#define UART3_IRQ_PRIO_SUB      0

//uart GPIO define
#define UART1_GPIO_TX       GPIO_Pin_6
#define UART1_TX_PIN_SOURCE GPIO_PinSource6
#define UART1_GPIO_RX       GPIO_Pin_7
#define UART1_RX_PIN_SOURCE GPIO_PinSource7
#define UART1_GPIO          GPIOB
#define UART1_GPIO_RCC      RCC_APB2Periph_GPIOB
#define RCC_APBPeriph_UART1 RCC_APB2Periph_USART1

#define UART2_GPIO_TX       GPIO_Pin_2
#define UART2_TX_PIN_SOURCE GPIO_PinSource2
#define UART2_GPIO_RX       GPIO_Pin_3
#define UART2_RX_PIN_SOURCE GPIO_PinSource3
#define UART2_GPIO          GPIOA
#define UART2_GPIO_RCC      RCC_APB2Periph_GPIOA
#define RCC_APBPeriph_UART2 RCC_APB1Periph_USART2

#define UART3_GPIO_TX       GPIO_Pin_8
#define UART3_TX_PIN_SOURCE GPIO_PinSource8
#define UART3_GPIO_RX       GPIO_Pin_9
#define UART3_RX_PIN_SOURCE GPIO_PinSource9
#define UART3_GPIO          GPIOD
#define UART3_GPIO_RCC      RCC_APB2Periph_GPIOD
#define RCC_APBPeriph_UART3 RCC_APB1Periph_USART3

/* Private macro -------------------------------------------------------------*/

//UART ring buffer initialization
#define UART_RINGBUFFER_INIT(n)                                                         \
{                                                                                       \
RingBuf_Init(&s_uart##n##ReadRingBuffer, s_uart##n##ReadBuf, UART_READ_BUF_SIZE);       \
RingBuf_Init(&s_uart##n##WriteRingBuffer, s_uart##n##WriteBuf, UART_WRITE_BUF_SIZE);    \
}

//UART clock configure
#define RCC_CONFIG_UART(n)                                                      \
{                                                                               \
RCC_APB2PeriphClockCmd(UART##n##_GPIO_RCC, ENABLE);                             \
RCC_APB1PeriphClockCmd(RCC_APBPeriph_UART##n, ENABLE);                          \
}

//UART GPIO configure
//UART GPIO configure
#define GPIO_CONFIG_UART(n)                                                     \
{                                                                               \
GPIO_InitTypeDef GPIO_InitStructure;                                            \
                                                                                \
GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;                                   \
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                               \
GPIO_InitStructure.GPIO_Pin = UART##n##_GPIO_TX | UART##n##_GPIO_RX;            \
GPIO_Init(UART##n##_GPIO, &GPIO_InitStructure);                                 \
    \
   \
}

//UART module configure
#define UART_CONFIG(n, bd)                                                      \
{                                                                               \
USART_InitTypeDef USART_InitStructure;                                          \
                                                                                \
USART_InitStructure.USART_BaudRate = bd;                                        \
USART_InitStructure.USART_WordLength = USART_WordLength_8b;                     \
USART_InitStructure.USART_StopBits = USART_StopBits_1;                          \
USART_InitStructure.USART_Parity = USART_Parity_No;                             \
USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; \
USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                 \
                                                                                \
USART_Init(USART##n, &USART_InitStructure);                                     \
                                                                                \
USART_Cmd(USART##n, ENABLE);                                                    \
                                                                                \
USART_ITConfig(USART##n, USART_IT_RXNE, ENABLE);                                \
}

//UART nested vectored interrupt controller(NVIC) configure
#define UART_NVIC_CONFIG(n, prePrio, subPrio)                                   \
{                                                                               \
NVIC_InitTypeDef NVIC_InitStructure;                                            \
                                                                                \
NVIC_InitStructure.NVIC_IRQChannel = USART##n##_IRQn;                           \
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = prePrio;                 \
NVIC_InitStructure.NVIC_IRQChannelSubPriority = subPrio;                        \
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                                 \
NVIC_Init(&NVIC_InitStructure);                                                 \
}

//UART interrupt request handler function
#define UART_IRQ_HANDLER(n) \
void USART##n##_IRQHandler()\
{\
    uint8_t data;\
    \
    if (USART_GetITStatus(USART##n, USART_IT_RXNE) != RESET) {\
        data = (uint8_t)(USART_ReceiveData(USART##n) & 0x00FF);\
        RingBuf_Put(&s_uart##n##ReadRingBuffer, &data, 1);\
    }\
    \
    if(USART_GetITStatus(USART##n, USART_IT_TXE) != RESET) {\
        if(RingBuf_Get(&s_uart##n##WriteRingBuffer, &data, 1)) {\
            USART_SendData(USART##n, data);\
        } else {\
            USART_ITConfig(USART##n, USART_IT_TXE, DISABLE);\
        }\
    }\
}

/* Private variables ---------------------------------------------------------*/
#ifdef USING_UART_PORT_1
//UART1 read ring buffer structure
static T_RingBuffer s_uart1ReadRingBuffer;
//UART1 write ring buffer structure
static T_RingBuffer s_uart1WriteRingBuffer;
//UART1 read buffer
static uint8_t s_uart1ReadBuf[UART_READ_BUF_SIZE];
//UART1 write buffer
static uint8_t s_uart1WriteBuf[UART_WRITE_BUF_SIZE];

#if PSDK_ARCH_USE_OS
//UART1 mutex
static osMutexId s_uart1Mutex;
#endif
#endif

#ifdef USING_UART_PORT_2
static T_RingBuffer s_uart2ReadRingBuffer;
static T_RingBuffer s_uart2WriteRingBuffer;
static uint8_t s_uart2ReadBuf[UART_READ_BUF_SIZE];
static uint8_t s_uart2WriteBuf[UART_WRITE_BUF_SIZE];

#if PSDK_ARCH_USE_OS
static osMutexId s_uart2Mutex;
#endif
#endif

#ifdef USING_UART_PORT_3
static T_RingBuffer s_uart3ReadRingBuffer;
static T_RingBuffer s_uart3WriteRingBuffer;
static uint8_t s_uart3ReadBuf[UART_READ_BUF_SIZE];
static uint8_t s_uart3WriteBuf[UART_WRITE_BUF_SIZE];

#if PSDK_ARCH_USE_OS
static osMutexId s_uart3Mutex;
#endif
#endif

/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/**
 * @brief UART initialization function.
 * @param uartNum UART number to be initialized.
 * @param baudRate UART baudrate.
 * @return None.
 */
void UART_Init(E_UartNum uartNum, uint32_t baudRate)
{    
    switch (uartNum) {

#ifdef USING_UART_PORT_1
        case UART_NUM_1: {
            UART_RINGBUFFER_INIT(1);
            RCC_APB2PeriphClockCmd(UART1_GPIO_RCC, ENABLE);
            RCC_APB2PeriphClockCmd(RCC_APBPeriph_UART1, ENABLE);
						RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	
						GPIO_PinRemapConfig(GPIO_Remap_USART1,ENABLE);
            GPIO_CONFIG_UART(1);
            UART_NVIC_CONFIG(1, UART1_IRQ_PRIO_PRE, UART1_IRQ_PRIO_SUB);
            UART_CONFIG(1, baudRate);

#if PSDK_ARCH_USE_OS
            osMutexDef(uart1Mutex);
            s_uart1Mutex = osMutexCreate(osMutex(uart1Mutex));
#endif
        }
            break;
#endif

#ifdef USING_UART_PORT_2
        case UART_NUM_2: {
            UART_RINGBUFFER_INIT(2);
            RCC_APB2PeriphClockCmd(UART2_GPIO_RCC, ENABLE);
            RCC_APB1PeriphClockCmd(RCC_APBPeriph_UART2, ENABLE);
            GPIO_CONFIG_UART(2);
            UART_NVIC_CONFIG(2, UART2_IRQ_PRIO_PRE, UART2_IRQ_PRIO_SUB);
            UART_CONFIG(2, baudRate);

#if PSDK_ARCH_USE_OS
            osMutexDef(uart2Mutex);
            s_uart2Mutex = osMutexCreate(osMutex(uart2Mutex));
#endif
        }
            break;
#endif

#ifdef USING_UART_PORT_3
        case UART_NUM_3: {
            UART_RINGBUFFER_INIT(3);
            RCC_APB2PeriphClockCmd(UART3_GPIO_RCC, ENABLE);
            RCC_APB1PeriphClockCmd(RCC_APBPeriph_UART3, ENABLE);
            //GPIO_CONFIG_UART(3);
            UART_NVIC_CONFIG(3, UART3_IRQ_PRIO_PRE, UART3_IRQ_PRIO_SUB);
            UART_CONFIG(3, baudRate);

#if PSDK_ARCH_USE_OS
            osMutexDef(uart3Mutex);
            s_uart3Mutex = osMutexCreate(osMutex(uart3Mutex));
#endif
        }
            break;
#endif

        default:
            break;
    }
}


//void Usart1_Init(uint32_t baudRate)
//{
//	GPIO_InitTypeDef GPIO_InitStructure;
//	
//	UART_RINGBUFFER_INIT(1);
//	RCC_APB2PeriphClockCmd(UART1_GPIO_RCC, ENABLE);
//  RCC_APB2PeriphClockCmd(RCC_APBPeriph_UART1, ENABLE);
//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
//	//USART1_TX   PA.9
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);

//	//USART1_RX      PA.10
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
//	GPIO_Init(GPIOA, &GPIO_InitStructure); 

//	UART_NVIC_CONFIG(1, UART1_IRQ_PRIO_PRE, UART1_IRQ_PRIO_SUB);
//	UART_CONFIG(1, baudRate);	
//}

/**
 * @brief Read UART data.
 * @param uartNum UART number.
 * @param buf Pointer to buffer used to store data.
 * @param readSize Size of data to be read.
 * @return Size of data read actually.
 */
int UART_Read(E_UartNum uartNum, uint8_t *buf, uint16_t readSize)
{
    uint16_t readRealSize;

    switch (uartNum) {

#ifdef USING_UART_PORT_1
        case UART_NUM_1: {
#if PSDK_ARCH_USE_OS
            osMutexWait(s_uart1Mutex, osWaitForever);
            readRealSize = RingBuf_Get(&s_uart1ReadRingBuffer, buf, readSize);
            osMutexRelease(s_uart1Mutex);
#else
            readRealSize = RingBuf_Get(&s_uart1ReadRingBuffer, buf, readSize);
#endif
        }
            break;
#endif

#ifdef USING_UART_PORT_2
        case UART_NUM_2: {
#if PSDK_ARCH_USE_OS
            osMutexWait(s_uart2Mutex, osWaitForever);
            readRealSize = RingBuf_Get(&s_uart2ReadRingBuffer, buf, readSize);
            osMutexRelease(s_uart2Mutex);
#else
            readRealSize = RingBuf_Get(&s_uart2ReadRingBuffer, buf, readSize);
#endif
        }
            break;
#endif

#ifdef USING_UART_PORT_3
        case UART_NUM_3: {
#if PSDK_ARCH_USE_OS
            osMutexWait(s_uart3Mutex, osWaitForever);
            readRealSize = RingBuf_Get(&s_uart3ReadRingBuffer, buf, readSize);
            osMutexRelease(s_uart3Mutex);
#else
            readRealSize = RingBuf_Get(&s_uart3ReadRingBuffer, buf, readSize);
#endif
        }
            break;
#endif

        default:
            return UART_ERROR;
    }

    return readRealSize;
}

/**
 * @brief Write UART data.
 * @param uartNum UART number.
 * @param buf Pointer to buffer used to store data.
 * @param writeSize Size of data to be write.
 * @return Size of data wrote actually.
 */
int UART_Write(E_UartNum uartNum, const uint8_t *buf, uint16_t writeSize)
{
    int writeRealLen;

    switch (uartNum) {

#ifdef USING_UART_PORT_1
        case UART_NUM_1: {
#if PSDK_ARCH_USE_OS
            osMutexWait(s_uart1Mutex, osWaitForever);
            writeRealLen = RingBuf_Put(&s_uart1WriteRingBuffer, buf, writeSize);
            USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
            osMutexRelease(s_uart1Mutex);
#else
            writeRealLen = RingBuf_Put(&s_uart1WriteRingBuffer, buf, writeSize);
            USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
#endif
        }
            break;
#endif

#ifdef USING_UART_PORT_2
        case UART_NUM_2: {
#if PSDK_ARCH_USE_OS
            osMutexWait(s_uart2Mutex, osWaitForever);
            writeRealLen = RingBuf_Put(&s_uart2WriteRingBuffer, buf, writeSize);
            USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
            osMutexRelease(s_uart2Mutex);
#else
            writeRealLen = RingBuf_Put(&s_uart2WriteRingBuffer, buf, writeSize);
            USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
#endif
        }
            break;
#endif

#ifdef USING_UART_PORT_3
        case UART_NUM_3: {
#if PSDK_ARCH_USE_OS
            osMutexWait(s_uart3Mutex, osWaitForever);
            writeRealLen = RingBuf_Put(&s_uart3WriteRingBuffer, buf, writeSize);
            USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
            osMutexRelease(s_uart3Mutex);
#else
            writeRealLen = RingBuf_Put(&s_uart3WriteRingBuffer, buf, writeSize);
            USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
#endif
        }
            break;
#endif

        default:
            return UART_ERROR;
    }

    return writeRealLen;
}

/**
 * @brief UART1 interrupt request handler fucntion.
 */
#ifdef USING_UART_PORT_1
UART_IRQ_HANDLER(1)
#endif

/**
 * @brief UART2 interrupt request handler fucntion.
 */
#ifdef USING_UART_PORT_2
UART_IRQ_HANDLER(2)
#endif

/**
 * @brief UART3 interrupt request handler fucntion.
 */
#ifdef USING_UART_PORT_3
UART_IRQ_HANDLER(3)
#endif

#if 0
void USART1_IRQHandler()
{
    uint8_t data;

    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
        data = (uint8_t)(USART_ReceiveData(USART1) & 0x00FF);
        RingBuf_Put(&s_uart1ReadRingBuffer, &data, 1);
    }

    if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET) {
        if(RingBuf_Get(&s_uart1WriteRingBuffer, &data, 1)) {
            USART_SendData(USART1, data);
        } else {
            USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
        }
    }
}
#endif
