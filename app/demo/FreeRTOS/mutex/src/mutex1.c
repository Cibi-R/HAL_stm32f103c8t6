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


/*****************************************************************************************************************************************
 * 
 * NOTE: Mutexes (and Binary semaphores):
 * 1. A mutex is a special type of binary semaphore that is used to control access to a resouce that is shared between two or more tasks.
 * 2. The word mutex originates from MUTual EXclusion, configUSE_MUTEXES must be set to 1 in FreeRTOSConfig.h for mutexes to be available
 * 
 * Even though mutexes and semaphore shares many characteristics, The primary difference is what happens to the semaphore after it has been
 * obtained.
 * 1. A semaphore that is used for mutual exclusion must always be returned.
 * 2. A semaphore that is used for synchronization is normally discarded and not returned.
 * 
 * Scenarios where mutex is used works purely through the diciplne of the application writer. 
 * 
 * 1. xSemaphoreCreateMutex() API is used to create mutex, mutex is a type of semaphore, handle to all the various types of FreeRTOS semaphore
 *    are stored in a variable of type SemaphoreHandle_t.
 * 2. xSemaphoreCreateMutexStatic(), can be used to create mutex statically (allocates memory at compile time). 
 * Before mutex can be used it must be created.
 * 
 * NOTE: Priority Inversion:
 * A higher priority task being delayed by a lower priority is called priority inversion. 
 * 
 * Consider below scenario where there tasks are created, task1, task2, task3 with the priority of 1,2,3 respectively
 * 1. task1 (low) takes the mutex before getting preempted by the higher priority task
 * 2. task3 (high) attempts to take the mutex but cant because it is still being held by the task1(low). task3(high) enters the blocked 
 *    state to wait for the mutex to become availabe.
 * 3. now task2 (mid) started running, since it has the higher priority than task1 it preempts the task1 and start running
 * Here the task2(mid) is running. The task3(high) is still waiting for task1(low) to return the mutex, but task1(low) is not even running.
 * 
 * Priority inversion can be significant problem, but in small embedded systems it can often be avoided at system design time, by 
 * considering how resources are accessed.
 * 
 * NOTE: Priority Inheritance:
 * 1. FreeRTOS mutexes and binary semaphores are very similar - the difference being that mutexes include a basic 'priority inheritance'
 *    machanism. whereas binary semaphore do not.
 * 2. Priority inheritance is a scheme that minimuzes the negative side effects of priority inversion. it does not fix priority inversion
 *    but merely lessens its impact by ensuring that the inversion is always time bounded. However, priority inheritance complicates
 *    system timing analysis, and it is not good practice to rely on it for correct system operation.
 * 3. Priority inheritance works by temporarily raising the priority of the mutex holder to the priority of the highes priority task that
 *    is atttempting to obtain the same mutex. 
 * 4. the low priority task that holds the mutex inherits the priority of the task waiting for the mutex.
 * 5. the priority of the mutex holder is reset automatically to its original value when it gives the mutex back.
 * 
 * Consider below scenario where there tasks are created, task1, task2, task3 with the priority of 1,2,3 respectively
 * 1. task1 (low) takes a mutex before being preempted by the other higher priority task.
 * 2. task3 (high) attempts to take the mutex but can't becuase it is still being held by the task1 (low). the task3 (high) enters the 
 *    blocked state to wait for the mutex to become available.
 * 3. task1 (low) is preventing the task3 (high) from executing so, inherits the priroty of the task1 (high).
 * 4. If task2 (mid) arrives it cannot preempt the task1 (low) as it inherited the priroty of task3(high), so the amount of time that 
 *    priority inversion exists is minimized compared to above case (see. Priority Inversion).
 * 5. Once the task1(low) return the mutex, task3 (high) will exit from blocked state and start executing.
 * 6. The task2 (mid) will start executing only when the task3 (high) returns to blocked state.
 *     
 * NOTE: Deadlock (or Deadly embrace):
 * Deadlock is another pitfall of using mutexes for mutual exclusion. Deadlock is sometimes also known by the more dramatic name
 * deadly embrace.
 * Deadlock occurs when two tasks cannot proceed because they are both waiting for a resource that is held by the other. 
 * 
 * Consider the following scenario:
 * 1. TaskA executes successully and takes mutex X.
 * 2. TaskA pre-empted by TaskB
 * 3. TaskB successfully take mutex Y, while attempting to take mutex X it is moved to blocked state (mutex X is held by TaskA)
 * 4. TaskA continues executing, it attempts to take mute Y and moves to blocked state (mutex Y is held by TaskB)
 * 
 * At the end of this scenario, Task A is waiting for a mutex held by TaskB and TaskB is waiting for a mutex held by TaskA. Deadlock is
 * occurred because neither task can proceed.
 * 
 * a. As with priority inversio, the best method of avoiding deadlock is to consider its potential at design time, and design the system
 *    to ensure that deadlock cannot occur.
 * b. It is normally bad practice for a task to wait indefintely (without a time out) to obtain a mutex. Instead, use a time out that is 
 *    little longer than the maximum time it is expected to have to wait, then failure to obtain mutex within the time will be a symptom 
 *    of a design error, which might be a deadlock. 
 * 
 * In practice, deadlock is not a big problem in small embedded systems, becuse the system designers can have a good understanding of the
 * entire application, and so can indentify and remove the areas where it could occur.
 * 
 * NOTE: Recursive Mutexes:
 * If is also possible for a task to deadlock with itself. this will happen if a task attempts to take the same mutex more than once, 
 * without returning the mutex. 
 * Consider the following scenario:
 * 1. A task successfully obtain the mutex.
 * 2. While holding the mutex, the task calls the library function
 * 3. The implementation of the library fucntion attempts to take the same mutex, and enters the blocked state to wait for the mutex to
 *    become available.
 * At the end of the scenario the task is in the blocked state to wait for the mutex to be returned, the but the task is already the
 * mutex holder. A deadlock has occurred because the task in the blocked state to wait for itself.
 * This type of deadlock can be avoided by using the recursive mutex in place of the standard mutex. A recursive mutex can be taken more
 * than once by the same task, and will be returned only after one call to give the recursive mutex has been executed for every 
 * PRECEEDING CALL TO TAKE THE MUTEX
 * 
 * Standard and Recursive mutexes are created in the same way:
 * 1. Recursive mutexes are created using xSemaphoreCreateRecursiveMutex()
 * 2. Recursive mutexes are ‘taken’ using xSemaphoreTakeRecursive()
 * 3. Recursive mutexes are ‘given’ using xSemaphoreGiveRecursive()
 * 4. 
 * 
 * NOTE: Mutexes and task scheduling:
 * 
 * NOTE: GateKeeper Tasks
 * Gatekeeper task provides a clean method of implementing mutual exclusion without the risk of priority inversion or deadlock.
 * 
 * Gatekeeper task is a task that has sole ownership of a resource. Only the gatekeeper task is allowed to access the resource directly
 * any other task needing to access the resource can do so only indirectly by using the services of the gatekeeper.
 * the services of gatekeeper task can created using queue, task notification or by other methods.
 * 
 *****************************************************************************************************************************************/

