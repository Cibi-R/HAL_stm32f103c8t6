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
 *    1. Temporal events - delay (timers)
 *    2. Synchronization events sent from a task or interrupt service routine
 *       a. Task notification
 *       b. Queue
 *       c. Event groups 
 *       d. Semaphore
 *       e. Mutex
 * 
 * Configuring the scheduling algorithm:
 * 
 * 1. The scheduling algorithm is the software routine that decides which ready state task transition into the running state.
 * 2. The scheduling algorithm can changed using configUSE_PREEMPTION and configUSE_TIME_SLICING(not defined in the current version) 
 *    configuration constants
 * 3. configUSE_TICKLESS_IDLE is also an important factor in scheduling algorithm but not defined in the current freeRTOS version
 * 4. In all possible configuration the freeRTOS scheduler will ensure tasks that share a priority are selected to enter the running 
 *    state in turn. The 'take it in turn' policy is often refered to as 'round robin scheduling' a round robin scheduling does not
 *    guarentee time is shared equally between tasks of equal priority. only that ready state tasks of equal priority will enter 
 *    the running state in turn.
 * 
 * Prioritized Pre-emptive scheduling with time slicing:
 * 1.  The below configuration sets the FreeRTOS scheduler to use a scheduling algorithm called  "Fixed priority pre-emptive scheduling
 *     with time slicing" 
 *     configUSE_PREEMPTION   1
 *     configUSE_TIME_SLICING 1
 * 2. This scheduling algorithm is used by most small RTOS application
 * 
 * An explantion of the terms used to describe the scheduling policy:
 * 
 * Fixed Priority:
 * 1. Scheduling algorithm described as "Fixed priority" do not change the priority assigned to the tasks being scheduled.
 * 2. But also do not prevent the tasks themselves from changing their own priority or that of other tasks.
 * 
 * Pre-emptive:
 * 1. Pre-emptive scheduling algorithm will immediately 'pre-empt' the running task if a task that has a priority higher than the running state
 *    task enters the ready state task.
 * 2. Being pre-empted means being involuntarily (without explicitly yielding or blocking) moved out of running state and into ready state to
 *    allow the different task to enter the running state.
 * 
 * Time slicing:
 * 1. Time slicing is used to share processing time between tasks of equal priority. even when the tasks do not excplicitly yield or enter
 *    the blocked state. 
 * 2. Scheduling algorithm described as using "Time Slicing" will select the new task to enter the running state at the end of each time slice
 *    if there are other ready state tasks that have the same priority as the running task. A time slice is equal to the time between two RTOS
 *    tick interrupts.
 * 
 * IDLE tasd configuration:
 * 1. if configIDLE_SHOULD_YIELD is set to 0 then the idle task will remain in the running state for the entierity of its time slice
 *    unless it is preempted by a higher priority task
 * 2. if configIDLE_SHOUDL_YIELD is set to 1 then the idle task will yield on each iteration of its loop if there are other idle priority
 *    tasks in the ready state.
 * 
 * Prioritized Pre-emptive scheduling without time slicing:
 * 
 * Prioritized preemptive scheduling without time slicing maintains the same task selection and preemption algorithm as described in the
 * with time slicing algorithm.
 * But does not use time slicing to share processing time between tasks of equal priority.
 * 
 * Use below configuration for above algorithm:
 * 1. configUSE_PREEMPTION   1
 * 2. configUSE_TIME_SLICING 0
 * 
 * When time slice is not used, then the scheduler will only select a new task to enter the running state on below condition:
 * 1. A higher priority task enters the ready state.
 * 2. The task in running state enters the blocked or suspended state.
 * 
 * a. There are fewer task context switches when time slicing not used, therefore turning time slicing off results in a reduction in the
 *    scheduler processing overhead.
 * b. However, turning time slicing off can also result in tasks of equal priority receiving greatly different amounts of processing time
 * c. running the scheduler without time slicing is considered an advanced technique that should only be used by experienced users
 * 
 * Co-operative scheduling:
 * FreeRTOS can also support co-operating scheduling, The FreeRTOSConfig.h settings that configure the FreeRTOS scheduler to use 
 * co-operative scheduling are
 * 
 * configUSE_PREEMPTION   0
 * configUSE_TIME_SLICING any value
 * 
 * 1. When co-operative scheduler is used, a context switch will only occur when the running state task enters the blocked state. or the
 *    running state task excplitly yields (manually requests a rechedule) by calling taskYIELD()
 * 2. Tasks are never preempted, so time slicing cannot be used.
 * 3. When the running state task has lower priority than the task in ready state also the preemption will not happen.
 * 4. When the running sate task moved to blocked state, the scheduler will select the task in the ready state based on the priority,
 *    again the selected task will run till it moved to blocked state.
 * 
 *****************************************************************************************************************************************/

