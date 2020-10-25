#ifndef __FLASH_H__
#define __FLASH_H__

/*****************************************************************************************************************************
 *                                                    Flash Info STM32F103C8T6
 * ***************************************************************************************************************************
 * Flash Memory Size : 128Kb
 * Botton to top diagram:
 * 
 *                  0X00000000  +++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *                              +  Aliased to Flash or system memory depending on     +        
 *                              +  Boot pins. Size : 128Mb                            +
 *                  0X08000000  +++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *                              +  Flash memory region                                +
 *                              +  Size : 128Kb                                       +
 *                  0X0801FFFF  +++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *                              +  Reserved Space                                     +
 *                              +  Size : 383Mb                                       +
 *                  0X1FFFF000  +++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *                              +  System Memory                                      +
 *                              +  Size : 2Kb                                         +
 *                  0X1FFFF800  +++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
 *                              +  Option bytes                                       +
 *                              +  Size : 16 Bytes                                    +
 *                  0X1FFFF80F  +++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
 *                              +  Reserved Space                                     +
 *                              +  Size : 2032 Bytes                                  +
 *                  0X1FFFFFFF  +++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 *****************************************************************************************************************************/

/*****************************************************************************************************************************
 *                                                   SRAM Info STM32F103C8T6
 * ***************************************************************************************************************************
 * SRAM Size : 20Kb
 * Note : We can adjust the start and end of teh stack by modifying the MSP value and Stack size
 * Botton to top diagram:
 * 
 *                  0X20000000  +++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *                              +  STACK Memory is comprised of Stack and             +        
 *                              +  Heap Section                                       +
 *                  0X4FFF0000  +++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 *****************************************************************************************************************************/


/******************************************************************************************************************************
 *												          Macro Defintions
 ******************************************************************************************************************************/

/*< Flash Error Macros */  
#define FLASH_TIMEOUT_ERROR          ((uint8_t) 0X01)
#define FLASH_PROG_ERROR             ((uint8_t) 0x02)
#define FLASH_WRITE_PROT_ERROR       ((uint8_t) 0X04)
#define FLASH_UNLOCK_ERROR           ((uint8_t) 0X08)
#define FLASH_LOCK_ERROR             ((uint8_t) 0X10)
#define FLASH_WRITE_ERROR            ((uint8_t) 0X20)
#define FLASH_READ_ERROR             ((uint8_t) 0X40)

/*< Flash Read/Write status */
#define FLASH_OK                     ((uint8_t) 0X00)
#define FLASH_WRITE_OK               ((uint8_t) 0X03)
#define FALSH_READ_OK                ((uint8_t) 0X05)

/*< Flash timeout, should not be higher than 0XFFFF */
#define FLASH_TIMEOUT                ((uint16_t)0xFFFF)

/*< Flash unlock keys */
#define FLASH_UNLOCK_KEY1 0x45670123UL
#define FLASH_UNLOCK_KEY2 0xCDEF89ABUL


/******************************************************************************************************************************
 *												      Function Declaration
 ******************************************************************************************************************************/

/******************************************************************************************************************************
 *                                                    !!!   CAUTION    !!!
 * 	Memory addresses passed to the Flash write functions should not be unaligned addresses, unaligned addresses would result in
 *  Usage fault/ unprecise hard fault
 ******************************************************************************************************************************/

/**
 * @brief : This function will write 8 bits of data to the flash memory
 * @param : param[0]-uint32_t, flash memory address, should be multiple of 2. param[1]-uint8_t*, reference to data to be sent.
 * @return: status of the write operation, Refer Flash Error and status macros
 */
uint8_t Flash_Write_Bit8(uint32_t startAdd, uint8_t *data);

/**
 * @brief : This function will write 16 bits of data to flash memory
 * @param : param[0]-uint32_t, flash memory address, should be multiple of 2. param[1]-uint16_t*, reference to data to be sent. 
 * @return: status of the write operation, Refer Flash Error and status macros
 */
uint8_t Flash_Write_Bit16(uint32_t startAdd, uint16_t *data);

/**
 * @brief : This function will write 32 bits of data to flash memory
 * @param : param[0]-uint32_t, flash memory address, should be multiple of 2. param[1]-uint32_t*, reference to data to be sent.
 * @return: status of the write operation, Refer Flash Error and status macros
 */
uint8_t Flash_Write_Bit32(uint32_t startAdd, uint32_t *data);

/**
 * @brief : This function will write stream of data to flash memory
 * @param : param[0]-uint32_t, flash memory address, should be multiple of 2. param[1]-uint8_t*, reference to data to be sent,
 *          length of the byte stream
 * @return: status of the write operation, Refer Flash Error and status macros
 */
uint8_t Flash_Write_Stream(uint32_t startAdd, uint8_t *data, uint8_t length);

/**
 * @brief : This funciton will read 8 bits of data from flash memory
 * @param : param[0]-uint32_t, flash memory address, should be multiple of 2. param[1]-uint8_t*, reference of the variable
 *          where data will be stored.
 * @return: status of the read operation, Refer Flash Error and status macros
 */
uint8_t Flash_Read_Bit8(uint32_t startAdd, uint8_t* data);

/**
 * @brief : This funciton will read 16 bits of data from flash memory
 * @param : param[0]-uint32_t, flash memory address, should be multiple of 2. param[1]-uint16_t*, reference of the variable
 *          where data will be stored.
 * @return: status of the read operation, Refer Flash Error and status macros
 */
uint8_t Flash_Read_Bit16(uint32_t startAdd, uint16_t* data);

/**
 * @brief : This funciton will read 32 bits of data from flash memory
 * @param : param[0]-uint32_t, flash memory address, should be multiple of 2. param[1]-uint32_t*, reference of the variable
 *          where data will be stored.
 * @return: status of the read operation, Refer Flash Error and status macros
 */
uint8_t Flash_Read_Bit32(uint32_t startAdd, uint32_t* data);

/**
 * @brief : This funciton will read stream of bytes from flash memory
 * @param : param[0]-uint32_t, flash memory address, should be multiple of 2. param[1]-uint8_t*, reference to the data stream
 * @return: status of the read operation, Refer Flash Error and status macros
 */
uint8_t Flash_Read_Stream(uint32_t startAdd, uint8_t* stream, uint8_t length);

/**
 * @brief : This function will erase the page - 128 pages, TO BE IMPLEMENTED
 * @param : uint8_t - Page to be erased
 * @return: status of the write operation, Refer Flash Error and status macros
 */
uint8_t Flash_Erase_Page(uint8_t page);

/**
 * @brief : This function will erase the partition of the flash memory, TO BE IMPLEMENTED
 * @param : uint8_t - Parition to be cleared
 * @return: status of the write operation, Refer Flash Error and status macros
 */
uint8_t Flash_Erase_Parition(uint8_t partition);

/**
 * @brief : This function will perform the complete erase, TO BE IMPLEMENTED
 * @param : void
 * @return: status of the write operation, Refer Flash Error and status macros
 */
uint8_t Flash_Erase_All(void);


#endif //__FLASH_H__
