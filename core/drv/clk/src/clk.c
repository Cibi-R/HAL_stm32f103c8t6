#include <drv.h>
#include <system.h>

/******************************************************************************************************************************
 *												      Typedefs
 ******************************************************************************************************************************/
typedef struct ClockParams_Tag
{
    uint32_t PLL_PreDiv;
    uint32_t PLL_Multiplier;
    uint32_t AHB_Prescalar;
    uint32_t APB1_Prescalar;
    uint32_t APB2_Prescalar;
} ClockParams_T;

/******************************************************************************************************************************
 *												    Global Variable
 ******************************************************************************************************************************/

/**
 * SystemClock_Global will hold the clock configuration of the system, which is in effect.
 */
System_Primary_Clk_T SystemClock_Global = {SYSTEM_CLOCK_HSI, Off, 8U};  /*< Internal RC Oscillator 8Mhz */


void System_Clk_Params_Init(uint64_t SystemClock, ClockParams_T *ClockParams)
{
    switch (SystemClock)
    {
        case SYSTEM_CLOCK_HSI_8MHZ:
        {
            break;
        }
		
		#if 0
        case SYSTEM_CLOCK_HSE:
        {
            break;
        }
		#endif

        case SYSTEM_CLOCK_24MHZ:
        {
			/*< Only two values available for PLL_PreDiv, if HSE is not divided, if set to RCC_CFGR_PLLXTPRE_HSE_Div2
			    HSE will divided by 2. Refer SYSTEM_CLOCK_60MHZ where we have divided HSE by 2 */
			ClockParams->PLL_PreDiv     = 0U;                 
            ClockParams->PLL_Multiplier = RCC_CFGR_PLLMULL3;
            ClockParams->AHB_Prescalar  = RCC_CFGR_HPRE_DIV1;
            ClockParams->APB1_Prescalar = RCC_CFGR_PPRE1_DIV1;
            ClockParams->APB2_Prescalar = RCC_CFGR_PPRE2_DIV1;
            break;
        }

        case SYSTEM_CLOCK_36MHZ:
        {
			ClockParams->PLL_PreDiv     = 0U;                 
            ClockParams->PLL_Multiplier = RCC_CFGR_PLLMULL9;
            ClockParams->AHB_Prescalar  = RCC_CFGR_HPRE_DIV2;
            ClockParams->APB1_Prescalar = RCC_CFGR_PPRE1_DIV1;
            ClockParams->APB2_Prescalar = RCC_CFGR_PPRE2_DIV1;
            break;
        }

        case SYSTEM_CLOCK_48MHZ:
        {
			ClockParams->PLL_PreDiv     = 0U;                 
            ClockParams->PLL_Multiplier = RCC_CFGR_PLLMULL6;
            ClockParams->AHB_Prescalar  = RCC_CFGR_HPRE_DIV1;
            ClockParams->APB1_Prescalar = RCC_CFGR_PPRE1_DIV2;
            ClockParams->APB2_Prescalar = RCC_CFGR_PPRE2_DIV2;
            break;
        }

        case SYSTEM_CLOCK_56MHZ:
        {
			ClockParams->PLL_PreDiv     = 0U;                 
            ClockParams->PLL_Multiplier = RCC_CFGR_PLLMULL7;
            ClockParams->AHB_Prescalar  = RCC_CFGR_HPRE_DIV1;
            ClockParams->APB1_Prescalar = RCC_CFGR_PPRE1_DIV2;
            ClockParams->APB2_Prescalar = RCC_CFGR_PPRE2_DIV2;
            break;
        }

        case SYSTEM_CLOCK_60MHZ:
        {
            ClockParams->PLL_PreDiv     = RCC_CFGR_PLLXTPRE_HSE_Div2;                 
            ClockParams->PLL_Multiplier = RCC_CFGR_PLLMULL15;
            ClockParams->AHB_Prescalar  = RCC_CFGR_HPRE_DIV1;
            ClockParams->APB1_Prescalar = RCC_CFGR_PPRE1_DIV2;
            ClockParams->APB2_Prescalar = RCC_CFGR_PPRE1_DIV2;
            break;
        }

        case SYSTEM_CLOCK_72MHZ:
        {
			ClockParams->PLL_PreDiv     = 0U;                 
            ClockParams->PLL_Multiplier = RCC_CFGR_PLLMULL9;
            ClockParams->AHB_Prescalar  = RCC_CFGR_HPRE_DIV1;
            ClockParams->APB1_Prescalar = RCC_CFGR_PPRE1_DIV2;
            ClockParams->APB2_Prescalar = RCC_CFGR_PPRE1_DIV2;
            break;
        }
	}
}

void System_Flash_Init(void)
{
    /* Enable Prefetch Buffer, should be enabled when the system clock is lower than 24Mhz */
    FLASH->ACR |= FLASH_ACR_PRFTBE;

    /* Flash 2 wait state */
    FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
    FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2; 
}

void System_Flash_Vector_Init(void)
{
	/* Vector Table Relocation in Internal FLASH. */
    SCB->VTOR = FLASH_BASE | VECT_TAB_OFFSET;
}

uint8_t System_Clock_Init(ClockParams_T* ClockParams)
{
    uint8_t retVal = False;

    volatile uint32_t timeout = HSE_STARTUP_TIMEOUT;

    /* Enable HSE */
    RCC->CR |= ((uint32_t)RCC_CR_HSEON);

    while ( (!(RCC->CR & RCC_CR_HSERDY)) && (timeout))
    {
        timeout--; /*< If the timeout value is equal to zero then the clock frequency is not set and ready. */
    }

    if (RCC->CR & RCC_CR_HSERDY)
    {
        System_Flash_Init();

        /* HCLK = SYSCLK */
        RCC->CFGR |= ClockParams->AHB_Prescalar;
      
        /* PCLK1 = HCLK */
        RCC->CFGR |= ClockParams->APB1_Prescalar;
    
        /* PCLK2 = HCLK */
        RCC->CFGR |= ClockParams->APB2_Prescalar;

        /* PLL configuration: PLLCLK = HSE * ClockParams->PLL_Multiplier =  SYSTEM_CLOCK_SET */
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL));
        RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | ClockParams->PLL_Multiplier | ClockParams->PLL_PreDiv);

        /* Enable PLL */
        RCC->CR |= RCC_CR_PLLON;

        /* Wait till PLL is ready */
        timeout = 0X00FFFFFFU;
        while( ((RCC->CR & RCC_CR_PLLRDY) == 0) && (timeout) )
        {
            timeout--;
        }

        if (RCC->CR & RCC_CR_PLLRDY)
        {
            /* Select PLL as system clock source */
            RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
            RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;    

            /* Wait till PLL is used as system clock source */
            timeout = 0X00FFFFFFU;
            while ( ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x08) && (timeout) )
            {
                timeout--;
            }

            if ( (RCC->CFGR & (uint32_t)RCC_CFGR_SWS_PLL) == RCC_CFGR_SWS_PLL ) 
            {
                retVal = True;
            }
        }
        else
        {
            /*< PLL Ready failed. */
            retVal = False;
        }
        
    }

    else
    {
        /*< HSE not ready */
        retVal = False;
    } 

    return retVal;
}

void System_Init(void)
{
    /* clockparams initializes the prescalar values for the desired system clock. */
    ClockParams_T ClockParams; 

    /* Reset the RCC clock configuration to the default reset state(for debug purpose) */
    /* Set HSION bit */
    RCC->CR |= (uint32_t)0x00000001;

    /* Reset SW, HPRE, PPRE1, PPRE2, ADCPRE and MCO bits */
    RCC->CFGR &= (uint32_t)0xF8FF0000;

    /* Reset HSEON, CSSON and PLLON bits */
    RCC->CR &= (uint32_t)0xFEF6FFFF;

    /* Reset HSEBYP bit */
    RCC->CR &= (uint32_t)0xFFFBFFFF;

    /* Reset PLLSRC, PLLXTPRE, PLLMUL and USBPRE/OTGFSPRE bits */
    RCC->CFGR &= (uint32_t)0xFF80FFFF;

    /* Disable all interrupts and clear pending bits  */
    RCC->CIR = 0x009F0000;

    /* Get the params for system clock frequency */
    System_Clk_Params_Init(SYSTEM_CLOCK_SET, &ClockParams);

    /* Configure the System clock frequency, HCLK, PCLK2 and PCLK1 prescalers */
    if (System_Clock_Init(&ClockParams))
	{
		SystemClock_Global.PLL_Enabled  = True;
		SystemClock_Global.PrimaryClock = SYSTEM_CLOCK_PLL_HSE;
		SystemClock_Global.SysClock     = (uint8_t) (SYSTEM_CLOCK_SET / ((uint16_t) 1000000));
	}
	
	System_Flash_Vector_Init();
}
