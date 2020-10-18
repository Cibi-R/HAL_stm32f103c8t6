#ifndef __CLK_H__
#define __CLK_H__

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************************************************************
 *												      Typedefs
 ******************************************************************************************************************************/

typedef enum System_Clk_State_Tag
{
    CLOCK_ON,
    CLOCK_OFF,
}System_Clk_State_T;

typedef struct System_Primary_Clk_Tag
{
    uint8_t PrimaryClock;          /*< This variable hold the  clock source which is used as system clock HSE, HSI, PLL */
    uint8_t PLL_Enabled;           /*< Hold the status of the PLL status */
    uint8_t SysClock;              /*< This variable will hold current system clock ex. for 6000000Mhz -> 60 -*/
}System_Primary_Clk_T;

/******************************************************************************************************************************
 *												 Function Declarations
 ******************************************************************************************************************************/

/**
 *  Brief   : To Configura the system clock and Flash memory region, Refer system.h to configure the system clock.
 *  Params  : void
 *  Return  : void 
 */

extern void System_Init(void);

#ifdef __cplusplus
}
#endif

#endif //__CLK_H__
