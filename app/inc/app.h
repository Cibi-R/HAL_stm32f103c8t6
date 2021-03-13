#ifndef __APP_H__
#define __APP_H__

#include <platform.h>

/*< System init header files */
#include "../demo/sys/api/sys.h"

/*< Driver application demos header files. */
#include "../demo/stm32_drv/flash/api/flash_app.h"
#include "../demo/stm32_drv/timer/api/timer_app.h"
#include "../demo/stm32_drv/uart/api/uart_app.h"

/*< FreeRTOS application demo header files.  */
#include "../demo/FreeRTOS/task/api/task1.h"
#include "../demo/FreeRTOS/task/api/task2.h"
#include "../demo/FreeRTOS/semaphore/api/sem.h"

#endif //__APP_H__
