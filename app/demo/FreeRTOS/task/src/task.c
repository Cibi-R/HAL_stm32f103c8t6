#include <app.h>


/******************************************************************************************************************************
 *												     Macro Definitions
 ******************************************************************************************************************************/

#define STACK_SIZE_512B         (0X80U)

/******************************************************************************************************************************
 *												   Function Declaration
 ******************************************************************************************************************************/

extern void FreeRTOS_TestApp1_Init(void);

extern void GPIO_Led_Init(void);

extern void FreeRTOS_Task_Create(void);

extern void FreeRTOS_Task_Func(void* pvParameters);

/******************************************************************************************************************************
 *												     Global Variable
 ******************************************************************************************************************************/

TaskHandle_t TaskHandle = NULL;


/******************************************************************************************************************************
 *												     Function Defintionns
 ******************************************************************************************************************************/

void FreeRTOS_TestApp1_Run(void)
{
	/* Initialize LED */
	GPIO_Led_Init();
	
	/*< Create the task. */
	FreeRTOS_Task_Create();
	
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

void FreeRTOS_Task_Create(void)
{
    /* Creating the task. */
    if (xTaskCreate(FreeRTOS_Task_Func, "TestApp1", configMINIMAL_STACK_SIZE, NULL,2U, &TaskHandle) != pdPASS)
	{
		/*< Task Creation failed. */
	}
}

void FreeRTOS_Task_Func(void* pvParameters)
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

