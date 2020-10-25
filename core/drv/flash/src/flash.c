#include <platform.h>

static uint8_t Flash_Is_Write_Completed(void)
{
	uint8_t retVal = FLASH_OK;
	uint16_t timeout = FLASH_TIMEOUT;

	/*< Wait till the ongoing flash operation got completed. */
	while ((FLASH->SR & FLASH_SR_BSY) && (timeout))
	{
		timeout--;
	}

	if (timeout)
	{
		/*< Clear the End Of Operation flag if it is set. */
		if (FLASH->SR & FLASH_SR_EOP)													
		{
			FLASH->SR |= FLASH_SR_EOP;
		}

		/*< Check for write protection error */
		if (FLASH->SR & FLASH_SR_WRPRTERR)
		{
			retVal |= FLASH_WRITE_PROT_ERROR;
		}

		/*< Check for programming error */
		if (FLASH->SR & FLASH_SR_PGERR)
		{											
			retVal |= FLASH_PROG_ERROR;
		}
	}
	else
	{
		retVal |= FLASH_TIMEOUT_ERROR;
	}

	
	/*< Clear the Programming bit in control register to enable the flash programming. */
	FLASH->CR &= (~(FLASH_CR_PG));

	return retVal;
}

static uint8_t Flash_Is_Locked(void)
{
	return ((FLASH->CR & FLASH_CR_LOCK) >> 7U);
}

static uint8_t Flash_Unlock(void)
{
	uint16_t timeout = FLASH_TIMEOUT;

	/*< Perform the key write operation to unlock the flash controller. */
	FLASH->KEYR = FLASH_UNLOCK_KEY1;
	FLASH->KEYR = FLASH_UNLOCK_KEY2;

	while ((FLASH->CR & FLASH_CR_LOCK) && (timeout))
	{
		timeout--;
	}

	return ((timeout) ? FLASH_OK : FLASH_UNLOCK_ERROR);
}

static uint8_t Flash_Lock(void)
{
	uint16_t timeout = FLASH_TIMEOUT;

	/*< Set Lock bit of the Control register to Lock the flash controller. */
	FLASH->CR |= FLASH_CR_LOCK;

	while ((!(FLASH->CR & FLASH_CR_LOCK)) && (timeout))
	{
		timeout--;
	}

	return ((timeout) ? FLASH_OK : FLASH_LOCK_ERROR);
}

static uint8_t Flash_Write(uint32_t add, uint16_t bits_16)
{
	/*< Set the Programming bit in control register to enable the flash programming. */
	FLASH->CR |= FLASH_CR_PG;

	/*< Write the desired value into the memory location. */
	*(volatile uint16_t *)add = bits_16;

	/*< Return the status of the write operation */
	return Flash_Is_Write_Completed();
}

uint8_t Flash_Write_Bit8(uint32_t startAdd, uint8_t *data)
{
	uint16_t flashValue;
	uint8_t retVal = FLASH_OK;

	if (Flash_Is_Locked())
	{
		retVal = Flash_Unlock();
	}

	if (retVal == FLASH_OK)
	{
		if (Flash_Read_Bit16(startAdd, &flashValue) == FLASH_OK)
		{
			flashValue &= (uint16_t)0XFF00;
			flashValue |= ((uint16_t)(*data));

			retVal = Flash_Write(startAdd, flashValue);
		}
	}
	
	retVal = Flash_Lock();

	return retVal;
}

uint8_t Flash_Write_Bit16(uint32_t startAdd, uint16_t *data)
{
	uint8_t retVal = FLASH_OK;

	if (Flash_Is_Locked())
	{
		retVal = Flash_Unlock();
	}

	if (FLASH_OK == retVal)
	{
		retVal = Flash_Write(startAdd, *data);
	}
	
	retVal = Flash_Lock();

	return retVal;
}

uint8_t Flash_Write_Bit32(uint32_t startAdd, uint32_t *data)
{
	uint8_t retVal = FLASH_OK;

	if (Flash_Is_Locked())
	{
		retVal = Flash_Unlock();
	}

	if (FLASH_OK == retVal)
	{
		retVal = Flash_Write(startAdd, ((uint16_t)(*data & ((uint32_t)0XFFFF))));

		startAdd += 2U;

		retVal |= (Flash_Write(startAdd, ((uint16_t) (((*data & (uint32_t)0XFFFF0000) >> 16) & 0XFFFF))));
	}
	
	retVal = Flash_Lock();

	return retVal;
}

uint8_t Flash_Write_Stream(uint32_t startAdd, uint8_t *data, uint8_t length)
{
	uint16_t flashValue = 0U;
	uint8_t i = FLASH_OK;
	
	if (Flash_Is_Locked())
	{
		i = Flash_Unlock();
	}
	
	if (FLASH_OK == i)
	{
		for (i = 1; i < length + 1; i++)
		{
			if (!(i & (uint8_t)0X01))
			{
				flashValue |= (((uint16_t)data[i - 1]) << 8);

				Flash_Write(startAdd, flashValue);

				startAdd += 2;

				flashValue = 0U;
			}
			else
			{
				flashValue |= ((uint16_t)data[i - 1]);
			}
		}

		if (length & 0X01)
		{
			flashValue = ((uint16_t)data[length - 1]) | ((uint16_t)0XFF00);
			Flash_Write_Bit16(startAdd, &flashValue);
		}	
	}
	
	return 0;
}

uint8_t Flash_Read_Bit8(uint32_t startAdd, uint8_t* data)
{
	*data = (*((uint8_t*)(startAdd)));

	return FLASH_OK;
}

uint8_t Flash_Read_Bit16(uint32_t startAdd, uint16_t* data)
{
	*data = (*((uint16_t*)(startAdd)));

	return FLASH_OK;
}

uint8_t Flash_Read_Bit32(uint32_t startAdd, uint32_t* data)
{
	*data =  (*((uint32_t*)(startAdd)));

	return FLASH_OK;
}

uint8_t Flash_Read_Stream(uint32_t startAdd, uint8_t* stream, uint8_t length)
{
	uint8_t i = 0;

	for (i = 0; i < length; i++)
	{
		stream[i] = (*((uint8_t*)startAdd));
	}

	return FLASH_OK;
}

uint8_t Flash_Erase_Page(uint8_t page)
{
	return 0;
}

uint8_t Flash_Erase_Parition(uint8_t partition)
{
	return 0;
}

uint8_t Flash_Erase_Complete(void)
{
	return 0;
}
