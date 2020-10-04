#ifndef __PLATFORM_H__
#define __PLATFORM_H__

/* Controller specific Header file. */
#include <stm32f10x.h>

/* Portable data types */
#include <stdint.h>

/*< stm32f103c8t6 hardware abstraction layer. */
#include <drv.h>

/*< FreeRTOS Header files */
#include <FreeRTOSConfig.h>
#include <FreeRTOS.h>
#include <task.h>


#define On             ((uint8_t)(0X01))
#define Off            ((uint8_t)(0X01))

#define True           On
#define False          Off

#endif //__PLATFORM_H__
