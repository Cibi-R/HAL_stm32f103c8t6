#ifndef __SPI_H__
#define __SPI_H__

#include "../api/spi_config.h"

/******************************************************************************************************************************
 *												      Preprocessor Constants
 ******************************************************************************************************************************/

/* SPI Clock related constants */

#define SPI_1_CLOCK_ENABLE()    RCC->APB2ENR |= (1<<12)
#define SPI_2_CLOCK_ENABLE()    RCC->APB1ENR |= (1<<14)
#define SPI_3_CLOCK_ENABLE()    RCC->APB1ENR |= (1<<15)

/******************************************************************************************************************************
 *												      Typedef definitions
 ******************************************************************************************************************************/

/* For SPI States */

typedef enum _SPI_Current_State_EN
{
    SPI_STATE_IDLE,
    SPI_STATE_BUSY_TX,
}SPI_Current_State_EN;

/* For SPI Parameter Initialization */

typedef struct _SPI_Init_ST
{
    uint32_t SPI_Mode : 1;
    uint32_t SPI_Direction : 2;
    uint32_t SPI_Phase : 1;
    uint32_t SPI_Polarity : 1;
    uint32_t SPI_Prescalar : 3;
    uint32_t SPI_On : 1;
    uint32_t SPI_FirstBit : 1;
    uint32_t SPI_DataSize : 1;
    uint32_t SPI_NSS : 2;
}SPI_Init_ST;

/* For SPI Peripheral Configuration */

typedef struct _SPI_Config
{
    SPI_TypeDef *SPI_Base;
    SPI_Init_ST Init;
    SPI_BUFFER_TYPE *Tx_Buffer;
    unsigned char Tx_Buffer_Size;
    SPI_Current_State_EN SPI_Current_State;
}SPI_Config;

#endif //__SPI_H__
