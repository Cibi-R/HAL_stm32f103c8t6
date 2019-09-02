#include <includes.h>
#include UART_H

/******************************************************************************************************************************
 *												 Variable Definitions
 ******************************************************************************************************************************/

UART_Handle_ST UART_Handle;

#if (UART_1_PERIPHERAL_ENABLE == ON)
    uint8_t UART1_TxBuffer[UART1_TX_BUFFER_MAX_SIZE];
    uint8_t UART1_TxBufferIndex;
#endif

#if (UART_2_PERIPHERAL_ENABLE == ON)
    uint8_t UART2_TxBuffer[UART2_TX_BUFFER_MAX_SIZE];
    uint8_t UART2_TxBufferIndex;
#endif

#if (UART_2_PERIPHERAL_ENABLE == ON)
    uint8_t UART3_TxBuffer[UART3_TX_BUFFER_MAX_SIZE];
    uint8_t UART3_TxBufferIndex;
#endif

/******************************************************************************************************************************
 *												  UART Subroutines
 ******************************************************************************************************************************/

#if UART_1_PERIPHERAL_ENABLE == ON

void USART1_IRQHandler(void)
{

}

#endif //UART_1_PERIPHERAL_ENABLE

#if UART_2_PERIPHERAL_ENABLE == ON

void USART2_IRQHandler(void)
{

}

#endif //UART_2_PERIPHERAL_ENABLE

#if UART_3_PERIPHERAL_ENABLE == ON

void USART3_IRQHandler(void)
{

}

#endif //UART_3_PERIPHERAL_ENABLE

/******************************************************************************************************************************
 *												 Function Definitions
 ******************************************************************************************************************************/

static void UART_Config_Mode(USART_TypeDef *Handle,UART_Operating_Mode_EN Operating_Mode)
{
	/* Clear the Transmitter and Receiver enable bits. */
	Handle->CR1 &= (~(0x3<<2));
	
	switch (Operating_Mode)
	{
		case UART_Transmitter:
			Handle->CR1 |= (1<<3);
			break;
		
		case UART_Receiver:
			Handle->CR1 |= (1<<2);
			break;
		
		case UART_Transceiver:
			Handle->CR1 |= (0x3<<2);
			break;
	}
}


void UART_Config_Init(UART_Config_ST* InitStruct)
{
    USART_TypeDef *Handle;
	
	Handle = InitStruct->Instance;
	
	/* Configure word length. */
	Handle->CR1 &= (~(1<<12));
	Handle->CR1 |= (InitStruct->WordLength << 12);
	
	/* Configure parity control and selection bits. */
	if (InitStruct->ParitySelection != UART_No_Parity)
	{
		/* Enable Parity Control. */
		Handle->CR1 |= (1<<10);
		
		/* Parity Selection. */
		Handle->CR1 &= (~(1<<9));
		Handle->CR1 |= (InitStruct->ParitySelection<<9);
	}else{ Handle->CR1 &= (~(1<<10)); /* Disable Parity Control. */ }
	
	/* Configure Stopbits. */
	Handle->CR2 &= (~(0x3<<12));
	Handle->CR2 |= (InitStruct->StopBits<<12);
	
	/* Configure Baudrates. */
	Handle->BRR = 0;
	Handle->BRR = (0xFFFF & InitStruct->BaudRate);
	
	/* Configure the operating mode. */
	UART_Config_Mode(Handle,InitStruct->Operating_Mode);
}

void UART_Tx_Bytes_Interrupt(USART_TypeDef *Handle,uint8_t BufferBase, uint8_t BufferSize)
{
	#if (UART_1_PERIPHERAL_ENABLE == ON)

    if ( (Handle == UART1) && (UART_Handle.UART1_Configured == 1) && (UART_Handle.UART1_State == UART_State_Idle) )
    {
		UART_Handle.UART1_State = UART_State_Tx;
    }

	#endif //UART_1_PERIPHERAL_ENABLE

	#if (UART_2_PERIPHERAL_ENABLE == ON)

    if ( (Handle == UART2) && (UART_Handle.UART2_Configured == 1) && (UART1_Handle.UART1_State == UART_State_Idle))
    {
		UART_Handle.UART2_State = UART_State_Tx;
    }

	#endif //UART_2_PERIPHERAL_ENABLE

	#if (UART_3_PERIPHERAL_ENABLE == ON)

    if ( (Handle == UART3) && (UART_Handle.UART3_Configured == 1) && (UART1_Handle.UART1_State == UART_State_Idle) )
    {
        UART_Handle.UART2_State = UART_State_Tx;
    }

	#endif //UART_3_PERIPHERAL_ENABLE

    else
    {
		/* On failure it will return 0 */
        return 0;
    }

	/* On success it will return 1. */
	return 1; 
}

void UART_Tx_Bytes(USART_TypeDef *Handle,uint8_t Bytes)
{
	#if (UART_1_PERIPHERAL_ENABLE == ON)

	if ( (Handle == UART1) && (UART_Handle.UART1_Configured == 1) )
    {

    }

	#if (UART_2_PERIPHERAL_ENABLE == ON)

    if ( (Handle == UART2) && (UART_Handle.UART2_Configured == 1) )
    {
        
    }

	#if (UART_3_PERIPHERAL_ENABLE == ON)

    if ( (Handle == UART1) && (UART_Handle.UART3_Configured == 1) )
    {
        
    }

	#endif //End

	#if ((UART_1_PERIPHERAL_ENABLE == ON) || (UART_2_PERIPHERAL_ENABLE == ON) || (UART_3_PERIPHERAL_ENABLE == ON))

    else
    {
        return 0;
    }

	return 1;

	#elif

	return 0;

	#endif //End
}

void UART_Tx_String(USART_TypeDef *Handle, uint8_t *Base)
{
    while (*Base)
    {
        UART_Tx_Bytes(Handle,*Base);
        Base++;
    }
}

uint8_t UART_Rx_Bytes_Polling(USART_TypeDef *Handle)
{

}