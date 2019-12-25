#include <includes.h>
#include FLASH_H

static HAL_StatusTypeDef Flash_WaitForLastOperation(void)
{
  while (__HAL_FLASH_GET_FLAG(FLASH_FLAG_BSY))
    ;

  /* Check FLASH End of Operation flag  */
  if (__HAL_FLASH_GET_FLAG(FLASH_FLAG_EOP))
  {
    /* Clear FLASH End of Operation pending bit */
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP);
  }

  if (__HAL_FLASH_GET_FLAG(FLASH_FLAG_WRPERR) ||
      __HAL_FLASH_GET_FLAG(FLASH_FLAG_OPTVERR) ||
      __HAL_FLASH_GET_FLAG(FLASH_FLAG_PGERR))
  {
    return HAL_ERROR;
  }

  /* There is no error flag set */
  return HAL_OK;
}

HAL_StatusTypeDef HAL_FLASH_Unlock(void)
{
  HAL_StatusTypeDef status = HAL_OK;

  if (READ_BIT(FLASH->CR, FLASH_CR_LOCK) != RESET)
  {
    /* Authorize the FLASH Registers access */
    WRITE_REG(FLASH->KEYR, FLASH_UNLOCK_KEY1);
    WRITE_REG(FLASH->KEYR, FLASH_UNLOCK_KEY2);

    /* Verify Flash is unlocked */
    if (READ_BIT(FLASH->CR, FLASH_CR_LOCK) != RESET)
    {
      status = HAL_ERROR;
    }
  }
  return status;
}

HAL_StatusTypeDef HAL_FLASH_Lock(void)
{
  /* Set the LOCK Bit to lock the FLASH Registers access */
  SET_BIT(FLASH->CR, FLASH_CR_LOCK);

  return HAL_OK;
}

static void FLASH_Program_HalfWord(uint32_t Address, uint16_t Data)
{
  /* Proceed to program the new data */
  SET_BIT(FLASH->CR, FLASH_CR_PG);

  /* Write data in the address */
  *(__IO uint16_t *)Address = Data;
}

HAL_StatusTypeDef HAL_FLASH_Program(uint32_t TypeProgram, uint32_t Address, uint64_t Data)
{
  HAL_StatusTypeDef status = HAL_ERROR;
  uint8_t index = 0;
  uint8_t nbiterations = 0;

  /* Check the parameters */
  assert_param(IS_FLASH_TYPEPROGRAM(TypeProgram));
  assert_param(IS_FLASH_PROGRAM_ADDRESS(Address));

  status = Flash_WaitForLastOperation();

  if (status == HAL_OK)
  {
    if (TypeProgram == FLASH_TYPEPROGRAM_HALFWORD)
    {
      /* Program halfword (16-bit) at a specified address. */
      nbiterations = 1U;
    }
    else if (TypeProgram == FLASH_TYPEPROGRAM_WORD)
    {
      /* Program word (32-bit = 2*16-bit) at a specified address. */
      nbiterations = 2U;
    }
    else
    {
      /* Program double word (64-bit = 4*16-bit) at a specified address. */
      nbiterations = 4U;
    }

    for (index = 0U; index < nbiterations; index++)
    {
      FLASH_Program_HalfWord((Address + (2U * index)), (uint16_t)(Data >> (16U * index)));

      /* Wait for last operation to be completed */
      status = Flash_WaitForLastOperation();

      /* If the program operation is completed, disable the PG Bit */
      CLEAR_BIT(FLASH->CR, FLASH_CR_PG);
      if (status != HAL_OK)
      {
        break;
      }
    }
  }
  
  return status;
}
