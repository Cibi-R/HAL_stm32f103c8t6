#ifndef __UART_H__
#define __UART_H__

#include "uart_config.h"


/******************************************************************************************************************************
 *												  Preprocessor Constants
 ******************************************************************************************************************************/

//#define NULL ((void*)0)

#define ENABLE_UART1_CLOCK()   RCC->APB2ENR |= (uint32_t)(1 << 14)
#define ENABLE_UART2_CLOCK()   RCC->APB1ENR |= (uint32_t)(1 << 17)
#define ENABLE_UART3_CLOCK()   RCC->APB1ENR |= (uint32_t)(1 << 18)


/******************************************************************************************************************************
 *												    Typde Definitions
 ******************************************************************************************************************************/

typedef enum _UART_Baudrate_EN
{
    UART_Baud_9600 = 0xC35,
    UART_Baud_19200,
    UART_Baud_57600,
}UART_Baudrate_EN;

typedef enum _UART_Operating_Mode_EN
{
    UART_Receiver = 1,
    UART_Transmitter,
    UART_Transceiver,
}UART_Operating_Mode_EN;

typedef enum _UART_WordLength_EN
{
    UART_8Bit = 0,
    UART_9Bit,
}UART_WordLength_EN;

typedef enum _UART_Parity_Selection_EN
{
    UART_Even_Parity = 0,
    UART_Odd_Parity,
    UART_No_Parity,
}UART_Parity_Selection_EN;

typedef enum _UART_StopBits_EN
{
    /* 1 */
    UART_1_StopBit = 0,
    /* 0.5 */  
    UART_05_StopBit,
    /* 2 */
    UART_2_StopBit,
    /* 1.5 */
    UART_15_StopBit,
}UART_StopBits_EN;


typedef struct _UART_Config_ST
{
    USART_TypeDef* Instance;

     /* If word length is 8 and parity is enabled, Parity bit will be inserted at 8 bit location. */
    UART_WordLength_EN WordLength;

    /* Based on the value of ParitySelection Parity control will be enabled or disabled. */
    UART_Parity_Selection_EN ParitySelection;

    /* To select the Stop bit duration. */
    UART_StopBits_EN StopBits;
	
	/* To select the baudrate of the UART peripheral. */
	UART_Baudrate_EN BaudRate;
	
	/* To configure the operating mode. */
	UART_Operating_Mode_EN OperatingMode;

    /* Assign the address of the function to be handled during UART reception if not used assign NULL */
    void (*UART_Rx_ISR)(void);
}UART_Config_ST;


/******************************************************************************************************************************
 *												  Function Declaration
 ******************************************************************************************************************************/

/*
 * @brief  : To Configure the UART peripheral
 * @para   : UART Init struct
 * @return : HAL_Status - indicating that the initialization is succeeded or not.
 */

extern HAL_Status UART_Config_Init(UART_Config_ST *InitStruct);


/*
 * @brief  : To Send 1 byte through UART
 * @para   : USART_Typtedef - Base Add of UART through which we are transmitting, uint8_t. Byte to be transmitted.
 * @return : HAL_Status - Status of transmission
 */

extern HAL_Status UART_Tx_Bytes(USART_TypeDef*, uint8_t Data);


/*
 * @brief  : To Send an Array of bytes through array.
 * @para   : USART_Typtedef - Base Add of UART through which we are transmitting, uint8_t - Base add of array, uint8_t - Len of array
 * @return : HAL_Status - Transmission status.
 */

extern HAL_Status UART_Tx_Array(USART_TypeDef *Handle, uint8_t *const Base, uint8_t Len);


/*
 * @brief  : To send string through UART.
 * @para   : USART_Typtedef - Base Add of UART through which we are transmitting, Base Add of string.
 * @return : HAL_Status - Transmission status.
 */

extern HAL_Status UART_Tx_String(USART_TypeDef *Handle, const uint8_t *Data);


/*
 * @brief  : To retrieve the received byte. This function should be called inside UART_Rx_ISR function.
 * @para   : USART_Typtedef - Base Add of UART
 * @return : uint8_t - Retrieved bytes.
 */

extern uint8_t UART_Rx_Bytes(USART_TypeDef *Handle);

#endif //__UART_H__
