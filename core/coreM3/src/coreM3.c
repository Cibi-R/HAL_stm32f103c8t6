#include <stdint.h>
#include "../api/coreM3.h"

volatile uint32_t jill = 1;

void CortexM3_Init(void)
{
	
	/*< Enable fault exceptions */
    NVIC_EnableIRQ(NonMaskableInt_IRQn);
	
	NVIC_EnableIRQ(MemoryManagement_IRQn);
	
	NVIC_EnableIRQ(BusFault_IRQn);
	
	NVIC_EnableIRQ(UsageFault_IRQn);
}

void NMI_Handler(void)
{
    volatile uint8_t i = 1;
    while (i)
    {
    }
}

void HardFault_Handler(void)
{
    volatile uint32_t jill = 1;
    while (jill)
    {
		jill = SCB->CFSR;
		
		jill = (0XFF & ((uint32_t)(jill >> 24)));
		
		jill = jill;
    }
}

void MemManage_Handler(void)
{
    volatile uint8_t i = 1;
    while (i)
    {
    }
}

void BusFault_Handler(void)
{
    volatile uint8_t i = 1;
    while (i)
    {
    }
}

void UsageFault_Handler(void)
{
    volatile uint8_t i = 1;
    while (i)
    {
    }
}
