#include <includes.h>
#include UART_H
//#include FLASH_H
//#include FLASH_APP_H

void delay(void)
{
	uint32_t i;
	
	for (i=0; i< 10000; i++);
}

void Flash_Init(void)
{
	/*
	HAL_FLASH_Unlock();
	
	HAL_FLASH_Program(2U,0x08002400U,0xddccbbAA );
	HAL_FLASH_Program(2U,0x08002404U,0x33221100 );
	
	HAL_FLASH_Lock();
	*/
}
