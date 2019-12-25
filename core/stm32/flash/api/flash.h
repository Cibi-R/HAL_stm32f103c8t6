#ifndef __FLASH_H__
#define __FLASH_H__

/***************************************************************************************************************
 *												                      Macro definitions
 ***************************************************************************************************************/

/* Platform Macros */

#define SET_BIT(REG, BIT) ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT) ((REG) &= ~(BIT))

#define READ_BIT(REG, BIT) ((REG) & (BIT))

#define CLEAR_REG(REG) ((REG) = (0x0))

#define WRITE_REG(REG, VAL) ((REG) = (VAL))

#define READ_REG(REG) ((REG))

#define MODIFY_REG(REG, CLEARMASK, SETMASK) WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

#define POSITION_VAL(VAL) (__CLZ(__RBIT(VAL)))

#define assert_param(expr) ((void)0U)

#define IS_FLASH_PROGRAM_ADDRESS(ADDRESS) (((ADDRESS) >= FLASH_BASE) && (((*((uint16_t *)FLASH_SIZE_DATA_REGISTER)) == 0x80U) ? ((ADDRESS) <= FLASH_BANK1_END) : (((*((uint16_t *)FLASH_SIZE_DATA_REGISTER)) == 0x40U) ? ((ADDRESS) <= 0x0800FFFF) : (((*((uint16_t *)FLASH_SIZE_DATA_REGISTER)) == 0x20U) ? ((ADDRESS) <= 0x08007FFF) : ((ADDRESS) <= 0x08003FFFU)))))

#define OBR_REG_INDEX 1U

#define FLASH_FLAG_OPTVERR ((OBR_REG_INDEX << 8U | FLASH_OBR_OPTERR)) /*!< Option Byte Error        */

#define __HAL_FLASH_GET_FLAG(__FLAG__) (((__FLAG__) == FLASH_FLAG_OPTVERR) ? (FLASH->OBR & FLASH_OBR_OPTERR) : (FLASH->SR & (__FLAG__)))
#define __HAL_FLASH_CLEAR_FLAG(__FLAG__)       \
  do                                           \
  {                                            \
    /* Clear FLASH_FLAG_OPTVERR flag */        \
    if ((__FLAG__) == FLASH_FLAG_OPTVERR)      \
    {                                          \
      CLEAR_BIT(FLASH->OBR, FLASH_OBR_OPTERR); \
    }                                          \
    else                                       \
    {                                          \
      /* Clear Flag in Bank1 */                \
      FLASH->SR = (__FLAG__);                  \
    }                                          \
  } while (0U)

/* Flash control register */

#define FLASH_CTRL_LOCK ((uint32_t)0X00000080)  //Flash Lock bit
#define FLASH_CTRL_ER_ST ((uint32_t)0X00000040) //Erase start
#define FLASH_CTRL_ME_EN ((uint32_t)0X00000004) //Mass Erase
#define FLASH_CTRL_PE_EN ((uint32_t)0X00000002) //Page Erase
#define FLASH_PG_SET ((uint32_t)0X00000001)     //Flash programming

#define FLASH_PG_RESET (~FLASH_PG_SET)

/* Flash status register. */

#define FLASH_STATUS_EOP 0X00000020U
#define FLASH_STATUS_WPERR 0X00000010U
#define FLASH_STATUS_PGERR 0X00000004U
#define FLASH_STATUS_BUSY 0X00000001U

/* Flash key values. */
  
#define FLASH_UNLOCK_KEY1 0x45670123UL
#define FLASH_UNLOCK_KEY2 0xCDEF89ABUL

#define FLASH_KEY1_Pos (0U)
#define FLASH_KEY1_Msk (0x45670123UL << FLASH_KEY1_Pos) /*!< 0x45670123 */
#define FLASH_KEY1 FLASH_KEY1_Msk                       /*!< FPEC Key1 */
#define FLASH_KEY2_Pos (0U)
#define FLASH_KEY2_Msk (0xCDEF89ABUL << FLASH_KEY2_Pos) /*!< 0xCDEF89AB */
#define FLASH_KEY2 FLASH_KEY2_Msk                       /*!< FPEC Key2 */

/* Flash Program and Erase controller unlock/lock. */

#define FLASH_PROGRAM_ERASE_CTRL_UNLOCK() \
  FLASH->KEYR = FLASH_UNLOCK_KEY1;        \
  FLASH->KEYR = FLASH_UNLOCK_KEY2;

#define FLASH_PROGRAM_ERASE_CTRL_LOCK() FLASH->CR |= FLASH_CTRL_LOCK

#define FLASH_TYPEPROGRAM_HALFWORD 0x01U   /*!<Program a half-word (16-bit) at a specified address.*/
#define FLASH_TYPEPROGRAM_WORD 0x02U       /*!<Program a word (32-bit) at a specified address.*/
#define FLASH_TYPEPROGRAM_DOUBLEWORD 0x03U /*!<Program a double word (64-bit) at a specified address*/

#define FLASH_FLAG_BSY FLASH_SR_BSY         /*!< FLASH Busy flag                          */
#define FLASH_FLAG_PGERR FLASH_SR_PGERR     /*!< FLASH Programming error flag             */
#define FLASH_FLAG_WRPERR FLASH_SR_WRPRTERR /*!< FLASH Write protected error flag         */
#define FLASH_FLAG_EOP FLASH_SR_EOP         /*!< FLASH End of Operation flag              */

typedef enum
{
  HAL_OK = 0x00U,
  HAL_ERROR = 0x01U,
  HAL_BUSY = 0x02U,
  HAL_TIMEOUT = 0x03U
} HAL_StatusTypeDef;

typedef enum _FlashType_EN
{
  FLASH_PROGRAM_HALFWORD = 1U,
  FLASH_PROGRAM_WORD = 2U,
  FLASH_PROGRAM_DOUBLE_WORD = 3U,
} FlashType_EN;

HAL_StatusTypeDef HAL_FLASH_Unlock(void);

HAL_StatusTypeDef HAL_FLASH_Program(uint32_t TypeProgram, uint32_t Address, uint64_t Data);

HAL_StatusTypeDef HAL_FLASH_Lock(void);

#endif //__FLASH_H__
