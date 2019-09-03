#ifndef __UART_H__
#define __UART_H__

#include "uart_config.h"

/******************************************************************************************************************************
 *												  Driver Control Selection
 ******************************************************************************************************************************/




/******************************************************************************************************************************
 *												  Preprocessor Constants
 ******************************************************************************************************************************/

#define ENABLE_UART1_CLOCK()   RCC->APB2ENR |= (uint32_t)(1 << 14)
#define ENABLE_UART2_CLOCK()   RCC->APB1ENR |= (uint32_t)(1 << 17)
#define ENABLE_UART3_CLOCK()   RCC->APB1ENR |= (uint32_t)(1 << 18)


/******************************************************************************************************************************
 *												    Typde Definitions
 ******************************************************************************************************************************/

typedef enum UART_State_EN
{
    UART_State_Idle,
    UART_State_Tx,
    UART_State_Rx,
    UART_State_TxRx,
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

typedef struct _UART_Watchdog_ST
{
    uint8_t UART1_State : 2;
    uint8_t UART2_State : 2;
    uint8_t UART3_State : 2;
    uint8_t Reserved : 2;
}UART_Watchdog_ST;


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
}UART_Config_ST;

/******************************************************************************************************************************
 *												  Variable Declaration
 ******************************************************************************************************************************/


extern UART_Watchdog_ST UART_Watchdog;


/******************************************************************************************************************************
 *												  Function Declaration
 ******************************************************************************************************************************/

extern unsigned char UART_Config_Init(UART_Config_ST *InitStruct);

extern unsigned char UART_Tx_Bytes_Interrupt(USART_TypeDef *Handle, uint8_t *BufferBase, uint8_t BufferSize);

extern void UART_Tx_Bytes(USART_TypeDef *Handle, uint8_t Bytes);

extern void UART_Tx_String(USART_TypeDef *Handle, uint8_t *Base);

extern uint8_t UART_Rx_Bytes_Polling(USART_TypeDef *Handle);

#endif //__UART_H__
