#ifndef  __SYSTEM_H__
#define  __SYSTEM_H__

/******************************************************************************************************************************
 *												      Macro Definitions
 ******************************************************************************************************************************/

/*< Primary and Secondary System clocks */
#define SYSTEM_CLOCK_HSE_RESONATOR    ((uint8_t)0XA1)
#define SYSTEM_CLOCK_HSE_CLOCK        ((uint8_t)0XA2)
#define SYSTEM_CLOCK_HSI              ((uint8_t)0XA3)
#define SYSTEM_CLOCK_PLL_HSI          ((uint8_t)0XA4) /*< HSI is the source of the PLL */
#define SYSTEM_CLOCK_PLL_HSE          ((uint8_t)0XA5) /*< HSE is the source of the PLL */


/*< System Clocks */
#define SYSTEM_CLOCK_HSI_8MHZ   ((uint64_t) 8000000)
#define SYSTEM_CLOCK_HSE        ((uint64_t) 8000000)
#define SYSTEM_CLOCK_24MHZ      ((uint64_t) 24000000)
#define SYSTEM_CLOCK_36MHZ      ((uint64_t) 36000000)
#define SYSTEM_CLOCK_48MHZ      ((uint64_t) 48000000)
#define SYSTEM_CLOCK_56MHZ      ((uint64_t) 56000000)
#define SYSTEM_CLOCK_60MHZ      ((uint64_t) 60000000)
#define SYSTEM_CLOCK_72MHZ      ((uint64_t) 72000000)

/*< System Clock to be Set, RTOS Application will be running at the below specified system frequency */
#define SYSTEM_CLOCK_SET  SYSTEM_CLOCK_48MHZ

/*!< Vector Table base offset field. This value must be a multiple of 0x200. */
#define VECT_TAB_OFFSET  0x0


#endif //__SYSTEM_H__
