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


