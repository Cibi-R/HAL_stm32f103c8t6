#include <platform.h>
#include <app.h>


/******************************************************************************************************************************
 *												     Macro Definitions
 ******************************************************************************************************************************/

#define STACK_SIZE_512B         (0X80U)

/******************************************************************************************************************************
 *												   Function Declaration
 ******************************************************************************************************************************/

extern void GPIO_Led_Init(void);

extern void Task1_FreeRTOS(void* pvParameters);

extern void Create_Tasks_FreeRTOS(void);

#if 0
extern void delay_test1(void);

extern void LED_Test_Function(void);
#endif
/******************************************************************************************************************************
 *												     Global Variable
 ******************************************************************************************************************************/

TaskHandle_t Task1Handle = NULL;


/******************************************************************************************************************************
 *												     Function Defintionns
 ******************************************************************************************************************************/

#if 0
void delay_test1(void)
{
	uint16_t i,j;
	
	for (i=0; i<10000; i++)
	{
		for (j=0; j<1000; j++);
	}
}
#endif

void GPIO_Led_Init(void)
{
	GPIO_Config PC13;
	
	PC13.CurrentPin  = P13;
	PC13.CurrentPort = PC;
	PC13.PinMode     = Speed_50MHz_Output;
	PC13.PinState    = Output_PushPull;
	
	GPIO_Config_Pin(&PC13);
}
 
void Run_FreeRTOS_Test1(void)
{
	/* Initialize LED */
	GPIO_Led_Init();
	
	/*< Create the task. */
	Create_Tasks_FreeRTOS();
	
    /*< Starts the scheduler */
    vTaskStartScheduler();
}

void Create_Tasks_FreeRTOS(void)
{
    /* Creating the task. */
    if (xTaskCreate(Task1_FreeRTOS, "Temp1", configMINIMAL_STACK_SIZE, NULL,2U, &Task1Handle) != pdPASS)
	{
		/*< Task Creation failed. */
	}
}

void Task1_FreeRTOS(void* pvParameters)
{
    volatile uint8_t taskRunning = True;

    while (taskRunning)
    {
		GPIO_Toggle_Pin(PC,P13);
		
		vTaskDelay(pdMS_TO_TICKS(1));
		
		#if 0
		/*< Not exactly 1ms, .8ms-.9ms */
		vTaskDelay(configTICK_RATE_HZ/1000U);
		#endif
    }
	
	vTaskDelete(NULL);
}

#if 0
void LED_Test_Function(void)
{
	while (1)
	{
		GPIO_Write_Data(PC,P13,High);
		delay_test1();
		
		GPIO_Write_Data(PC,P13,Low);
		delay_test1();
	}
}
#endif

