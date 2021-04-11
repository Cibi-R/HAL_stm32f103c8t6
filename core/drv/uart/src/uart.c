#include <platform.h>

/******************************************************************************************************************************
 *												Local fucntion declarations
 ******************************************************************************************************************************/

/**
 * @brief : This function is used to get the base address of the UART channel
 * @param : uint8_t - Refer UART Channels to check available UART channels 
 * @return: USART_TypeDef - Base address of the UART peripheral - Line 1239 of stm32f10x.h
 **/
static USART_TypeDef* UART_GetBase_Add(uint8_t uartChannel);

/**
 * @brief : To check if the UART channel is availble or not, UART_Handles will hold the already configured UART channels
 * @param : uint8_t - Refer UART Channels to check available UART channels
 * @return: uint8_t 
 **/
static uint8_t UART_Is_Channel_Available(uint8_t channel);

/**
 * @brief : To initialize the UART channel with the supplied configuration
 * @param : UART_Params_T
 * @return: uint8_t
 **/
extern uint8_t UART_Init(UART_Params_T *uartParams);


/**
 * @brief: Global handle variable to hold the status of configured UART channel, This avoids the re-initialization or re instantiation of 
 *         of any particular UART channel
 **/
UART_Handle_Tag UART_Handles[DEVICE_UART_CHANNEL_MAX] =
{
	{DEVICE_UART_CHANNEL_NONE, NULL, DEVICE_UART_MODE_NONE},
	{DEVICE_UART_CHANNEL_NONE, NULL, DEVICE_UART_MODE_NONE},
	{DEVICE_UART_CHANNEL_NONE, NULL, DEVICE_UART_MODE_NONE},
};

/******************************************************************************************************************************
 *												          UART ISRs
 ******************************************************************************************************************************/

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

/**
 * @brief: This function is used to get the base address of the UART channel
 **/

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
 * @brief : To check if the UART channel is availble or not, UART_Handles will hold the already configured UART channels
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
 **/

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

/**
 * @brief: To configure the UART channel with the supplied configuration 
 **/

UART_Handle_T UART_SetConfig(UART_Params_T *uartParams)
{
	UART_Handle_T uartHandle = NULL;

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

/**
 * @brief: To release the configured UART channel 
 **/

void UART_ReleaseConfig(UART_Handle_T uartHandle)
{
	uartHandle->uart_Channel       = DEVICE_UART_CHANNEL_NONE;
	uartHandle->uart_Handle        = NULL;
	uartHandle->uart_OperatingMode = DEVICE_UART_MODE_NONE;
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
		/*< Enable clock before start configuring the UART channel */
		UART_Open(uartParams->uart_Channel);
		
		/*< Reset the registers before assigning values. */
		uartHandle->CR1 = 0X00000000;
		uartHandle->BRR = 0X00000000;

		/*< Configure the word length. */
		uartHandle->CR1 &= (~(1 << 12));
		uartHandle->CR1 |= (0u << 12);

		/*< Configure the parity control and selection bits. */
		if (DEVICE_UART_PARITY_NONE != uartParams->uart_Parity)
		{
			/*< Enable Parity Control. */
			uartHandle->CR1 |= (1 << 10);

			/*< Parity Selection. */
			uartHandle->CR1 &= (~(1 << 9));
			uartHandle->CR1 |= ((uint32_t)uartParams->uart_Parity << 9);
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

#if 0  // If the clock needs to disabled to save power, from application we can control using UART_Close, UART_Open APIs
		/*< Disable clock after configuring the UART channel */
		UART_Close(uartParams->uart_Channel);
#endif
		return True;
	}

	return False;
}

void UART_Open(uint8_t uartChannel)
{
	/*< Enable clock for UART */
	switch (uartChannel)
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
			/*< Do Nothing */
			break;
		}	
	}

	/*< Enable UART interrupt in NVIC */
}

void UART_Close(uint8_t uartChannel)
{
	/*< Disable clock for UART */
	switch (uartChannel)
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

void UART_TxByte(UART_Handle_T uartHandle, uint8_t data)
{
	if (NULL != uartHandle)
	{
		while (!(uartHandle->uart_Handle->SR & (1 << 6)))
			;

		uartHandle->uart_Handle->DR = data;
	}
}

void UART_TxString(UART_Handle_T uartHandle, uint8_t *data, uint16_t len)
{
	uint16_t i;
	
	for (i = 0; i < len; i++)
	{
		UART_TxByte(uartHandle, data[i]);
	}
}

void UART_TxCancel(UART_Handle_T uartHandle)
{

}

uint8_t UART_Read(UART_Handle_T uartHandle)
{
	if (uartHandle->uart_Handle->SR & (1<<5))
	{
		uartHandle->uart_Handle->SR &= (~(1<<5));

		return uartHandle->uart_Handle->DR;
	}

	return 0;
}

void UART_Read_Polling(UART_Handle_T uartHandle)
{

}

