#include <app.h>


/*****************************************************************************************************************************************
 * Task Notifications
 * 
 * 1. It has been seen that applications that use FreeRTOS are structured as a set of independent tasks, and that it is likely that these
 *    autonomous tasks will have to communicate with each other so that, collectively, they can provide useful system functionality. 
 * 
 * NOTE: Communicating through intermediary objects
 * 
 * 1. This book has already described various ways in which tasks can communicate with each other. The methods described so far have required
 *    the creation of a communication object. Examples of communication objects include queues, event groups, and various different types 
 *    of semaphore.
 * 2. When a communication object is used, events and data are not sent directly to a receiving task, or a receiving ISR, but are instead sent
 *    to the communication object. Likewise, tasks and ISRs receive events and data from the communication object, rather than directly from the 
 *    task or ISR that sent the event or data.
 * Refer Image1
 * 
 * NOTE: Task Notification - Direct to Task communication
 * 
 * 1. Task notification functionality is optional. To include task notification functionality set configUSE_TASK_NOTIFICATIONS to 1
 *    in FreeRTOSConfig.h
 * 2. When configUSE_TASK_NOTIFICATIONS is set to 1, each task has a ‘Notification State’, which can be either ‘Pending’ or ‘Not-Pending’
 * 3. and a ‘Notification Value’, which is a 32-bit unsigned integer.
 * 4. When a task receives a notification, its notification state is set to pending. When a task reads its notification value,
 *    its notification state is set to not-pending.
 * 5. A task can wait in the Blocked state, with an optional time out, for its notification state to become pending.
 * 
 * NOTE: Task Notifications; Benifits and Limitations
 * 
 * Performance Benenfits of task notifications
 * 1. Using a task notification to send an event or data to a task is significantly faster than using a queue, semaphore or event group
 *    to perform an equivalent operation.
 * 
 * RAM Footprints benefits of task notifications
 * 1. Likewise, using a task notification to send an event or data to a task requires significantly less RAM than using a queue, semaphore
 *    or event group to perform an equivalent operation.
 * 2.  This is because each communication object (queue, semaphore or event group) must be created before it can be used, whereas enabling
 *     task notification functionality has a fixed overhead of just eight bytes of RAM per task.
 * 
 * Limitations of task notifications
 * 
 * Task notifications are faster and use less RAM than communication objects, but task notifications cannot be used in all scenarios.
 * 
 * Sending an Event or Data to an ISR:
 * 1. Communication objects can be used to send events and data from an ISR to a task, and from a task to an ISR.
 * 2. Task notifications can be used to send events and data from an ISR to a task, but they cannot be used to send events or data from
 *    a task to an ISR.
 * 
 * Enabling more than one receiving task:
 * 1. A communication object can be accessed by any task or ISR that knows its handle (which might be a queue handle, semaphore handle,
 *    or event group handle). Any number of tasks and ISRs can process events or data sent to any given communication object.
 * 2. Task notifications are sent directly to the receiving task, so can only be processed by the task to which the notification is sent.
 *    However, this is rarely a limitation in practical cases because, while it is common to have multiple tasks and ISRs sending to the same
 *    communication object, it is rare to have multiple tasks and ISRs receiving from the same communication object.
 * 
 * Buffering multiple data items:
 * 1. A queue is a communication object that can hold more than one data item at a time. Data that has been sent to the queue, but not yet
 *    received from the queue, is buffered inside the queue object.
 * 2. Task notifications send data to a task by updating the receiving task’s notification value. A task’s notification value can only hold
 *    one value at a time.
 * 
 * Broadcasting to more than one task:
 * 1. An event group is a communication object that can be used to send an event to more than one task at a time
 * 2. Task notifications are sent directly to the receiving task, so can only be processed by the receiving task.
 * 
 * Waiting in the blocked state for a send to complete:
 * 1. If a communication object is temporarily in a state that means no more data or events can be written to it (for example, when a queue
 *    is full no more data can be sent to the queue), then tasks attempting to write to the object can optionally enter the Blocked state to
 *    wait for their write operation to complete.
 * 2. If a task attempts to send a task notification to a task that already has a notification pending, then it is not possible for the sending
 *    task to wait in the Blocked state for the receiving task to reset its notification state. As will be seen, this is rarely a limitation in 
 *    practical cases in which a task notification is used.
 *
 *****************************************************************************************************************************************/
