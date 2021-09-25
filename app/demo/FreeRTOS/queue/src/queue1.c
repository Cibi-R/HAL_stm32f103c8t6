#include <app.h>

extern void FreeRTOS_Queue1_Create(void);

static void vSenderTask(void *pvParameters);

static void vReceiverTask(void *pvParameters);

/**
 * QueueHandle_t xQueueCreate( UBaseType_t uxQueueLength, UBaseType_t uxItemSize );
 * 
 * @brief  :  
 * 1. A queue must be explicitly created before it can be used.
 * 2. Queues are referenced by handles, which are variables of type QueueHandle_t. The xQueueCreate() API function creates a queue and returns 
 *    a QueueHandle_t that references the queue it created.
 * 3. FreeRTOS V9.0.0 also includes the xQueueCreateStatic() function, which allocates the memory required to createa queue statically at 
 *    compile time
 * 4. The RAM is used to hold both the queue data structures and the items that are contained in the queue. xQueueCreate() will return NULL if 
 *    there is insufficient heap RAM available for the queue to be created.
 * 
 * @param  :
 * uxQueueLength  :  The maximum number of items that the queue being created can hold at any one time
 * uxItemSize     :  The size in bytes of each data item that can be stored in the queue.
 * 
 * @return : If NULL is returned, then the queue cannot be created because there is insufficient heap memory available for FreeRTOS to allocate 
 *           the queue data structures and storage area.
 *           A non-NULL value being returned indicates that the queue has been created successfully. The returned value should be stored as the 
 *           handle to the created queue.
 * 
 * After queue has been created the xQueueReset() API function can be used to return the queue to its original empty state.
 **/

/**
 * BaseType_t xQueueSendToFront( QueueHandle_t xQueue,const void * pvItemToQueue, TickType_t xTicksToWait );
 * 
 * @brief: xQueueSendToFront() is used to send data to the front (head) of a queue.
 * 
 * BaseType_t xQueueSendToBack( QueueHandle_t xQueue, const void * pvItemToQueue, TickType_t xTicksToWait );
 * 
 * @brief: xQueueSendToBack() is used to send data to the back (tail) of a queue
 * 
 * @param: 
 * xQueue  : The handle of the queue to which the data is being sent (written). The queue handle will have been returned from the call to
 *           xQueueCreate() used to create the queue.
 * pvItemToQueue : A pointer to the data to be copied into the queue, The size of each item that the queue can hold is set when the queue is
 *                 created, so this many bytes will be copied from pvItemToQueue into the queue storage area.
 * xTicksToWait  : 1. The maximum amount of time the task should remain in the Blocked state to wait for space to become available on the queue,
 *                    should the queue already be full.
 *                 2. Both xQueueSendToFront() and xQueueSendToBack() will return immediately if xTicksToWait is zero and the queue is already full.
 *                    The block time is specified in tick periods, so the absolute time itrepresents is dependent on the tick frequency. The macro
                      pdMS_TO_TICKS() can be used to convert a time specified in milliseconds into a time specified in ticks.
                   3. Setting xTicksToWait to portMAX_DELAY will cause the task to wait indefinitely (without timing out),  
                      provided INCLUDE_vTaskSuspend is set to 1 in FreeRTOSConfig.h.
 *
 * @return: There are two possible return values:
 *          1. pdPASS
 *             a. pdPASS will be returned only if data was successfully sent to the queue.
 *             b. If a block time was specified (xTicksToWait was not zero), then it is possible the calling task was placed into the 
 *                Blocked state, to wait for space to become available in the queue, before the function returned, but data was successfully
 *                written to the queue before the block time expired.
 *          2. errQUEUE_FULL
 *             a. errQUEUE_FULL will be returned if data could not be written to the queue because the queue was already full.
 *             b. If a block time was specified (xTicksToWait was not zero) then the calling task will have been placed into the Blocked
 *                state to wait for another task or interrupt to make space in the queue, but the specified block time expired before that
 *                happened.
 * 
 **/

/**
 * BaseType_t xQueueReceive( QueueHandle_t xQueue,void * const pvBuffer, TickType_t xTicksToWait );
 * 
 * @brief: 1. xQueueReceive() is used to receive (read) an item from a queue. The item that is received is removed from the queue.
 *         2. Never call xQueueReceive() from an interrupt service routine. The interrupt-safexQueueReceiveFromISR()
 * 
 *
 * @param:
 * QueueHandle_t  :  BaseType_t xQueueReceive( QueueHandle_t xQueue,void * const pvBuffer, TickType_t xTicksToWait );
 * pvBuffer       :  1. A pointer to the memory into which the received data will be copied
 *                   2. The size of each data item that the queue holds is set when the queue is created. The memory pointed to by pvBuffer
 *                      must be at least large enough to hold that many bytes.
 * xTicksToWait   :  1. The maximum amount of time the task should remain in the Blocked state to wait for data to become available on the queue,
 *                      should the queue already be empty
 *                   2. The block time is specified in tick periods, so the absolute time it represents is dependent on the tick frequency.
 *                      The macro pdMS_TO_TICKS() can be used to convert a time specified in milliseconds into a time specified in ticks.
 *                   3. Setting xTicksToWait to portMAX_DELAY will cause the task to wait indefinitely (without timing out) provided
 *                      INCLUDE_vTaskSuspend is set to 1 in FreeRTOSConfig.h.
 * 
 * @return : There are two possible return values:
 *           1. pdPASS
 *           2. pdPASS will be returned only if data was successfully read from the queue.
 *           3. If a block time was specified (xTicksToWait was not zero), then it is possible the calling task was placed into the Blocked state,
 *              to wait for data to become available on the queue, but data was successfully read from the queue before the block time expired.
 * 
 *           1. errQUEUE_EMPTY
 *           2. errQUEUE_EMPTY will be returned if data cannot be read from the queue because the queue is already empty.
 *           3. If a block time was specified (xTicksToWait was not zero,) then the calling task will have been placed into the Blocked state
 *              to wait for another task or interrupt to send data to the queue, but the block time expired before that happened.
 **/

/**
 * UBaseType_t uxQueueMessagesWaiting( QueueHandle_t xQueue );
 * 
 * @brief: uxQueueMessagesWaiting() is used to query the number of items that are currently in a queue. Never call uxQueueMessagesWaiting() 
 *         from an interrupt service routine. The interrupt safe uxQueueMessagesWaitingFromISR() should be used in its place
 * 
 * @param:
 * xQueue : The handle of the queue being queried. The queue handle will have been returned from the call to xQueueCreate() used to 
 *          create the queue.
 * 
 * @return: The number of items that the queue being queried is currently holding. If zero is returned, then the queue is empty.
 * 
 **/



///Example1

/* Declare a variable of type QueueHandle_t. This is used to store the handle
to the queue that is accessed by all three tasks. */
QueueHandle_t xQueue;

void FreeRTOS_Queue1_Create(void)
{
    /* The queue is created to hold a maximum of 5 values, each of which is
      large enough to hold a variable of type int32_t. */
    xQueue = xQueueCreate(5, sizeof(int32_t));

    if (xQueue != NULL)
    {
        /* Create two instances of the task that will send to the queue. The task
         parameter is used to pass the value that the task will write to the queue,
         so one task will continuously write 100 to the queue while the other task 
         will continuously write 200 to the queue. Both tasks are created at
         priority 1. */
        /* Both tasks that send to the queue have an identical priority. This causes the two sending 
         tasks to send data to the queue in turn. */
        xTaskCreate(vSenderTask, "Sender1", 1000, (void *)100, 1, NULL);
        xTaskCreate(vSenderTask, "Sender2", 1000, (void *)200, 1, NULL);

        /* Create the task that will read from the queue. The task is created with
            priority 2, so above the priority of the sender tasks. */
        xTaskCreate(vReceiverTask, "Receiver", 1000, NULL, 2, NULL);
    }

    else
    {
        /* The queue could not be created. */
    }

    /* If all is well then main() will never reach here as the scheduler will 
            now be running the tasks. If main() does reach here then it is likely that 
            there was insufficient FreeRTOS heap memory available for the idle task to be 
            created. Chapter 2 provides more information on heap memory management. */
    for (;;)
        ;
}

static void vSenderTask(void *pvParameters)
{
    int32_t lValueToSend;
    BaseType_t xStatus;
    /* Two instances of this task are created so the value that is sent to the
      queue is passed in via the task parameter - this way each instance can use 
      a different value. The queue was created to hold values of type int32_t, 
      so cast the parameter to the required type. */
    lValueToSend = (int32_t)pvParameters;
    /* As per most tasks, this task is implemented within an infinite loop. */
    for (;;)

    {
        /* Send the value to the queue.
            The first parameter is the queue to which data is being sent. The 
            queue was created before the scheduler was started, so before this task
            started to execute.
            The second parameter is the address of the data to be sent, in this case
            the address of lValueToSend.
            The third parameter is the Block time – the time the task should be kept
            in the Blocked state to wait for space to become available on the queue
            should the queue already be full. In this case a block time is not 
            specified because the queue should never contain more than one item, and
            therefore never be full. */
        xStatus = xQueueSendToBack(xQueue, &lValueToSend, 0);
        if (xStatus != pdPASS)
        {
            /* The send operation could not complete because the queue was full -
                  this must be an error as the queue should never contain more than 
                  one item! */
            #if 0
            vPrintString("Could not send to the queue.\r\n");
            #endif
        }
    }
}

static void vReceiverTask(void *pvParameters)
{
    /* Declare the variable that will hold the values received from the queue. */
    int32_t lReceivedValue;
    BaseType_t xStatus;
    const TickType_t xTicksToWait = pdMS_TO_TICKS(100);

    /* This task is also defined within an infinite loop. */
    for (;;)
    {
        /* This call should always find the queue empty because this task will
           immediately remove any data that is written to the queue. */
        if (uxQueueMessagesWaiting(xQueue) != 0)
        {
            #if 0
            vPrintString("Queue should have been empty!\r\n");
            #endif
        }
        /*  Receive data from the queue.
            The first parameter is the queue from which data is to be received. The
            queue is created before the scheduler is started, and therefore before this
            task runs for the first time.
            The second parameter is the buffer into which the received data will be
            placed. In this case the buffer is simply the address of a variable that
            has the required size to hold the received data.
            The last parameter is the block time – the maximum amount of time that the
            task will remain in the Blocked state to wait for data to be available 
            should the queue already be empty. */
        xStatus = xQueueReceive(xQueue, &lReceivedValue, xTicksToWait);

        if (xStatus == pdPASS)
        {
            /*  Data was successfully received from the queue, print out the received
                value. */
            #if 0
            vPrintStringAndNumber("Received = ", lReceivedValue);
            #endif
        }
        else
        {
            /*  Data was not received from the queue even after waiting for 100ms.
                This must be an error as the sending tasks are free running and will be
                continuously writing to the queue. */
            #if 0
            vPrintString("Could not receive from the queue.\r\n");
            #endif
        }
    }
}
