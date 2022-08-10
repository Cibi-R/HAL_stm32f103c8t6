#ifndef __UART_H__
#define __UART_H__

/*< System Header file included in order to include the baudrate values according to the clock frequency */
#if 0
#include <system.h>
#endif

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
 * @brief: UART Channels
 */
#define DEVICE_UART_CHANNEL_NONE         ((uint8_t)0X00)
#define DEVICE_UART_CHANNEL_1            ((uint8_t)0X01)
#define DEVICE_UART_CHANNEL_2            ((uint8_t)0X02)
#define DEVICE_UART_CHANNEL_3            ((uint8_t)0X03)
#define DEVICE_UART_CHANNEL_MAX          ((uint8_t)0X04)

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
    uint8_t uart_Channel;           /*< Refer "UART Channels" macros */
    uint8_t uart_OperatingMode;     /*< Refer "UART Modes" macros */
    uint8_t uart_WordLength;        /*< Refer "UART Packet Length" macros */
    uint8_t uart_StopBits;          /*< Refer "UART Frame StopBits" macros */
    uint8_t uart_Parity;            /*< Refer "UART Parity Bits" macros */
    uint8_t uart_Reserved;          /*< reserved member */
    uint16_t uart_Baudrate;         /*< Refer  "UART baudrate" macro */
    void (*uart_RxCallBack)(uint8_t);       /*< Not yet implemented */
    uint32_t uart_TxCallBack;       /*< Not yet implemented */
}UART_Params_T;

typedef struct UART_Handle_Tag
{
    uint8_t uart_Channel;           /*< Refer "UART Channels" macros for available ports */
    uint8_t uart_OperatingMode;     /*< Refer "UART Modes" macros for operating modes */
    USART_TypeDef *uart_Handle;     /*< Refer "UART Peripheral Base address" macros for base address
                                        This member holds the base address of UART peripheral in flash memory */
}UART_Handle_Tag;

typedef UART_Handle_Tag* UART_Handle_T;

/**
 * @brief : To set the default values for UART peripheral while initialization
 * @param : UART_Params_T
 * @return: void
 **/
extern void UART_Params_Init(UART_Params_T *uartParams);

/**
 * @brief : To configure the UART channel with the supplied configuration
 * @param : UART_Params_T
 * @return: UART_Handle_T
 **/
extern UART_Handle_T  UART_SetConfig(UART_Params_T *uartParams);

/**
 * @brief : To release the configured UART channel
 * @param : UART_Handle_T
 * @return: void
 **/
extern void UART_ReleaseConfig(UART_Handle_T uartHandle);

/**
 * @brief: To enable clock to the UART peripheral, By default UART clock will be enabled after configuration if closed exclicitly (UART_Close),
 *         we need enable the enable clock
 * @param: uint8_t
 * @return:void
 **/
extern void UART_Open(uint8_t uartChannel);

/**
 * @brief : To disable clock to the UART peripheral, If disabled, the clock needs to enabled before the next use of the UART
 * @param : uartChannel
 * @return: void
 **/
extern void UART_Close(uint8_t uartChannel);

/**
 * @brief :
 * @param :
 * @return:
 **/
extern void UART_TxByte(UART_Handle_T uartHandle, uint8_t data);

/**
 * @brief:
 * @param:
 * @return:
 **/
extern void UART_TxString(UART_Handle_T uartHandle, uint8_t *data, uint16_t len);

/**
 * @brief:
 * @param:
 * @return:
 **/
extern void UART_TxCancel(UART_Handle_T uartHandle);

/**
 * @brief:
 * @param:
 * @return:
 **/
extern uint8_t UART_Read(UART_Handle_T uartHandle);

/**
 * @brief:
 * @param:
 * @return:
 **/
extern void UART_Read_Polling(UART_Handle_T uartHandle);

#endif //__UART_H__


