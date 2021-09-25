#include <app.h>


int main(void)

{	
    PORTA_CLOCK_ENABLE();
    PORTB_CLOCK_ENABLE();
    PORTC_CLOCK_ENABLE();
    PORTD_CLOCK_ENABLE();

    AFIOEN_CLOCK_ENABLE();

	SCB->CCR |= (1 << 3);
	
	Sys_Init();

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
#if 0
	UART1_Test_App();
#endif
#if 1
    FreeRTOS_Task_Demo();
#endif
	while (1);
}



