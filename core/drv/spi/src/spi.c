#include <platform.h>

/******************************************************************************************************************************
 *												      Variable Definitions
 ******************************************************************************************************************************/

SPI_BUFFER_TYPE  SPI_Tx_Buffer[SPI_BUFFER_MAX];

unsigned char SPI_Tx_Buffer_Index = 0;


/******************************************************************************************************************************
 *												      Function Definitions
 ******************************************************************************************************************************/


void SPI_Config_Init(SPI_Config *spi_param)
{

}

void SPI_Tx_Byte(SPI_TypeDef* SPI_Base, SPI_BUFFER_TYPE Byte)
{

}

void SPI_Tx_String(SPI_TypeDef* SPI_Base, SPI_BUFFER_TYPE *Buffer_Base)
{

}

void SPI_Tx_Init(SPI_TypeDef* SPI_Base,SPI_BUFFER_TYPE *Buffer_Base, unsigned char Buffer_Size)
{

}
