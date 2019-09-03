#include <includes.h>
#include GPIO_H
#include UART_H

static void UART_Config_Pin(void)
{
    /* UART-1 Pin Configuration. No remapping programmed for UART1. */
	GPIO_Config PA9, PA10;

	PA9.CurrentPort = PA;
	PA9.CurrentPin = P9;
	PA9.PinState = Output_Alternate_PushPull;
	PA9.PinMode = Speed_50MHz_Output;

	PA10.CurrentPort = PA;
	PA10.CurrentPin = P10;
	PA10.PinState = Input_Floating;
	PA10.PinMode = Input;

	GPIO_Config_Pin(&PA9);
	GPIO_Config_Pin(&PA10);
}

void UART_Init(void)
{
    UART_Config_ST uart1;

    uart1.Instance = UART1;
    uart1.WordLength = UART_8Bit;
    uart1.ParitySelection = UART_No_Parity;
    uart1.StopBits = UART_1_StopBit;
    uart1.BaudRate = UART_Baud_9600;
    uart1.OperatingMode = UART_Transceiver;

    ENABLE_UART1_CLOCK();

    UART_Config_Pin();

    UART_Config_Init(&uart1);
}
