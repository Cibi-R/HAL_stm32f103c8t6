#include <app.h>

void delay(void)
{
	uint32_t i;
	
	for (i=0; i< 10000; i++);
}

void Flash_Init(void)
{

	FLASH_Unlock();
	
	FLASH_Program(FLASH_PROGRAM_WORD,0x08002408U,0xddccbbAA );
	FLASH_Program(FLASH_PROGRAM_WORD,0x0800240CU,0x33221100 );
	
	FLASH_Lock();
}
