#include <includes.h>
#include <string.h>
#include GPIO_H
#include UART_H

void Test1(void)
{
	UART_Tx_Bytes(UART1, UART_Rx_Bytes(UART1));
}

void Test2(void)
{
	UART_Tx_Bytes(UART2, UART_Rx_Bytes(UART2));
}

void Test3(void)
{
	UART_Tx_Bytes(UART3, UART_Rx_Bytes(UART3));
}

static void UART_Config_Pin(void)
{
    /* UART-1 Pin Configuration. No remapping programmed for UART1. */
	GPIO_Config PA9, PA10;

	/* UART-2 Pin Configuration. No remapping programmed for UART2. */
	GPIO_Config PA2, PA3;

	/* UART-3 Pin Configuration. No remapping programmed for UART3. */
	GPIO_Config PB10, PB11;

	/* UART-1 */
	PA9.CurrentPort = PA;
	PA9.CurrentPin = P9;
	PA9.PinState = Output_Alternate_PushPull;
	PA9.PinMode = Speed_50MHz_Output;

	PA10.CurrentPort = PA;
	PA10.CurrentPin = P10;
	PA10.PinState = Input_Floating;
	PA10.PinMode = Input;

	/* UART-2 */
	PA2.CurrentPort = PA;
	PA2.CurrentPin = P2;
	PA2.PinState = Output_Alternate_PushPull;
	PA2.PinMode = Speed_50MHz_Output;

	PA3.CurrentPort = PA;
	PA3.CurrentPin = P3;
	PA3.PinState = Input_Floating;
	PA3.PinMode = Input;

	/* UART-3 */
	PB10.CurrentPort = PB;
	PB10.CurrentPin = P10;
	PB10.PinState = Output_Alternate_PushPull;
	PB10.PinMode = Speed_50MHz_Output;

	PB11.CurrentPort = PB;
	PB11.CurrentPin = P11;
	PB11.PinState = Input_Floating;
	PB11.PinMode = Input;

	/* UART-1 */
	GPIO_Config_Pin(&PA9);
	GPIO_Config_Pin(&PA10);

	/* UART-2 */
	GPIO_Config_Pin(&PA2);
	GPIO_Config_Pin(&PA3);

	/* UART-3 */
	GPIO_Config_Pin(&PB10);
	GPIO_Config_Pin(&PB11);
}

void UART_Init(void)
{
	/* Test Strings */
	uint8_t String[] = "String Function Working!\n\r";
	uint8_t Array[] = "Array Function Working!\n\r";
	
	/* Instantiate variable to configure UART peripherals. */
    UART_Config_ST uart1;
	UART_Config_ST uart2;
	UART_Config_ST uart3;

    uart1.Instance = UART1;
    uart1.WordLength = UART_8Bit;
    uart1.ParitySelection = UART_No_Parity;
    uart1.StopBits = UART_1_StopBit;
    uart1.BaudRate = UART_Baud_9600;
    uart1.OperatingMode = UART_Transceiver;
	uart1.UART_Rx_ISR = Test1;
	

	uart2.Instance = UART2;
    uart2.WordLength = UART_8Bit;
    uart2.ParitySelection = UART_No_Parity;
    uart2.StopBits = UART_1_StopBit;
    uart2.BaudRate = UART_Baud_9600;
    uart2.OperatingMode = UART_Transceiver;
	uart2.UART_Rx_ISR = Test2;

	uart3.Instance = UART3;
    uart3.WordLength = UART_8Bit;
    uart3.ParitySelection = UART_No_Parity;
    uart3.StopBits = UART_1_StopBit;
    uart3.BaudRate = UART_Baud_9600;
    uart3.OperatingMode = UART_Transceiver;
	uart3.UART_Rx_ISR = Test3;

	/*< Enable clock of the UART. */
    ENABLE_UART1_CLOCK();
	ENABLE_UART2_CLOCK();
	ENABLE_UART3_CLOCK();
	
	/*< Enable the UART interrupt. */
	NVIC_EnableIRQ(USART1_IRQn);
	NVIC_EnableIRQ(USART2_IRQn);
	NVIC_EnableIRQ(USART3_IRQn);

	/*< Configure the UART pins. */
    UART_Config_Pin();

	/*< Configure UART. */
    UART_Config_Init(&uart1);
	UART_Config_Init(&uart2);
	UART_Config_Init(&uart3);
	
	/*< Send String. */
	UART_Tx_String(UART1,String);
	UART_Tx_String(UART2,String);
	UART_Tx_String(UART3,String);

	/*< Send Array. */
	UART_Tx_Array(UART1,Array,sizeof(Array));
	UART_Tx_Array(UART2,Array,sizeof(Array));
	UART_Tx_Array(UART3,Array,sizeof(Array));
}


