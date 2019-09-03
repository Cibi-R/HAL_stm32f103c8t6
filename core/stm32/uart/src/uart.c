#include <includes.h>
#include UART_H

/******************************************************************************************************************************
 *												 Variable Definitions
 ******************************************************************************************************************************/

UART_Watchdog_ST UART_Watchdog;

uint8_t UART1_Tx_Buffer[UART1_TX_BUFFER_MAX_SIZE];
uint8_t UART2_Tx_Buffer[UART2_TX_BUFFER_MAX_SIZE];
uint8_t UART3_Tx_Buffer[UART3_TX_BUFFER_MAX_SIZE];

uint8_t UART1_Tx_BufferSize;
uint8_t UART2_Tx_BufferSize;
uint8_t UART3_Tx_BufferSize;

uint8_t UART1_Tx_BufferIndex;
uint8_t UART2_Tx_BufferIndex;
uint8_t UART3_Tx_BufferIndex;


/******************************************************************************************************************************
 *												  UART Subroutines
 ******************************************************************************************************************************/



void USART1_IRQHandler(void)
{
	/* Check TXE bit in control register. */
	if (UART1->SR & (1<<7))
	{
		UART1->DR = UART1_Tx_Buffer[UART1_Tx_BufferIndex];

		if (UART1_Tx_BufferIndex == UART1_Tx_BufferSize)
		{
			UART1->CR1 &= (~(1<<7));			
		}

		else
		{
			UART1_Tx_BufferIndex++;
		}
	}
}

void USART2_IRQHandler(void)
{
	/* Check TXE bit in control register. */
	if (UART2->SR & (1<<7))
	{
		UART2->DR = UART2_Tx_Buffer[UART2_Tx_BufferIndex];

		if (UART2_Tx_BufferIndex == UART2_Tx_BufferSize)
		{
			UART2->CR1 &= (~(1<<7));			
		}

		else
		{
			UART2_Tx_BufferIndex++;
		}
	}
}

void USART3_IRQHandler(void)
{
	/* Check TXE bit in control register. */
	if (UART3->SR & (1<<7))
	{
		UART3->DR = UART3_Tx_Buffer[UART3_Tx_BufferIndex];

		if (UART3_Tx_BufferIndex == UART3_Tx_BufferSize)
		{
			UART3->CR1 &= (~(1<<7));			
		}

		else
		{
			UART3_Tx_BufferIndex++;
		}
	}
}

/******************************************************************************************************************************
 *												 Function Definitions
 ******************************************************************************************************************************/

static uint8_t Is_UART_Available(USART_TypeDef *Handle)
{
	if ((Handle == UART1) && (UART_Watchdog.UART1_State != UART_State_Tx))
	{
		return 1;
	}

	else if ((Handle == UART2) && (UART_Watchdog.UART2_State != UART_State_Tx))
	{
		return 1;
	}

	else if ((Handle == UART3) && (UART_Watchdog.UART3_State != UART_State_Tx))
	{
		return 1;
	}

	return 0;
}

static void UART_Assign_State(USART_TypeDef *Handle,UART_State_EN CurrentState)
{
	if (Handle == UART1)
	{
		UART_Watchdog.UART1_State = CurrentState;
	}

	else if (Handle == UART2)
	{
		UART_Watchdog.UART2_State = CurrentState;
	}

	else if (Handle == UART3)
	{
		UART_Watchdog.UART3_State = CurrentState;
	}
}

unsigned char UART_Config_Init(UART_Config_ST *InitStruct)
{
	USART_TypeDef *Handle;

	Handle = InitStruct->Instance;

	if ((UART1 == Handle) || (UART2 == Handle) || (UART3 == Handle))
	{
		/* Configure the word length. */
		Handle->CR1 &= (~(1 << 12));
		Handle->CR1 |= (InitStruct->WordLength << 12);

		/* Configure the parity control and selection bits. */
		if (InitStruct->ParitySelection != UART_No_Parity)
		{
			/* Enable Parity Control. */
			Handle->CR1 |= (1 << 10);

			/* Parity Selection. */
			Handle->CR1 &= (~(1 << 9));
			Handle->CR1 |= (InitStruct->ParitySelection << 9);
		}

		else
		{
			/* Disable Parity Control. */
			Handle->CR1 &= (~(1 << 10)); 
		}

		/* Configure the Stopbits. */
		Handle->CR2 &= (~(0x3 << 12));
		Handle->CR2 |= (InitStruct->StopBits << 12);

		/* Configure Baudrates. */
		Handle->BRR = 0;
		Handle->BRR = (0xFFFF & InitStruct->BaudRate);

		/* Configure the operating mode. */
		Handle->CR1 &= (~(0x3 << 2));
		Handle->CR1 |= (InitStruct->OperatingMode << 2);
		
		/* Enable USART Peripheral. */
		Handle->CR1 |= (1<<13);

		return 1;
	}

	return 0;
}

unsigned char UART_Tx_Bytes_Interrupt(USART_TypeDef *Handle, uint8_t *BufferBase, uint8_t BufferSize)
{
	uint8_t *TxBuffer;
	uint8_t BufferMax;
	uint8_t i;

	if (Is_UART_Available(Handle))
	{
		if (Handle == UART1){ BufferMax = UART1_TX_BUFFER_MAX_SIZE; TxBuffer = UART1_Tx_Buffer; UART1_Tx_BufferSize = BufferSize; UART1_Tx_BufferIndex = 0; }

		if (Handle == UART2){ BufferMax = UART2_TX_BUFFER_MAX_SIZE; TxBuffer = UART2_Tx_Buffer; UART2_Tx_BufferSize = BufferSize; UART2_Tx_BufferIndex = 0; }

		if (Handle == UART3){ BufferMax = UART3_TX_BUFFER_MAX_SIZE; TxBuffer = UART3_Tx_Buffer; UART3_Tx_BufferSize = BufferSize; UART3_Tx_BufferIndex = 0; }


		/* If the size of the Tx byte count is higher than the buffer size. Reset the buffersize to Maximum size. */
		if (BufferSize > BufferMax)
		{
			BufferSize = BufferMax;
		}

		for (i = 0; i < BufferSize; i++)
		{
			TxBuffer[i] = BufferBase[i];
		}

		for (; i<BufferMax; i++)
		{
			TxBuffer[i] = 0;
		}

		/* Enable the Tx Buffer empty interrupt enable. */
		Handle->CR1 |= (1<<7);

		return 1;
	}

	return 0;
}

void UART_Tx_Bytes(USART_TypeDef *Handle, uint8_t Bytes)
{
	while (!(Handle->SR & (1<<6)));

	Handle->DR = Bytes;
}

void UART_Tx_String(USART_TypeDef *Handle, uint8_t *Base)
{
	if (Is_UART_Available(Handle))
	{
		while (*Base)
		{
			UART_Tx_Bytes(Handle, *Base);
			Base++;
		}

		UART_Assign_State(Handle, UART_State_Idle);
	}
}

uint8_t UART_Rx_Bytes_Polling(USART_TypeDef *Handle)
{
	return 0;
	/* To be implemented. */
}
