#include <app.h>





/*****************************************************************************************************************************************
 * Queue Management:
 * 
 * ‘Queues’ provide a task-to-task, task-to-interrupt, and interrupt-to-task communication mechanism.
 * 
 * Characteristics of a queue:
 * 1. A queue can hold a finite number of fixed size data items. The maximum a queue can hold is called its length. Both the length and
 *    size of each data item are set when the queue is created.
 * 2. Queues are normally used as First In First Out (FIFO) buffers, where data is written to the end (tail) of the queue and removed 
 *    from the front (head) of the queue.
 * 3. It is also possible to write to the front of a queue, and to overwrite data that is already at the front of a queue
 * 
 * There are two ways in which queue behaviour could have been implemented:
 * 1. Queue by copy
 *    Queuing by copy means the data sent to the queue is copied byte for byte into the queue
 * 
 * 2. Queue by Reference
 *    Queuing by reference means the queue only holds pointers to the data sent to the queue, not the data itself.
 * 
 * FreeRTOS uses the queue by copy method. Queuing by copy is considered to be simultaneously more powerful and simpler to use than 
 * queueing by reference because:
 * 
 * 1. Stack variable can be sent directly to a queue, even though the variable will not exist after the function in which it is 
 *    declared has exited.
 * 2. Data can be sent to a queue without first allocating a buffer to hold the data, and then copying the data into the allocated 
 *    buffer
 * 3. The sending task can immediately re-use the variable or buffer that was sent to the queue.
 * 4. The sending task and the receiving task are completely de-coupled the application designer does not need to concern themselves 
 *    with which task ‘owns’ the data, or which task is responsible for releasing the data.
 * 5. Queuing by copy does not prevent the queue from also being used to queue by reference. For example, when the size of the data 
 *    being queued makes it impractical to copy the data into the queue, then a pointer to the data can be copied into the queue 
 *    instead.
 * 6. The RTOS takes complete responsibility for allocating the memory used to store data.
 * 7. In a memory protected system, the RAM that a task can access will be restricted. In that case queueing by reference could only 
 *    be used if the sending and receiving task could both access the RAM in which the data was stored. Queuing by copy does not 
 *    impose that restriction; the kernel always runs with full privileges, allowing a queue to be used to pass data across memory 
 *    protection boundaries.
 * 
 * NOTE: Access by multiple task
 * 1. Queues are objects in their own right that can be accessed by any task or ISR that knows of their existence.
 * 2. Any number of tasks can write to the same queue, and any number of tasks can read from the same queue. In practice it is very
 *    common for a queue to have multiple writers, but much less common for a queue to have multiple readers.
 * 
 * NOTE: Blocking on Queue Reads
 * 1. When a task attempts to read from a queue, it can optionally specify a ‘block’ time. This is the time the task will be kept in 
 *    the Blocked state to wait for data to be available from the queue, should the queue already be empty.
 * 2. A task that is in the Blocked state, waiting for data to become available from a queue, is automatically moved to the Ready 
 *    state when another task or interrupt places data into the queue.
 * 3. The task will also be moved automatically from the Blocked state to the Ready state if the specified block time expires before
 *    data becomes available.
 * 4. Queues can have multiple readers, so it is possible for a single queue to have more than one task blocked on it waiting for data.
 *    When this is the case, only one task will be unblocked when data becomes available.
 * 5. The task that is unblocked will always be the highest priority task that is waiting for data. If the blocked tasks have equal 
 *    priority, then the task that has been waiting for data the longest will be unblocked.
 * 
 * NOTE: Blocking on Queue Writes
 * 1. Just as when reading from a queue, a task can optionally specify a block time when writing to a queue.
 * 2. In this case, the block time is the maximum time the task should be held in the Blocked state to wait for space to become 
 *    available on the queue, should the queue already be full.
 * 3. Queues can have multiple writers, so it is possible for a full queue to have more than one task blocked on it waiting to complete
 *    a send operation. When this is the case, only one task will be unblocked when space on the queue becomes available.
 * 4. The task that is unblocked will always be the highest priority task that is waiting for data. If the blocked tasks have equal 
 *    priority, then the task that has been waiting for data the longest will be unblocked.
 * 
 * NOTE: Blocking on Multiple Queues
 * 1. Queues can be grouped into sets, allowing a task to enter the Blocked state to wait for data to become available on any of the
 *    queues in the set. 
 * 
 *****************************************************************************************************************************************/
