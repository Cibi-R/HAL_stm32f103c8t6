#include <drv.h>


/******************************************************************************************************************************
 *												      Function Definitions
 ******************************************************************************************************************************/

/**
 * @brief  : Stub function to get the base address of a gpio port
 * @param  : param[0]-uint8_t, Refer : STM32 Device Ports. param[1]-GPIO_TypeDef, Refer device specific header file.
 * @return : uint8_t (Boolean)
 */

uint8_t GPIO_GetBase_Add(uint8_t port, GPIO_TypeDef** regBase)
{
    uint8_t retVal = True;

    if (port == DEVICE_PORT_A)
    {
        *regBase = GPIOA;
    }

    else if (port == DEVICE_PORT_B)
    {
        *regBase = GPIOB;
    }

    else if (port == DEVICE_PORT_C)
    {
        *regBase = GPIOC;
    }

    else if (port == DEVICE_PORT_D)
    {
        *regBase = GPIOD;
    }

    else
    {
        retVal  = False;
    }

    return retVal;
}

/**
 * @brief  : To Configure a pin mode, Refer gpio.h for more informatoin
 */

uint8_t GPIO_SetConfig(GPIO_Params_T* pinConfig)
{
    uint8_t retVal = False;

    GPIO_TypeDef* gpioBase;

    volatile uint32_t* gpioConfigReg;

    if (GPIO_GetBase_Add(pinConfig->GPIO_Port, &gpioBase))
    {
        if (DEVICE_PORT_PIN_08 > pinConfig->GPIO_Pin)
        {
            gpioConfigReg = &gpioBase->CRL;
        }
        else
        {
            gpioConfigReg = &gpioBase->CRH;
        }

        *gpioConfigReg &= (~((uint32_t)0x3 << (4 * (pinConfig->GPIO_Pin % 8))));  /*< Clear bits */
        *gpioConfigReg |= (((uint32_t)pinConfig->GPIO_Mode)  << (4 * (pinConfig->GPIO_Pin % 8)));

        *gpioConfigReg &= (~((uint32_t)0x3 << ((4 * (pinConfig->GPIO_Pin % 8)) + 2)));  /*< Clear bits */
        *gpioConfigReg |= (((uint32_t)pinConfig->GPIO_Config_Func) << ((4 * (pinConfig->GPIO_Pin % 8)) + 2));

         retVal = True;
    }

    return retVal;
}

/**
 * @brief  : To Configure group of pins, Refer gpio.h for more informatoin.
 */

uint8_t GPIO_Init(GPIO_Params_T* pinConfigArr, uint8_t numElements)
{
    uint8_t retVal = True;

    for (uint8_t i = 0; i < numElements; i++)
    {
        if (!GPIO_SetConfig(pinConfigArr + i))
        {
            /*< GPIO_Port value can be used to tell the status of the gpio configuration to caller
                If the GPIO_Mode value is read 0xFF after the initialization then that pin configuration is failed. */
            pinConfigArr[i].GPIO_Mode = DEVICE_PIN_CONFIG_FAILED;

            retVal = False;
        }
    }

    return retVal;
}

/**
 * @brief  : To read a pin's status, Refer gpio.h for more informatoin.
 */

uint8_t GPIO_Read(uint8_t port, uint8_t pin)
{
    uint8_t retPinState = False;

    GPIO_TypeDef* gpioBase;

    if (GPIO_GetBase_Add(port, &gpioBase))
    {
        retPinState = ((uint8_t)((gpioBase->IDR >> pin) & 0x00000001));
    }

    return retPinState;
}

/**
 * @brief  : To set the output state of a particular pin, Refer gpio.h for more informatoin.
 */
void GPIO_Write(uint8_t port, uint8_t pin, uint8_t out)
{
    GPIO_TypeDef* gpioBase;

    if (GPIO_GetBase_Add(port, &gpioBase))
    {
        if (out == True)
        {
            gpioBase->ODR |= (1 << pin);
        }

        else
        {
            gpioBase->ODR &= (~(1 << pin));
        }
    }
}

/**
 * @brief  : To toggle the state of a particular pin, Refer gpio.h for more information.
 */
void GPIO_Toggle(uint8_t port, uint8_t pin)
{
    GPIO_TypeDef* gpioBase;

    if (GPIO_GetBase_Add(port, &gpioBase))
    {
        gpioBase->ODR ^= ((uint32_t)1 << pin);
    }
}

/**
 * @brief  : To Enable interrrupt of a pin, Refer gpio.h for more information.
 */
uint8_t GPIO_Enable_Int(GPIO_Params_T pin)
{
    /*< To use external interrupt, the port must be configured in input mode. */
	return 0;
}


/**
 * @brief  : To disable interrupt of a pin, Refer gpio.h for more informatoin.
 */
uint8_t GPIO_Disable_Int(GPIO_Params_T pin)
{
	return 0;
}

/**
 * @brief : Initializes all the gpio port clocks
 */
void GPIO_Clock_Init(void)
{
	PORTA_CLOCK_ENABLE();
	PORTB_CLOCK_ENABLE();
	PORTC_CLOCK_ENABLE();
	PORTD_CLOCK_ENABLE();

	AFIOEN_CLOCK_ENABLE();
}
