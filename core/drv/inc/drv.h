#ifndef __DRV_H__
#define __DRV_H__

/******************************************************************************************************************************
 *												      Header Files
 ******************************************************************************************************************************/

/*< Controller specific Header file. */
#include <stm32f10x.h>

/*< Portable data types */
#include <stdint.h>

/*< Driver plaform */
#include <drv_platform.h>

/*< Driver header files. */
#include "../clk/api/clk.h"
#include "../flash/api/flash.h"
#include "../gpio/api/gpio.h"
#include "../spi/api/spi.h"
#include "../timer/api/timer.h"
#include "../uart/api/uart.h"

#endif //__HAL_INCLUDES_H__
