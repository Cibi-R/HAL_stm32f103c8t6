#ifndef __STM32_H__
#define __STM32_H__

/******************************************************************************************************************************
 *												                            Type definiton
 ******************************************************************************************************************************/
/*
typedef enum
{
  HAL_OK = 0x00U,
  HAL_ERROR = 0x01U,
  HAL_BUSY = 0x02U,
  HAL_TIMEOUT = 0x03U
} HAL_StatusTypeDef;
*/
#include  "core/drv/inc/hal_platform.h"
#define   GPIO_H        "core/drv/gpio/api/gpio.h"
#define   UART_H        "core/drv/uart/api/uart.h"
#define   SPI_H         "core/drv/spi/api/spi.h"
#define   FLASH_H       "core/drv/flash/api/flash.h"
#define   TIMER_H       "core/drv/timer/api/timer.h"

#endif //__STM32_H__
