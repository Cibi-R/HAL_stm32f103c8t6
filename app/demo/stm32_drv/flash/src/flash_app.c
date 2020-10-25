#include <app.h>

void Flash_Delay(void)
{
	uint16_t i;
	
	for (i=0; i<10000; i++);
}

void Flash_App_Test(void)
{	
	#if 0
	uint8_t data = 0XBB;
	
	Flash_Write_Bit8(0X8002001, &data);
	#endif
	
	#if 0
	uint32_t add = 0X8002001U;
	for (uint16_t i = 0X0001; i < 0XFF; i++)
	{
		Flash_Write_Bit16(add, &i);
		add += 2;
	}
	#endif
	
	#if 0
	uint32_t add = 0X8002000;
	
	uint8_t value[5] = {0xAA,0XBB, 0XCC, 0XDD, 0XEE};
	
	Flash_Write_Stream(add, value, 5);
	#endif
	
	#if 0
	uint32_t add = 0X08002000;
	
	uint32_t value = 0XDDCCBBAA;
	
	Flash_Write_Bit32(add, &value);
	
	Flash_Erase_Page(8);
	#endif
	
	#if 1
	Flash_Erase_Mass();
	#endif
}
