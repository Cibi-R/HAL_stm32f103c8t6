#include <includes.h>
#include FLASH_H

static HAL_Status Flash_Is_Busy(void)
{
	HAL_Status Status = HAL_Ok;

	/*< Wait till the ongoing flash operation got completed. */
	while (FLASH->SR & FLASH_SR_BSY);

	/*< Clear the End Of Operation flag if it is set. */
	if (FLASH->SR & FLASH_SR_EOP)
	{
		FLASH->SR |= FLASH_SR_EOP;
	}

	/*< In case of programming error or write protection error return HAL error. */
	if ((FLASH->SR & FLASH_SR_PGERR) || (FLASH->SR & FLASH_SR_WRPRTERR))
	{
		Status = HAL_Err;
	}

	return Status;
}

HAL_Status FLASH_Unlock(void)
{
	HAL_Status status = HAL_Ok;

	/*< Check if the LOCK Bit is set. */
	if (FLASH->CR & FLASH_CR_LOCK)
	{
		/*< Perform the key write operation to unlock the flash controller. */
		FLASH->KEYR = FLASH_UNLOCK_KEY1;
		FLASH->KEYR = FLASH_UNLOCK_KEY2;

		/*< If it is not unlocked return HAL Error. */
		if (READ_BIT(FLASH->CR, FLASH_CR_LOCK) != RESET)
		{
			status = HAL_Err;
		}
	}
	return status;
}

HAL_Status FLASH_Lock(void)
{
	/*< Set Lock bit of the Control register to Lock the flash controller. */
	FLASH->CR |= FLASH_CR_LOCK;

	return HAL_Ok;
}

static void FLASH_Program_HalfWord(uint32_t Address, uint16_t Data)
{
	/*< Set Programming bit to enable the flash programming. */
	FLASH->CR |= FLASH_CR_PG;

	/*< Write the desired value into the memory location. */
	*(volatile uint16_t *)Address = Data;
}

HAL_Status FLASH_Program(FlashType_EN ProgramType, uint32_t Address, uint64_t Data)
{
	HAL_Status status = HAL_Err;

	status = Flash_Is_Busy();

	if (status == HAL_Ok)
	{
		for (uint8_t i = 0U; i < ProgramType; i++)
		{
			FLASH_Program_HalfWord((Address + (2U * i)), (uint16_t)((Data >> (16U * i)) & 0xFFFF));

			status = Flash_Is_Busy();

			/*< Clear the flash programming bit. */
			FLASH->CR &= (~FLASH_CR_PG);

			if (status != HAL_Ok)
			{
				break;
			}
		}
	}

	return status;
}
