#include <platform.h>


/******************************************************************************************************************************
 *												      Function Definitions
 ******************************************************************************************************************************/

/**
 * @brief  : Stub function to get the base address of the gpio port
 * @param  : param[0] : uint8_t, port value. param[1] : GPIO_TypeDef, structure definition of GPIO Peripheral base addresses
 * @return : uint8_t
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

uint8_t GPIO_Init(GPIO_Params_T pinConfigArr[], uint8_t numElements)
{
    uint8_t retVal = True;

    for (uint8_t i = 0; i < numElements; i++)
    {
        if (!GPIO_SetConfig(&pinConfigArr[i]))
        {
            /*< GPIO_Port value can be used to tell the status of the gpio configuration to caller 
                If the GPIO_Port value is read 0xFF after the initialization then that pin configuration is failed. */
            pinConfigArr[i].GPIO_Port = DEVICE_PIN_CONFIG_FAILED;

            retVal = False;
        }
    }

    return retVal;
}

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

void GPIO_Toggle(uint8_t port, uint8_t pin)
{
    GPIO_TypeDef* gpioBase;

    if (GPIO_GetBase_Add(port, &gpioBase))
    {
        gpioBase->ODR ^= ((uint32_t)1 << pin);
    }
}
