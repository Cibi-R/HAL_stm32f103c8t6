#include <app.h>

void HardFault_Handler(void)
{
	volatile uint8_t i = 0;
	while (i)
	{
		
	}
}

int main(void)

{	
    PORTA_CLOCK_ENABLE();
    PORTB_CLOCK_ENABLE();
    PORTC_CLOCK_ENABLE();
    PORTD_CLOCK_ENABLE();

    AFIOEN_CLOCK_ENABLE();

#if 0
    UART_Init();
    Flash_Init();
	
	GPIO_Config PC13;

	PC13.CurrentPort = PC;
	PC13.CurrentPin = P13;
	PC13.PinState = Output_PushPull;
	PC13.PinMode = Speed_50MHz_Output;
	
	GPIO_Config_Pin(&PC13);
#endif
	
#if 0
	Flash_App_Test();
#endif

    Run_FreeRTOS_Test1();
	
	while (1)
	{
#if 0
		GPIO_Write_Data(PC, P13, High);
		Delay();
		
		GPIO_Write_Data(PC, P13, Low);
		Delay();
#endif
	}
}



