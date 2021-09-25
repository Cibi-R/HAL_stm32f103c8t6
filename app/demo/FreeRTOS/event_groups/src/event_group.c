#include <app.h>

/**
 * EventGroupHandle_t xEventGroupCreate( void );
 * 
 * @brief: Event groups are referenced using variables of type EventGroupHandle_t. The xEventGroupCreate() API function is used to create
 *         an event group, and returns an EventGroupHandle_t to reference the event group it creates. FreeRTOS V9.0.0 also includes the
 *         xEventGroupCreateStatic() function, which allocates the memory required to create an event group statically at compile time:
 *         An event group must be explicitly created before it can be used.
 * @param: void
 * @return: If NULL is returned, then the event group cannot be created because there is insufficient heap memory available for FreeRTOS
 *          to allocate the event group data structures. Chapter 2 provides more information on heap memory management.
 **/

/**
 * EventBits_t xEventGroupSetBits( EventGroupHandle_t xEventGroup,const EventBits_t uxBitsToSet );
 * 
 * @brief: The xEventGroupSetBits() API function sets one or more bits in an event group, and is typically used to notify a task that the
 *         events represented by the bit, or bits, being set has occurred.
 *         Never call xEventGroupSetBits() from an interrupt service routine. The interrupt-safe version xEventGroupSetBitsFromISR() should
 *         be used in its place.
 * @param: 
 * xEventGroup : The handle of the event group in which bits are being set. The event group handle will have been returned from the call
 *               to xEventGroupCreate() used to create the event group.
 * uxBitsToSet : A bit mask that specifies the event bit, or event bits, to set to 1 in the event group. The value of the event group is
 *               updated by bitwise ORing the event group’s existing value with the value passed in uxBitsToSet.
 *               As an example, setting uxBitsToSet to 0x04 (binary 0100) will result in event bit 3 in the event group becoming set 
 *               (if it was not already set), while leaving all the other event bits in the event group unchanged.
 * @return: The value of the event group at the time the call to xEventGroupSetBits() returned. Note that the value returned will not
 *          necessarily have the bits specified by uxBitsToSet set, because the bits may have been cleared again by a different task.
 **/

/**
 * BaseType_t xEventGroupSetBitsFromISR( EventGroupHandle_t xEventGroup,const EventBits_t uxBitsToSet, BaseType_t *pxHigherPriorityTaskWoken );
 * 
 * @brief: 
 * 1. Giving a semaphore is a deterministic operation because it is known in advance that giving a semaphore can result in at most one task
 *    leaving the Blocked state. When bits are set in an event group it is not known in advance how many tasks will leave the Blocked state,
 *    so setting bits in an event group is not a deterministic operation.
 * 2. The FreeRTOS design and implementation standard does not permit non-deterministic operations to be performed inside an interrupt service
 *    routine, or when interrupts are disabled. For that reason, xEventGroupSetBitsFromISR() does not set event bits directly inside the 
 *    interrupt service routine, but instead defers the action to the RTOS daemon task.
 * @param:
 * xEventGroup : The handle of the event group in which bits are being set. The event group handle will have been returned from the call to 
 *               xEventGroupCreate() used to create the event group.
 * uxBitsToSet : A bit mask that specifies the event bit, or event bits, to set to 1 in the event group. The value of the event group is
 *               updated by bitwise ORing the event group’s existing value with the value passed in uxBitsToSet.
 * pxHigherPriorityTaskWoken : 
 *               xEventGroupSetBitsFromISR() does not set the event bits directly inside the interrupt service routine, but instead defers 
 *               the action to the RTOS daemon task by sending a command on the timer command queue. If the daemon task was in the 
 *               Blocked state to wait for data to become available on the timer command queue, then writing to the timer command queue will 
 *               cause the daemon task to leave the Blocked state. If the priority of the daemon task is higher than the priority of the 
 *               currently executing task (the task that was interrupted), then, internally, xEventGroupSetBitsFromISR() will set 
 *               pxHigherPriorityTaskWoken to pdTRUE.
 *               If xEventGroupSetBitsFromISR() sets this value to pdTRUE,then a context switch should be performed before the interrupt 
 *               is exited. This will ensure that the interrupt returns directly to the daemon task, as the daemon task will be the highest 
 *               priority Ready state task.
 * @return:
 * pdPASS : pdPASS will be returned only if data was successfully sent to the timer command queue.
 * pdFAIL : pdFALSE will be returned if the ‘set bits’ command could not be written to the timer command queue because the queue was already full. 
 **/

/**
 * EventBits_t xEventGroupWaitBits( const EventGroupHandle_t xEventGroup, const EventBits_t uxBitsToWaitFor,
 *                                  const BaseType_t xClearOnExit, const BaseType_t xWaitForAllBits,
 *                                  TickType_t xTicksToWait );
 * 
 * @brief: The xEventGroupWaitBits() API function allows a task to read the value of an event group, and optionally wait in the Blocked state
 *         for one or more event bits in the event group to become set, if the event bits are not already set.
 *         1. The condition used by the scheduler to determine if a task will enter the Blocked state, and when a task will leave the Blocked
 *            state, is called the ‘unblock condition’. The unblock condition is specified by a combination of the uxBitsToWaitFor and the
 *            xWaitForAllBits parameter values
 *         2. A task will not enter the Blocked state if its unblock condition is met at the time xEventGroupWaitBits() is called
 *         3. Examples of conditions that will result in a task either entering the Blocked state, or exiting the Blocked state, are provided
 *            in Table image2 and image3. image2 and image3 only shows the least significant four binary bits of the event group and
 *            uxBitsToWaitFor values—the other bits of those two values are assumed to be zero.
 *         4. The calling task specifies bits to test using the uxBitsToWaitFor parameter, and it is likely the calling task will need to clear
 *            these bits back to zero after its unblock condition has been met. Event bits can be cleared using the xEventGroupClearBits()
 *            API function, but using that function to manually clear event bits will lead to race conditions in the application code 
 *            if:
 *            a. There is more than one task using the same event group
 *            b. Bits are set in the event group by a different task, or by an interrupt service routine.
 *         5. The xClearOnExit parameter is provided to avoid these potential race conditions. If xClearOnExit is set to pdTRUE, then
 *            the testing and clearing of event bits appears to the calling task to be an atomic operation (uninterruptable by other tasks
 *            or interrupts).
 * 
 * 
 * @param: 
 * xEventGroup : The handle of the event group that contains the event bits being read. The event group handle will have been returned from
 *               the call to xEventGroupCreate() used to create the event group.
 * uxBitsToWaitFor : uxBitsToWaitFor specifies which event bits in the event group to test (A bit mask that specifies the event bit, or event bits, 
 *                   to test in the event group. )
 * xClearOnExit : If the calling task’s unblock condition has been met, and xClearOnExit is set to pdTRUE, then the event bits specified by
 *                uxBitsToWaitFor will be cleared back to 0 in the event group before the calling task exits the xEventGroupWaitBits() API
 *                function.
 *                If xClearOnExit is set to pdFALSE, then the state of the event bits in the event group are not modified by the
 *                xEventGroupWaitBits() API function.
 * xWaitForAllBits : Explained in brief section and image2, image3
 * xTicksToWait : The maximum amount of time the task should remain in the Blocked state to wait for its unblock condition to be met.
 *                xEventGroupWaitBits() will return immediately if xTicksToWait is zero, or the unblock condition is met at the time
 *                xEventGroupWaitBits() is called
 *                Setting xTicksToWait to portMAX_DELAY will cause the task to wait indefinitely (without timing out), provided
 *                INCLUDE_vTaskSuspend is set to 1 in FreeRTOSConfig.h.
 * 
 * @return:
 * EventBits_t :
 * If xEventGroupWaitBits() returned because the calling task’s unblock condition was met, then the returned value is the value of the
 * event group at the time the calling task’s unblock condition was met (before any bits were automatically cleared if xClearOnExit was
 * pdTRUE). In this case the returned value will also meet the unblock condition.
 * If xEventGroupWaitBits() returned because the block time specified by the xTicksToWait parameter expired, then the returned value is the
 * value of the event group at the time the block time expired. In this case the returned value will not meet the unblock condition.
 *  
 **/

#define mainFIRST_TASK_BIT   0X01UL /*< Event bit 0 which is set by task 1*/
#define mainSECOND_TASK_BIT  0X02UL /*< Event bit 1 which is set by task 2*/
#define mainISR_BIT                 /*< Event bit 2 which is set by ISR */

/*< Create event group handle */
EventGroupHandle_t xEventGroup;

static void vEventBitSettingTask(void *pvParameters)
{
    const TickType_t xDelay200ms = pdMS_TO_TICKS(200UL);
    // const TickType_t xDontBlock = 0;

    for (;;)
    {
        vTaskDelay(xDelay200ms);
    }
}

static void vEventBitReadingTask(void *pvParameters)
{

}

static void vInterruptGenerator(void *pvParameters)
{

}

void FreeRTOS_EventGroup_Demo(void)
{
    xEventGroup = xEventGroupCreate();

#if 0
    if (xEventGroup == NULL)
    {
        while (1);
    }
#endif

    xTaskCreate(vEventBitSettingTask, "Event SetBit Task", configMINIMAL_STACK_SIZE, NULL, 2, NULL);

    xTaskCreate(vEventBitReadingTask, "Event ReadBit Task", configMINIMAL_STACK_SIZE, NULL, 2, NULL);

    xTaskCreate(vInterruptGenerator, "INT Generator Task", configMINIMAL_STACK_SIZE, NULL, 2, NULL);

    vTaskStartScheduler();
}
