#include <app.h>

/**
 * APIs to handle semaphore
 * 1. vSemaphoreCreateBinary(xsemaphoreHandle);
 *    a. The semaphore is first created in empty state, so it must be give/post first
 * 2. vSemaphoreGive(vsemaphoreHandle);
 *    a. The above function is used to give/post the semaphore
 * 3. vSemaphoreTake(vsemaphoreHandle, waitTime);
 *    a. The above function is used to take/pend the semaphore
 *    c. waitTime is of type 
 *    d. on semaphore take failure it returns pdFAIL
 * 4. In order to give/post semaphore inside interrupt xSemaphoreGiveFromISR(XSemaphoreHandle *)
 **/

#define SEM_WAIT_TIME 1000U

xSemaphoreHandle mySemHandleBinary;

void BinarySemaphoreAPIs(void)
{
    /*< Creates binary semaphore */
    vSemaphoreCreateBinary(mySemHandleBinary);

    /*< Give/Post binary semaphore */
    xSemaphoreGive(mySemHandleBinary);

    /*< Take/Pend binary semaphore */
    // xSemaphoreTake(mySemHandleBinary, SEM_WAIT_TIME);
    xSemaphoreTake(mySemHandleBinary, portMAX_DELAY);     /*< We can also use the macro from FreeRTOS */
    

#if 0
    xSemaphoreGiveFromISR(mySemHandleBinary);
#endif

    /*< Delete semaphore */
    vSemaphoreDelete(mySemHandleBinary);
}

void CountingSemaphoreAPIs(void)
{

}
