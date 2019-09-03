#ifndef __UART_CONFIG_H__
#define __UART_CONFIG_H__

/******************************************************************************************************************************
 *												      Preprocessor Constants
 ******************************************************************************************************************************/

/* Name USART is replaced with UART. */
#define UART1    USART1
#define UART2    USART2
#define UART3    USART3

#define UART1_TX_BUFFER_MAX_SIZE  (uint8_t)20
#define UART2_TX_BUFFER_MAX_SIZE  (uint8_t)20
#define UART3_TX_BUFFER_MAX_SIZE  (uint8_t)20


/* This macro includes the driver code for the enabled peripheral */
#define UART_1_PERIPHERAL_ENABLE    ON
#define UART_2_PERIPHERAL_ENABLE    ON
#define UART_3_PERIPHERAL_ENABLE    ON

#endif //__UART_CONFIG_H__
