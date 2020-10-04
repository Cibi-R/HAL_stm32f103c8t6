#include <includes.h>
#include UART_H

/******************************************************************************************************************************
 *												 Variable Definitions
 ******************************************************************************************************************************/

void (*UART1_Rx_Handler)(void) = NULL;
void (*UART2_Rx_Handler)(void) = NULL;
void (*UART3_Rx_Handler)(void) = NULL;


/******************************************************************************************************************************
 *												  UART Subroutines
 ******************************************************************************************************************************/


void USART1_IRQHandler(void)
{
	if (UART1->SR & (1<<5))
	{
		if (UART1_Rx_Handler != NULL)
		{
			UART1_Rx_Handler();
		}
	}	
}

void USART2_IRQHandler(void)
{
	if (UART2->SR & (1<<5))
	{
		if (UART2_Rx_Handler != NULL)
		{
			UART2_Rx_Handler();
		}
	}
}

void USART3_IRQHandler(void)
{
	if (UART3->SR & (1<<5))
	{
		if (UART3_Rx_Handler != NULL)
		{
			UART3_Rx_Handler();
		}
	}
}

/******************************************************************************************************************************
 *												 Function Definitions
 ******************************************************************************************************************************/

HAL_Status UART_Config_Init(UART_Config_ST *InitStruct)
{
	USART_TypeDef *Handle;

	Handle = InitStruct->Instance;

	if ((UART1 == Handle) || (UART2 == Handle) || (UART3 == Handle))
	{
		/*< Reset the registers before assigning values. */
		Handle->CR1 = 0X00000000;
		Handle->BRR = 0X00000000;

		/*< Configure the word length. */
		Handle->CR1 &= (~(1 << 12));
		Handle->CR1 |= (InitStruct->WordLength << 12);

		/*< Configure the parity control and selection bits. */
		if (InitStruct->ParitySelection != UART_No_Parity)
		{
			/*< Enable Parity Control. */
			Handle->CR1 |= (1 << 10);

			/*< Parity Selection. */
			Handle->CR1 &= (~(1 << 9));
			Handle->CR1 |= (InitStruct->ParitySelection << 9);
		}

		else
		{
			/*< Disable Parity Control. */
			Handle->CR1 &= (~(1 << 10)); 
		}

		/*< Configure the Stopbits. */
		Handle->CR2 &= (~(0x3 << 12));
		Handle->CR2 |= (InitStruct->StopBits << 12);

		/*< Configure Baudrates. */
		Handle->BRR = 0;
		Handle->BRR = (0xFFFF & InitStruct->BaudRate);

		/*< Configure the operating mode. */
		Handle->CR1 &= (~(0x3 << 2));
		Handle->CR1 |= (InitStruct->OperatingMode << 2);

		/*< Enable interrupts incase of receiver or transceiver configuration */
		if ((InitStruct->OperatingMode == UART_Receiver) || (InitStruct->OperatingMode == UART_Transceiver))
		{
			Handle->CR1 |= (1<<5);
			
			if (Handle == UART1){ UART1_Rx_Handler = InitStruct->UART_Rx_ISR; }
			
			if (Handle == UART2){ UART2_Rx_Handler = InitStruct->UART_Rx_ISR; }
			
			if (Handle == UART3){ UART3_Rx_Handler = InitStruct->UART_Rx_ISR; }
		}
		
		/*< Enable USART Peripheral. */
		Handle->CR1 |= (1<<13);

		return HAL_Ok;
	}

	return HAL_Err;
}

HAL_Status UART_Tx_Bytes(USART_TypeDef *Handle, uint8_t Bytes)
{
	while (!(Handle->SR & (1<<6)));

	Handle->DR = Bytes;
	
	return HAL_Ok;
}

HAL_Status UART_Tx_Array(USART_TypeDef *Handle, uint8_t *const Base, uint8_t Len)
{
	uint8_t i = 0;

	while (i<Len)
	{
		UART_Tx_Bytes(Handle, Base[i]);
		i++;
	}

	return HAL_Ok;
}

HAL_Status UART_Tx_String(USART_TypeDef *Handle, const uint8_t *Data)
{
	while (*Data)
	{
		UART_Tx_Bytes(Handle, *Data);
		Data++;
	}
	
	return HAL_Ok;
}

uint8_t UART_Rx_Bytes(USART_TypeDef *Handle)
{
	if (Handle->SR & (1<<5))
	{
		Handle->SR &= (~(1<<5));
		return Handle->DR;
	}

	return 0;
}
