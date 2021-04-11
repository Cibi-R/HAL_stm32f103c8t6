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

/**
 * SemaphoreHandle_t xSemaphoreCreateBinary( void )
 * 
 * @brief: 
 * 1. FreeRTOS V9.0.0 also includes the xSemaphoreCreateBinaryStatic() function, which allocates the memory required to create a binary
 *    semaphore statically at compile time: Handles to all the various types of FreeRTOS semaphore are stored in a variable of type
 *    SemaphoreHandle_t.
 * @param:
 * void
 * @return:
 * 1. If NULL is returned, then the semaphore cannot be created because there is insufficient heap memory available for FreeRTOS to
 *    allocate the semaphore data structures.
 **/

/**
 * BaseType_t xSemaphoreTake( SemaphoreHandle_t xSemaphore, TickType_t xTicksToWait );
 * 
 * @brief:
 * 1. ‘Taking’ a semaphore means to ‘obtain’ or ‘receive’ the semaphore. The semaphore can be taken only if it is available.
 * 2. All the various types of FreeRTOS semaphore, except recursive mutexes, can be ‘taken’ using the xSemaphoreTake() function.
 * @param:
 * xSemaphore:  1. The semaphore being ‘taken’
 *              2. A semaphore is referenced by a variable of type SemaphoreHandle_t. It must be explicitly created before it can be used.
 * 
 * xTicksToWait:1. The maximum amount of time the task should remain in the Blocked state to wait for the semaphore if it is not already
 *                 available
 *              2. If xTicksToWait is zero, then xSemaphoreTake() will return immediately if the semaphore is not available.
 *              3. The block time is specified in tick periods, so the absolute time it represents is dependent on the tick frequency.
 *                 The macro pdMS_TO_TICKS() can be used to convert a time specified in milliseconds to a time specified in ticks.
 *              4. Setting xTicksToWait to portMAX_DELAY will cause the task to wait indefinitely (without a timeout) if INCLUDE_vTaskSuspend 
 *                 is set to 1 in FreeRTOSConfig.h
 * @return:
 * pdPASS - pdPASS is returned only if the call to xSemaphoreTake() was successful in obtaining the semaphore.
 * pdFALSE- The semaphore is not available.
 * 
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

/*****************************************************************************************************************************************
 * Semaphore
 * 1. Semaphore was proposed by Dijkstra in 1965 which is a very significant technique to manage concurrent processes by using a simple 
 *    integer value, which is known as a semaphore.
 * 2. Semaphore is simply a variable which is non-negative and shared between threads. This variable is used to solve the critical 
 *    section problem and to achieve process synchronization in the multiprocessing environment.
 *    a. Binary semaphore
 *    b. counting semaphore
 *  
 * Binary semaphore:
 * This is also known as mutex lock. It can have only two values – 0 and 1. Its value is initialized to 1. It is used to implement the 
 * solution of critical section problem with multiple processes.
 * 
 * Counting semaphore:
 * Its value can range over an unrestricted domain. It is used to control access to a resource that has multiple instances.
 * 
 * Limitations:
 * 1. One of the biggest limitation of semaphore is priority inversion.
 * 2. Deadlock, suppose a process is trying to wake up another process which is not in sleep state.Therefore a deadlock may block indefinitely.
 * 3. The operating system has to keep track of all calls to wait and to signal the semaphore.
 * 
 * Binary semaphore used for synchronization:
 * 
 * 1. 
 * 
 *****************************************************************************************************************************************/

