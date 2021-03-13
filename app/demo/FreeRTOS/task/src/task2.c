#include <app.h>


void FreeRTOS_Task_5(void *pvParameters);
void FreeRTOS_Task_5sub(void* pvParameters);

TaskHandle_t TaskHandle5;
TaskHandle_t TaskHandle5sub;

void FreeRTOS_Task_5_Create(void)
{
    if (xTaskCreate(FreeRTOS_Task_5, "Task-5", configMINIMAL_STACK_SIZE, NULL, 2U, &TaskHandle5) == pdFAIL)
    {
        while (1);
    }
}

void FreeRTOS_Task_5(void *pvParameters)
{
    /**
     * void vTaskPrioritySet( TaskHandle_t pxTask,
     *                        UBaseType_t uxNewPriority
     * )
     * 
     * pxTask  :  The handle of the task whose priority is being modified (the subject task), A task can its own priority by passing NULL
     *            in place of a valid task handle.
     * uxNewPriority : The priority of which the subject task is set.
     * 
     * UBaseType_t uxPriorityGet( TaskHandle_t pxTask);
     * )
     * 
     * pxTask : The handle of a task. A task can query its own priority by passing NULL
     * return : The priority currently assigned to the task being queried.
     * 
     **/
#if 0
    UBaseType_t uxPriority;
#endif
    volatile uint8_t uxThreadStatus = 1u;

    while (uxThreadStatus)
    {
        /**
         * NOTE: 
         * Since the priority of the FreeRTOS_Task_5sub is higher than FreeRTOS_Task_5, the scheduler will immediately move this task to 
         * running state from ready state as soon as it is created.
         * 
         * FreeRTOS_Task_5sub task does nothing but deleting itself.
         **/
        if (xTaskCreate(FreeRTOS_Task_5sub, "Task-5 sub", configMINIMAL_STACK_SIZE, NULL, 3U, &TaskHandle5sub))
        {
            /*< If task not created delete the parent task. */
            vTaskDelete(NULL);
        }

        /**
         * NOTE:
         * During the delay period, the calling task will be blocked and moved to blocked state and since there is no application task that
         * can be moved from ready to running state. Idle task will start executing and resource of FreeRTOS_Task_5sub will be cleared there.
         **/
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    /**
     * vTaskDelete( TaskHandle_t pxTaskToDelete
     * );
     * pxTaskToDelete  :  The handle of the task that is to be deleted. A task can delete itself by passing NULL.
     **/
    vTaskDelete(NULL);
}

void FreeRTOS_Task_5sub(void* pvParameters)
{
    /*< Both API can be used to delete the task */
#if 0
    vTaskDelete(NULL);
#endif
    vTaskDelete(TaskHandle5sub);
}


/*****************************************************************************************************************************************
 * Changing the task priority:
 * 1. The vTaskPrioritySet() API funciton can be used to chang the priority of any task after the scheduler has been started.
 * 2. vTaskPrioritySet() is only available when INCLUDE_vTaskPrioritySet is set to 1 in FreeRTOSConfig.h
 * 3. uxTaskPriorityGet() API function can be used to query the priority of a task. Note that this function is available only when 
 *    INCLUDE_uxTakPriorityGet is set to 1 in FreeRTOSConfig.h
 * 4. A task can use vTaskDelete() API function to delete itself and any other task. This API is available only when INCLUDE_vTaskDelete
 *    is set to 1 in FreeRTOSConfig.h
 * 5. Deleted task do no exist and cannot enter the running state again.  
 * 6. It is the responsibility of the idle task to free memory allocated to tasks that have been deleted. Therefor it is important that
 *    applications using vTaskDelete() API function do not completely starve the idle task of all processing time.
 * NOTE: 
 * only memory allocated to a task by the kernel itself will be freed automatically when the task is deleted. Any memory or other resources
 * that the implementation of the task allocated must be freed explicitly
 * 
 * NOTE:
 * Scheduling algorithm:
 * 
 * Recap of task states and events:
 * 1. A task acutally running is in running state. On a single core processor there can only be one task in the running state at any
 *    given point in time.
 * 2. Tasks that are in ready state are available to be selected by the scheduler as the task to enter running state.
 * 3. Task can wait in the blocked state for an event and are automatically moved back to the ready state when the event occurs.
 *    The events are
 *    1. Temporal events - delay
 *    2. Synchronization events sent from a task or interrupt service routine
 *       a. Task notification
 *       b. Queue
 *       c. Event groups 
 *       d. Semaphore
 *       e. Mutex
 * 
 * Configuring the scheduling algorithm:
 * 
 * 
 *****************************************************************************************************************************************/

