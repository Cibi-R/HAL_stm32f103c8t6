#include <app.h>

static void FreeRTOS_Mutex_Task1(void *pcString);
static void FreeRTOS_Mutex_Task1_sub(void *pcString);

#if 0
static void FreeRTOS_Mutex_Task2(void* pvParameters);
#endif

SemaphoreHandle_t xMutex;
SemaphoreHandle_t xRecursiveMutex;


void FreeRTOS_Mutex_Task1_Create(void)
{
    /**
     * SemaphoreHandle_t xSemaphoreCreateMutex(void);
     * 
     * SemaphoreHandle_t : If NULL is returned then the mutex could not be created because there is insufficient heap memory available for 
     *                     FreeRTOS to allocate the mutex data structures. A non-NULL return value indicates that the mutex has been created.
     **/
    xMutex = xSemaphoreCreateMutex();

    if (xMutex != NULL)
    {
        while (1);
    }

    xTaskCreate(FreeRTOS_Mutex_Task1, "Mutex Task-1", configMINIMAL_STACK_SIZE, NULL, 1u, NULL);

    xTaskCreate(FreeRTOS_Mutex_Task1_sub, "Mutex Task-1 sub", configMINIMAL_STACK_SIZE, NULL, 2u, NULL);
}

#if 0
void FreeRTOS_Mutex_Task2_Create(void)
{
	#if 0
    /* Before a recursive mutex is used it must be explicitly created. */
    xRecursiveMutex = xSemaphoreCreateRecursiveMutex();
    
    /*< */
    configASSERT( xRecursiveMutex );
	#endif
	
    xTaskCreate(FreeRTOS_Mutex_Task2, "Mutex Task-2", configMINIMAL_STACK_SIZE, NULL, 1u, NULL);
}
#endif
static void FreeRTOS_Mutex_Task1(void *pcString)
{
    /* The mutex is created before the scheduler is started, so already exists by the 
       time this task executes.
 
      Attempt to take the mutex, blocking indefinitely to wait for the mutex if it is not available straight away. The call to 
      xSemaphoreTake() will only return when  the mutex has been successfully obtained, so there is no need to check the
      function return value. If any other delay period was used then the code must check that xSemaphoreTake() returns pdTRUE before 
      accessing the shared resource (which in this case is standard out). As noted earlier in this book, indefinite 
      time outs are not recommended for production code. */
    xSemaphoreTake(xMutex, portMAX_DELAY);
    {
        /* The following line will only execute once the mutex has been successfully obtained. */

       
        /* The mutex MUST be given back! */
    }
    xSemaphoreGive(xMutex);
}

static void FreeRTOS_Mutex_Task1_sub(void *pcString)
{
    xSemaphoreTake(xMutex, portMAX_DELAY);
    {
        
    }
    xSemaphoreGive(xMutex);
}
#if 0
static void FreeRTOS_Mutex_Task2(void *pvParameters)
{
	#if 0
    const TickType_t xMaxBlock20ms = pdMS_TO_TICKS( 20 );
    #endif
    for (;;)
    {
		#if 0
        /* Take the recursive mutex. */
        if (xSemaphoreTakeRecursive(xRecursiveMutex, xMaxBlock20ms) == pdPASS)
        {
            /* The recursive mutex was successfully obtained. The task can now access the resource the mutex is protecting. At this point the 
               recursive call count (which is the number of nested calls to xSemaphoreTakeRecursive()) is 1, as the recursive mutex has only 
               been taken once. */

            /* While it already holds the recursive mutex, the task takes the mutex again. In a real application, this is only likely to 
               occur inside a sub-function called by this task, as there is no practical reason to knowingly take the same mutex more than 
               once. The calling task is already the mutex holder, so the second call to xSemaphoreTakeRecursive() does nothing more 
               than increment the recursive call count to 2. */
            xSemaphoreTakeRecursive(xRecursiveMutex, xMaxBlock20ms);
            /* ... */

            /* The task returns the mutex after it has finished accessing the resource the mutex is protecting. At this point the recursive 
               call count is 2, so the first call to xSemaphoreGiveRecursive() does not return the mutex. Instead, it simply decrements the 
               recursive call count back to 1. */
            xSemaphoreGiveRecursive(xRecursiveMutex);
            /* The next call to xSemaphoreGiveRecursive() decrements the recursive call count to 0, so this time the recursive mutex is 
               returned.*/
            xSemaphoreGiveRecursive(xRecursiveMutex);
            /* Now one call to xSemaphoreGiveRecursive() has been executed for every proceeding call to xSemaphoreTakeRecursive(), so the 
               task is no longer the mutex holder. */
        }
		#endif
    }
}
#endif
