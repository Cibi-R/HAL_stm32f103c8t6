#ifndef __FLASH_H__
#define __FLASH_H__

/******************************************************************************************************************************
 *												                         Function Declaration
 ******************************************************************************************************************************/

/*< Flash key values. */
  
#define FLASH_UNLOCK_KEY1 0x45670123UL
#define FLASH_UNLOCK_KEY2 0xCDEF89ABUL


/******************************************************************************************************************************
 *												                        Function Declaration
 ******************************************************************************************************************************/

/*< Flash Program type */

typedef enum _FlashType_EN
{
  FLASH_PROGRAM_HALFWORD = 1U,
  FLASH_PROGRAM_WORD = 2U,
  FLASH_PROGRAM_DOUBLE_WORD = 3U,
} FlashType_EN;


/******************************************************************************************************************************
 *												                        Function Declaration
 ******************************************************************************************************************************/

/*
 * @brief  : To unlock the flash program and erase controller module. 
 * @para   : void
 * @return : HAL_Status (Status of unlock operation)
 */

extern HAL_Status FLASH_Unlock(void);


/*
 * @brief  : To lock the flash program and erase controller module.
 * @para   : void
 * @return : HAL_Status (Status of lock operation)
 */

extern HAL_Status FLASH_Lock(void);


/*
 * @brief  : To write flash memory
 * @para   : FlashType_EN - To Set the programming type, Address - Base address of the value to be written, Data - Data to be written.
 * @return : HAL_Status (Status of the write operation)
 */

extern HAL_Status FLASH_Program(FlashType_EN ProgramType, uint32_t Address, uint64_t Data);


/*
 * @brief  : To Erase the Flash memory.
 * @para   : 
 * @return : 
 */

extern HAL_Status FLASH_Erase(void);

#endif //__FLASH_H__
