#ifndef __UART_H__
#define __UART_H__

/*< System Header file included in order to include the baudrate values according to the clock frequency */
#include <system.h>

#include "uart_config.h"


/******************************************************************************************************************************
 *												  Macro Definitions
 ******************************************************************************************************************************/
/**
 * @brief : Macro to enable clock for UART peripherals
 **/

#define UART1_CLOCK_ENABLE()   RCC->APB2ENR |= ((uint32_t)(1 << 14))
#define UART2_CLOCK_ENABLE()   RCC->APB1ENR |= ((uint32_t)(1 << 17))
#define UART3_CLOCK_ENABLE()   RCC->APB1ENR |= ((uint32_t)(1 << 18))

/**
 * @brief : Macro to disable clock for UART peripherals
 **/

#define UART1_CLOCK_DISABLE()   RCC->APB2ENR &= (~((uint32_t)(1 << 14)))
#define UART2_CLOCK_DISABLE()   RCC->APB1ENR &= (~((uint32_t)(1 << 17)))
#define UART3_CLOCK_DISABLE()   RCC->APB1ENR &= (~((uint32_t)(1 << 18)))


/******************************************************************************************************************************
 *												        Macro Definitions
 ******************************************************************************************************************************/

/**
 * @brief: Number of UART channels in STM32F103C8T6
 */
#define DEVICE_UART_CHANNEL_MAX          ((uint8_t)0X03)

/**
 * @brief: UART Channels
 */
#define DEVICE_UART_CHANNEL_NONE         ((uint8_t)0X00)
#define DEVICE_UART_CHANNEL_1            ((uint8_t)0X01)
#define DEVICE_UART_CHANNEL_2            ((uint8_t)0X02)
#define DEVICE_UART_CHANNEL_3            ((uint8_t)0X03)

/**
 * @brief: UART Modes
 */
#define DEVICE_UART_MODE_NONE            ((uint8_t)0X00)
#define DEVICE_UART_MODE_TX              ((uint8_t)0X02)
#define DEVICE_UART_MODE_RX              ((uint8_t)0X01)
#define DEVICE_UART_MODE_TXRX            ((uint8_t)0X03)

/**
 * @brief: UART Packet Length
 *         StartBit - 8/9 databit - stopbit 
 */
#define DEVICE_UART_WORD_LEN_8           ((uint8_t)0x00)
#define DEVICE_UART_WORD_LEN_9           ((uint8_t)0x01)

/**
 * @brief: UART Frame StopBits
 */
#define DEVICE_UART_STOP_BIT_1           ((uint8_t)0x00)
#define DEVICE_UART_STOP_BIT0_5          ((uint8_t)0x01)
#define DEVICE_UART_STOP_BIT2            ((uint8_t)0x02)
#define DEVICE_UART_STOP_BIT1_5          ((uint8_t)0x03)

/**
 * @brief: UART Parity Bits
 */
#define DEVICE_UART_PARITY_EVEN          ((uint8_t)0X00)
#define DEVICE_UART_PARITY_ODD           ((uint8_t)0X01)
#define DEVICE_UART_PARITY_NONE          ((uint8_t)0X02)

/**
 * @brief : UART Baudrate
 **/
#define DEVICE_UART_BR_9600  ((uint16_t)0X9C4)

/******************************************************************************************************************************
 *												           Typedefs
 ******************************************************************************************************************************/

typedef struct UART_Params_Tag
{
    uint8_t uart_Channel;           /*< Refer "UART Channels" macros for available ports */
    uint8_t uart_OperatingMode;     /*< */
    uint8_t uart_WordLength;        /*< */
    uint8_t uart_StopBits;          /*< */
    uint8_t uart_Parity;            /*< */
    uint8_t uart_RxCallBack;        /*< */
    uint8_t uart_TxCallBack;        /*< */
	uint16_t uart_Baudrate;         /*< */
}UART_Params_T;

typedef struct UART_Handle_Tag
{
    uint8_t uart_Channel;           /*< Refer "UART Channels" macros for available ports */
    USART_TypeDef *uart_Handle;     /*< Refer "UART Peripheral Base address" macros for base address
                                        This member holds the base address of UART peripheral in flash memory */
    uint8_t uart_OperatingMode;     /*< Refer "UART Modes" macros for operating modes */
}UART_Handle_T;


/**
 * @brief : 
 * @param :
 * @return:
 **/
extern void UART_Params_Init(UART_Params_T *uartParams);

/**
 * @brief : 
 * @param :
 * @return:
 **/
extern UART_Handle_T*  UART_SetConfig(UART_Params_T *uartParams);

/**
 * @brief : 
 * @param :
 * @return: 
 **/
extern void UART_ReleaseConfig(UART_Handle_T* uarthandle);

/**
 * @brief:
 * @param:
 * @return:
 **/
extern uint8_t UART_Open(UART_Handle_T *uart_params);

/**
 * @brief:
 * @param:
 * @return:
 **/
extern void UART_Close(UART_Handle_T *uart_params);

/**
 * @brief:
 * @param:
 * @return:
 **/
extern void UART_TxByte(UART_Handle_T *uart_params, uint8_t data)                                                                       ;

/**
 * @brief:
 * @param:
 * @return:
 **/
extern void UART_TxString(UART_Handle_T *uart_params, uint8_t *data, uint16_t len);

/**
 * @brief:
 * @param:
 * @return:
 **/
extern void UART_TxPolling(UART_Handle_T *uart_params, const char *data);

/**
 * @brief:
 * @param:
 * @return:
 **/
extern void UART_TxCancel(UART_Handle_T *uart_params);

/**
 * @brief:
 * @param:
 * @return:
 **/
extern uint8_t UART_Read(UART_Handle_T *uart_params);

/**
 * @brief:
 * @param:
 * @return:
 **/
extern void UART_Read_Polling(UART_Handle_T *uart_params);

#endif //__UART_H__
