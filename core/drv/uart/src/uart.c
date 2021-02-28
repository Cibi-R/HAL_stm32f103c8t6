#include <platform.h>

/******************************************************************************************************************************
 *												Local fucntion declarations
 ******************************************************************************************************************************/

static USART_TypeDef* UART_GetBase_Add(uint8_t uartChannel);

static uint8_t UART_Is_Channel_Available(uint8_t channel);

extern uint8_t UART_Init(UART_Params_T *uartParams);


/**
 * @brief: Global handle variable to hold the status of configured UART channel, This avoids the re-initialization or re instantiation of 
 *         of any particular UART channel
 **/
UART_Handle_T UART_Handles[DEVICE_UART_CHANNEL_MAX] =
{
	{DEVICE_UART_CHANNEL_NONE, NULL, DEVICE_UART_MODE_NONE},
	{DEVICE_UART_CHANNEL_NONE, NULL, DEVICE_UART_MODE_NONE},
	{DEVICE_UART_CHANNEL_NONE, NULL, DEVICE_UART_MODE_NONE},
};

/**
 * @brief: UART1 interrupt handler
 **/
void USART1_IRQHandler(void)
{
		
}

/**
 * @brief: UART2 interrupt handler
 **/
void USART2_IRQHandler(void)
{
	
}

/**
 * @brief: UART3 interrupt handler
 **/
void USART3_IRQHandler(void)
{
	
}


/******************************************************************************************************************************
 *												    Function Definitions
 ******************************************************************************************************************************/


static USART_TypeDef* UART_GetBase_Add(uint8_t uartChannel)
{
	USART_TypeDef *uartHandle = NULL;

	switch (uartChannel)
	{
		case DEVICE_UART_CHANNEL_1:
		{
			uartHandle = USART1;
			break;
		}
		case DEVICE_UART_CHANNEL_2:
		{
			uartHandle = USART2;
			break;
		}
		case DEVICE_UART_CHANNEL_3:
		{
			uartHandle = USART3;
			break;
		}
		default:
		{
			uartHandle = NULL;
			break;
		}
	}

	return uartHandle;
}

/**
 * @brief :  
 * @param : 
 * @return: 
 **/

static uint8_t UART_Is_Channel_Available(uint8_t channel)
{
	if ((DEVICE_UART_CHANNEL_MAX >= channel) && (0 < channel))
	{
		if (DEVICE_UART_CHANNEL_NONE == UART_Handles[channel-1].uart_Channel)
		{
			channel = True;			
		}
		else
		{
			channel = False;
		}
	}

	return channel;
}

/**
 * @brief: To set the default values for UART peripheral while initialization, Refer uart.h for more information
 */
void UART_Params_Init(UART_Params_T *uartParams)
{
	uartParams->uart_Channel       = DEVICE_UART_CHANNEL_NONE;
	uartParams->uart_OperatingMode = DEVICE_UART_MODE_TX;
	uartParams->uart_WordLength    = DEVICE_UART_WORD_LEN_8;
	uartParams->uart_StopBits      = DEVICE_UART_STOP_BIT_1;
	uartParams->uart_Parity        = DEVICE_UART_PARITY_NONE;
	uartParams->uart_Baudrate      = DEVICE_UART_BR_9600;
	uartParams->uart_TxCallBack    = NULL;
	uartParams->uart_RxCallBack    = NULL;
}

UART_Handle_T* UART_SetConfig(UART_Params_T *uartParams)
{
	UART_Handle_T *uartHandle = NULL;

	if (NULL != uartParams)
	{
		if (UART_Is_Channel_Available(uartParams->uart_Channel))
		{
			if (UART_Init(uartParams))
			{
				UART_Handles[uartParams->uart_Channel - 1].uart_Channel = uartParams->uart_Channel;
				UART_Handles[uartParams->uart_Channel - 1].uart_Handle = UART_GetBase_Add(uartParams->uart_Channel);
				UART_Handles[uartParams->uart_Channel - 1].uart_OperatingMode = uartParams->uart_OperatingMode;

				uartHandle = &UART_Handles[uartParams->uart_Channel-1];
			}
			else
			{
				/*< UART initialization failed, return NULL */
			}
		}
		else
		{
			/*< The passed UART channel number is already in use */	
		}
	}

	return uartHandle;
}

void UART_ReleaseConfig(UART_Handle_T* uarthandle)
{
	uarthandle->uart_Channel       = DEVICE_UART_CHANNEL_NONE;
	uarthandle->uart_Handle        = NULL;
	uarthandle->uart_OperatingMode = DEVICE_UART_MODE_NONE;
}

/**
 * @brief: To configure the UART peripheral, Refer uart.h for more information
 */
uint8_t UART_Init(UART_Params_T *uartParams)
{	
	USART_TypeDef *uartHandle;

	uartHandle = UART_GetBase_Add(uartParams->uart_Channel);

	if ((UART1 == uartHandle) || (UART2 == uartHandle) || (UART3 == uartHandle))
	{
		/*< Reset the registers before assigning values. */
		uartHandle->CR1 = 0X00000000;
		uartHandle->BRR = 0X00000000;

		/*< Configure the word length. */
		uartHandle->CR1 &= (~(1 << 12));
		uartHandle->CR1 |= (0u << 12);

		/*< Configure the parity control and selection bits. */
		if (0)
		{
			/*< Enable Parity Control. */
			uartHandle->CR1 |= (1 << 10);

			/*< Parity Selection. */
			uartHandle->CR1 &= (~(1 << 9));
			// uartHandle->CR1 |= (InitStruct->ParitySelection << 9);
		}

		else
		{
			/*< Disable Parity Control. */
			uartHandle->CR1 &= (~(1 << 10)); 
		}

		/*< Configure the Stopbits. */
		uartHandle->CR2 &= (~(0x3 << 12));
		uartHandle->CR2 |= (0 << 12);

		/*< Configure Baudrates. */
		uartHandle->BRR = 0;
		uartHandle->BRR = (0xFFFF & DEVICE_UART_BR_9600);

		/*< Configure the operating mode. */
		uartHandle->CR1 &= (~(0x3 << 2));
		uartHandle->CR1 |= (0X02U << 2);

		#if 0
		/*< Enable interrupts incase of receiver or transceiver configuration */
		if ((InitStruct->OperatingMode == UART_Receiver) || (InitStruct->OperatingMode == UART_Transceiver))
		{
			Handle->CR1 |= (1<<5);
			
			if (Handle == UART1){ UART1_Rx_Handler = InitStruct->UART_Rx_ISR; }
			
			if (Handle == UART2){ UART2_Rx_Handler = InitStruct->UART_Rx_ISR; }
			
			if (Handle == UART3){ UART3_Rx_Handler = InitStruct->UART_Rx_ISR; }
		}
		#endif
		
		/*< Enable USART Peripheral. */
		uartHandle->CR1 |= (1<<13);

		return True;
	}

	return False;
}

uint8_t UART_Open(UART_Handle_T *uart_params)
{
	uint8_t retVal = True;

	/*< Enable clock for UART */
	switch (uart_params->uart_Channel)
	{
		case DEVICE_UART_CHANNEL_1:
		{
			UART1_CLOCK_ENABLE();
			break;
		}
		case DEVICE_UART_CHANNEL_2:
		{
			UART2_CLOCK_ENABLE();
			break;
		}
		case DEVICE_UART_CHANNEL_3:
		{
			UART3_CLOCK_ENABLE();
			break;
		}
		default:
		{
			retVal = False;
			break;
		}	
	}

	/*< Enable UART interrupt in NVIC */

	return retVal;
}

void UART_Close(UART_Handle_T *uart_params)
{
	/*< Disable clock for UART */
	switch (uart_params->uart_Channel)
	{
		case DEVICE_UART_CHANNEL_1:
		{
			UART1_CLOCK_DISABLE();
			break;
		}
		case DEVICE_UART_CHANNEL_2:
		{
			UART2_CLOCK_DISABLE();
			break;
		}
		case DEVICE_UART_CHANNEL_3:
		{
			UART3_CLOCK_DISABLE();
			break;
		}
		default:
		{
			break;
		}		
	}

	/*< Disable UART interrupt */
}

void UART_TxByte(UART_Handle_T *uart_params, uint8_t data)
{
	while (!(USART1->SR & (1 << 6)))
		;

	USART1->DR = data;
}

void UART_TxString(UART_Handle_T *uart_params, uint8_t *data, uint16_t len)
{
	uint16_t i;
	
	for (i = 0; i < len; i++)
	{
		UART_TxByte(uart_params, data[i]);
	}
}

void UART_TxCancel(UART_Handle_T *uart_params)
{

}

uint8_t UART_Read(UART_Handle_T *uart_params)
{
	if (uart_params->uart_Handle->SR & (1<<5))
	{
		uart_params->uart_Handle->SR &= (~(1<<5));
		return uart_params->uart_Handle->DR;
	}

	return 0;
}

void UART_Read_Polling(UART_Handle_T *uart_params)
{

}

