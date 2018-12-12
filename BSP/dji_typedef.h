/**
 ******************************************************************************
 * @file    dji_ringbuffer.h
 * @version V1.0.0
 * @date    2017/11/10
 * @brief   The file defines some type aliases used.
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
#ifndef TRANSFER_RING_DJI_TYPEDEF_H
#define TRANSFER_RING_DJI_TYPEDEF_H

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


/* Exported constants --------------------------------------------------------*/
#define STATIC              static

#define INTERFACE
#define RTN_SUCCESS     0
#define RTN_FAILURE     (-1)

#define BOOL            uint8_t

#ifndef TRUE
#define TRUE (1)
#endif

#ifndef FALSE
#define FALSE (0)
#endif

#ifndef __weak_symbol
#define	__weak_symbol	__attribute__((__weak__))
#endif

/* Exported macros -----------------------------------------------------------*/
#define _Error_Handler() while(1) \
{ \
    LOG_ERROR("ErrorHandler  file = %s, line = %d \r\n", __FILE__, __LINE__); \
    osDelay(1000); \
}

#define Error_Handler() _Error_Handler()

/* Exported types ------------------------------------------------------------*/
typedef void                VOID;
typedef char                CHAR;
typedef unsigned char       Bool;
typedef unsigned char       BOOLEAN;


typedef enum {
    RT_STAT_OK              = 0x00,
    RT_STAT_ERR_TIMEOUT     = 0x01,
    RT_STAT_ERR_ALLOC       = 0x02,
    RT_STAT_ERR_BUSY        = 0x03,
    RT_STAT_ERR_PARAM       = 0x04,
    RT_STAT_ERR_ACK_LEN     = 0x05,

    RT_STAT_ERR             = 0xFF,
}E_RtStat;

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

#endif //TRANSFER_RING_DJI_TYPEDEF_H
