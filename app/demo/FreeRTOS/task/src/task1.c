#include <app.h>


/******************************************************************************************************************************
 *												     Macro Definitions
 ******************************************************************************************************************************/

#define STACK_SIZE_512B         (0X80U)

/******************************************************************************************************************************
 *												   Function Declaration
 ******************************************************************************************************************************/

extern void FreeRTOS_Task_Demo(void);

extern void GPIO_Led_Init(void);

/**
 * @brief: Task function to check the task creation and delay function APIs
 **/
extern void FreeRTOS_Task_1_Create(void);

/**
 * @brief: Task function to check the vTaskDelayUntil API
 **/
extern void FreeRTOS_Task_4_Create(void);

/**
 * @brief: Task function to check the vTaskDelayUntil API
 **/
extern void FreeRTOS_Task_1(void* pvParameters);

/**
 * @brief: Task function to check the vTaskDelayUntil API
 **/
extern void FreeRTOS_Task_4(void* pvParameters);

/**
 * @brief: Task function to check the vTaskDelayUntil API
 **/
extern void FreeRTOS_Task_MulInstance(void *pvParameters);

/******************************************************************************************************************************
 *												     Global Variable
 ******************************************************************************************************************************/

TaskHandle_t TaskHandle = NULL;

TaskHandle_t TaskInstance_1 = NULL;

TaskHandle_t TaskInstance_2 = NULL;

const char *TaskParam1 = "Task Param 1";
const char *TaskParam2 = "Task Param 2";

volatile uint32_t uIdleCycleCount = 0u;

/******************************************************************************************************************************
 *												     Function Defintionns
 ******************************************************************************************************************************/

void FreeRTOS_Task_Demo(void)
{
	/* Initialize LED */
	GPIO_Led_Init();
	
	/*< Create the task. */
	FreeRTOS_Task_1_Create();
	
    /*< Starts the scheduler */
    vTaskStartScheduler();
}

void GPIO_Led_Init(void)
{
	GPIO_Params_T PC13;
	
	PC13.GPIO_Port           = DEVICE_PORT_C;
	PC13.GPIO_Pin            = DEVICE_PORT_PIN_13;
	PC13.GPIO_Mode           = DEVICE_PIN_MODE_OUT_50Mhz;
	PC13.GPIO_Config_Func    = DEVICE_PIN_CONFIG_FUNC_OUT_PUSH_PULL;
	
	GPIO_SetConfig(&PC13);
}

/**
 * @brief: Idle hook function MUST be called vApplicationIdleHook(), take no parameters and return void.
 **/
void vApplicationIdleHook(void)
{
	/*< This hook funciton does nothing but increment the counter. */
	uIdleCycleCount++;
}

void FreeRTOS_Task_1_Create(void)
{
	/**
	 * BaseType_t xTaskCreate( TaskFunction_t pvTaskCode,
	 * 						   const char * const pcName,
	 *                         uint16_t usStackDepth,
	 *                         void *pvParameters,
	 *                         UBaseType_t uxPriority,
	 *                         TaskHandle_t *pxCreatedTask);
	 * pvTaskCode    : Tasks are C functions that never exit, as such, are normally implemened as infinite loop
	 *                  In essence TaskFunction_t is a pointer to a task function
	 * pcName        : A descriptive name for task. This is not used by FreeRTOS in any way. It is included purely as
	 *                 debugging aid.
	 * usStackDepth  : Each task has its own stack space that is allocated to kernel to the task. The value specified the
	 *                 number words the stack can hold, not the number of bytes.
	 *                 The stack depth multiplied by the stack width(4 - word size) mush not exceed the maximum value
	 *                 that can be contained in a variable of type uint16_t
	 *                 The size of the stack used by the idle task is defined by the application-defined constant 
	 *                 configMINIMAL_STACK_SIZE
	 *                 There is not easy way to determin the stack space required by a task. It is possible to calculate
	 *                 but most users will simply assign what think is a reasonable value.
	 * pvParameters  : Task functions accept a parameter of type pointer to void*. The value assigned to pvParameters is 
	 *                 the value passed into the task.
	 * uxPriority    : Defines the priority at which the task will execute. Priorities can be assigned from zero which is
	 *                 the lowest priority, to configMAX_PRIORITIES-1. passing a uxPriority value above configMAX_PRIORITIES
	 *                 will result in maximum legitimate value.
	 * pxCreatedTask : It can be used to pass out a handle to the task being created. This handle then be used to reference
	 *                 the task in API calls that, for example, change the task priority or delete the task.
	 *                 We can also pass NULL if we do not require the handle of the task.
	 * 
	 * return value  : There are two possible return values
	 *                 1. pdPASS
	 *                 Indicates that the task has been created successfully
	 *                 2. pdFAIL
	 *                 Indicates that the task has not been created because there is insufficient heap memory available for 
	 *                 FreeRTOS to allocate enough RAM to hold the task data structure and stack.
	 * 
	 * NOTE:
	 * Tasks should be created before starting the scheduler, vTaskStartScheduler(); API is used to start the scheduler.
	 **/

    /*< Creating the task. */
    if (xTaskCreate(FreeRTOS_Task_1, "TestApp1", configMINIMAL_STACK_SIZE, NULL,2U, &TaskHandle) != pdPASS)
	{
		/*< Task Creation failed. */
	}

	/*<Creating two instance of a task. */
	if (xTaskCreate(FreeRTOS_Task_MulInstance, "Task Instance 1", configMINIMAL_STACK_SIZE, (void *)TaskParam1, 2U, &TaskInstance_1))
	{
		if (xTaskCreate(FreeRTOS_Task_MulInstance, "Task Instance 2", configMINIMAL_STACK_SIZE, (void *)TaskParam2, 2U, &TaskInstance_2))
		{

		}
		else
		{
			while(1);
		}
		
	}
	else
	{
		while (1);
	}
	
}

void FreeRTOS_Task_4_Create(void)
{
	if (xTaskCreate(FreeRTOS_Task_4, "Task-4", configMINIMAL_STACK_SIZE, NULL, 2U, NULL))
	{
		while (1);
	}
}

void FreeRTOS_Task_1(void* pvParameters)
{
    volatile uint8_t taskRunning = True;

    while (taskRunning)
    {
		GPIO_Toggle(DEVICE_PORT_C,DEVICE_PORT_PIN_13);
		
		vTaskDelay(pdMS_TO_TICKS(1));
    }
	
	/*< A task should be deleted before the exit, the NULL parameter indicates that the calling function should be deleted. */
	vTaskDelete(NULL);
}

void FreeRTOS_Task_4(void* pvParameters)
{
	uint8_t xThreadStatus = 1u;
	
	TickType_t xLastWakeupTime;

	xLastWakeupTime = xTaskGetTickCount();

	while (xThreadStatus)
	{
		/**
		 * void vTaskDelayUntil( TickType_t *pxPreviousWakeTime,
		 *                       TickType_t xTimeIncrement
		 * );
		 * pxPreviousWakeTime :  This parameter is named on the assumption that vTaskDelayUntil() is being used to implement a 
		 *                       a task that executes periodically and with a fixed frequency. In this case pxPrevioudWakeTime
		 *                       holds the time at which the task has left the blocked state, This time is used as a reference point
		 *                       to calculate the time at which the task should next leave the blocked state.
		 *                       Since we passing reference, it is updated automatically inside vTaskDelayUntil, but must be 
		 *                       initialized to the
		 *                       current tick count before it is used for the first time.
		 * xTimeIncrement    :   This parameter is also named on the assumption that vTaskDelayUntil() is being used to implement a 
		 *                       task that executes periodically and with a fixed frequency.
		 *                       The value is specified in ticks. The macro pdMS_TO_TICKS() can be used to convert a time specified in
		 *                       milleseconds into a time specified in ticks
		 **/

		GPIO_Toggle(DEVICE_PORT_C,DEVICE_PORT_PIN_13);

		/**
		 * This task should execute every 10 millisecond exactly
		 **/
		vTaskDelayUntil(&xLastWakeupTime, pdMS_TO_TICKS(10));
	}

	vTaskDelete(NULL);
}

void FreeRTOS_Task_MulInstance(void *pvParameters)
{
	vTaskDelete(NULL);
}

