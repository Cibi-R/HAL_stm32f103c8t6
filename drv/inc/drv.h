#ifndef __DRV_H__
#define __DRV_H__

/******************************************************************************************************************************
 *												      Typedefs and macros
 ******************************************************************************************************************************/
#define NULL           ((void*)0)
#define null           NULL

#define On             ((uint8_t)(0X01))
#define Off            ((uint8_t)(0X01))

#define True           On
#define False          Off

typedef enum HAL_Status
{
    HAL_Ok,
    HAL_Err,
}HAL_Status;


/******************************************************************************************************************************
 *												      Header Files
 ******************************************************************************************************************************/

/*< Portable data types */
#include <stdint.h>

/*< string library */
#include <string.h>

/*< Controller specific Header file. */
#include "stm32f10x.h"

/*< Driver header files. */
#include "../clock/api/clock.h"
#include "../gpio/api/gpio.h"
#include "../uart/api/uart.h"

#endif //__HAL_INCLUDES_H__
