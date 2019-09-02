#ifndef __UART_H__
#define __UART_H__

#include "uart_config.h"

/******************************************************************************************************************************
 *												  Driver Control Selection
 ******************************************************************************************************************************/




/******************************************************************************************************************************
 *												  Preprocessor Constants
 ******************************************************************************************************************************/

typedef enum UART_State_EN
{
    UART_State_Idle,
    UART_State_Tx,
    UART_State_Rx,
    UART_State_Err,
}UART_State_EN;

typedef enum _UART_Baudrate_EN
{
    UART_Baud_9600 = 0xC35,
    UART_Baud_19200,
    UART_Baud_57600,
}UART_Baudrate_EN;

typedef enum _UART_Operating_Mode_EN
{
    UART_Transmitter = 0,
    UART_Receiver = 1,
    UART_Transceiver = 2,
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

typedef struct _UART_Handle_ST
{
    uint16_t UART1_Configured : 1;
    uint16_t UART2_Configured : 1;
    uint16_t UART3_Configured : 1;
    uint16_t UART1_State : 2;
    uint16_t UART2_State : 2;
    uint16_t UART3_State : 2;
    uint16_t Reserved : 7;
}UART_Handle_ST;


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
	UART_Operating_Mode_EN Operating_Mode;
}UART_Config_ST;

extern UART_Handle_ST UART_Handle;

#endif //__UART_H__
