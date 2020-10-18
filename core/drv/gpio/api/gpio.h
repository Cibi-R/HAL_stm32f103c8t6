#ifndef __GPIO_H__
#define __GPIO_H__

/*****************************************************************************************************************************
 *                                                    GPIO Info STM32F103C8T6
 * ***************************************************************************************************************************
 * 48 Pin Package
 * --------------
 * 
 * PORTA + P0 - P15     +  GPIO                                   +     16
 * PORTB + P0 - P15     +  GPIO                                   +     16 (PB2 will be mapped as a BOOT1 pin)
 * PORTC + PC13 - PC15  +  GPIO                                   +     03
 * PORTD + PD0 - PD1    +  RCC_OSC_IN, RCC_OSC_OUT Respectively   +     02
 * 
 * Pin numbering starts from 1
 * 
 * Pin 1  + VBAT                                                  +     01
 * Pin 8  + VSSA                                                  +     01                                               
 * Pin 9  + VDDA                                                  +     01
 * Pin 23 + VSS                                                   +     01 
 * Pin 24 + VDD                                                   +     01
 * Pin 35 + VSS                                                   +     01
 * Pin 36 + VDD                                                   +     01
 * Pin 47 + VSS                                                   +     01
 * Pin 48 + VDD                                                   +     01
 * 
 * NRST (Reset)                                                   +     01
 * BOOT0                                                          +     01
 *                                                            --------------------
 *                                                                      48
 *****************************************************************************************************************************/


/******************************************************************************************************************************
 *												      Macro Definitions
 ******************************************************************************************************************************/

#define AFIOEN_CLOCK_ENABLE()  RCC->APB2ENR |= (1<<0)

#define PORTA_CLOCK_ENABLE()   RCC->APB2ENR |= (1<<2)
#define PORTB_CLOCK_ENABLE()   RCC->APB2ENR |= (1<<3)
#define PORTC_CLOCK_ENABLE()   RCC->APB2ENR |= (1<<4)
#define PORTD_CLOCK_ENABLE()   RCC->APB2ENR |= (1<<5)

#define IsClockEnabled_PortA() (RCC->APB2ENR & (1<<2))
#define IsClockEnabled_PortB() (RCC->APB2ENR & (1<<3))
#define IsClockEnabled_PortC() (RCC->APB2ENR & (1<<4))
#define IsClockEnabled_PortD() (RCC->APB2ENR & (1<<5))

/*< STM32 Device Ports */

#define DEVICE_PORT_A            ((uint8_t) 0X00)
#define DEVICE_PORT_B            ((uint8_t) 0X01)
#define DEVICE_PORT_C            ((uint8_t) 0X02)
#define DEVICE_PORT_D            ((uint8_t) 0X03)  /*< If external oscillator is used, this pin conf should be locked*/

/*< STM32 Device Pins */
/*< Available pins count could vary for port c,d. please refer "GPIO Info STM32F103C8T6" section of header file */

#define DEVICE_PORT_PIN_01       ((uint8_t) 0X01)
#define DEVICE_PORT_PIN_02       ((uint8_t) 0X02)
#define DEVICE_PORT_PIN_03       ((uint8_t) 0X03)
#define DEVICE_PORT_PIN_04       ((uint8_t) 0X04)
#define DEVICE_PORT_PIN_05       ((uint8_t) 0X05)
#define DEVICE_PORT_PIN_06       ((uint8_t) 0X06)
#define DEVICE_PORT_PIN_07       ((uint8_t) 0X07)
#define DEVICE_PORT_PIN_08       ((uint8_t) 0X08)
#define DEVICE_PORT_PIN_09       ((uint8_t) 0X09)
#define DEVICE_PORT_PIN_10       ((uint8_t) 0X0A)
#define DEVICE_PORT_PIN_11       ((uint8_t) 0X0B)
#define DEVICE_PORT_PIN_12       ((uint8_t) 0X0C)
#define DEVICE_PORT_PIN_13       ((uint8_t) 0X0D)
#define DEVICE_PORT_PIN_14       ((uint8_t) 0X0E)
#define DEVICE_PORT_PIN_15       ((uint8_t) 0X0F)

/*< STM32 Device Pin Modes */

#define DEVICE_PIN_MODE_IN           ((uint8_t) 0X00)
#define DEVICE_PIN_MODE_OUT_10Mhz    ((uint8_t) 0X01)
#define DEVICE_PIN_MODE_OUT_02Mhz    ((uint8_t) 0X02)
#define DEVICE_PIN_MODE_OUT_50Mhz    ((uint8_t) 0X03)

/*< STM32 Device Configuration States */

#define DEVICE_PIN_CONFIG_FUNC_IN_ANALOG                   ((uint8_t) 0X00)
#define DEVICE_PIN_CONFIG_FUNC_IN_FLOAT                    ((uint8_t) 0X01)
#define DEVICE_PIN_CONFIG_FUNC_IN_PULL_UP_DOWN_EN          ((uint8_t) 0X02)
#define DEVICE_PIN_CONFIG_FUNC_OUT_PUSH_PULL               ((uint8_t) 0X00) 
#define DEVICE_PIN_CONFIG_FUNC_OUT_OPEN_DRAIN              ((uint8_t) 0X01)
#define DEVICE_PIN_CONFIG_FUNC_ALT_OUT_PUSH_PULL           ((uint8_t) 0X02)
#define DEVICE_PIN_CONFIG_FUNC_ALT_OUT_OPEN_DRAIN          ((uint8_t) 0X03)

/*< STM32 Device Configuration Error */

#define DEVICE_PIN_CONFIG_FAILED   ((uint8_t) 0XFF)

/******************************************************************************************************************************
 *												           Typedefs
 ******************************************************************************************************************************/

typedef struct GPIO_Params_Tag
{
    uint8_t GPIO_Port;          /*< Refer "STM32 Device Ports" macros for available ports */
    uint8_t GPIO_Pin;           /*< Refer "STM32 Device Pins" macros for available pins */
    uint8_t GPIO_Mode;          /*< Refer "STM32 Device Pin Modes" macros for available pin modes */
    uint8_t GPIO_Config_Func;   /*< Refer "STM32 Device Configuration States" macros for available configuration states*/
}GPIO_Params_T;


/******************************************************************************************************************************
 *												      Fucntion Declarations
 ******************************************************************************************************************************/
/**
 * @brief  : To Configure a pin mode
 * @param  : While holds the configuration info for that particular pin. Refer : GPIO_Params_Tag
 * @return : Configuration status, Boolean value
 */

extern uint8_t GPIO_SetConfig(GPIO_Params_T* Pin);

/**
 * @brief  : To Configure group of pins
 * @param  : Param[0] : GPIO_Params_T, Array of pin configuration values, Refer : GPIO_Params_Tag, Param[1] : uint8_t, Number of elements
 * @return : Configuration status, Boolean value
 */

extern uint8_t GPIO_Init(GPIO_Params_T pinConfigArr[], uint8_t numElements);

/**
 * @brief  : To read a pin's status
 * @param  : uint8_t[0] Port, uint8_t[1] Pin, Refer : STM32 Device Ports, STM32 Device Pins
 * @return : uint8_t, Pin current status
 */

extern uint8_t GPIO_Read(uint8_t port, uint8_t pin);

/**
 * @brief  : To set the output state of a particular pin
 * @param  : uint8_t[0] Port, uint8_t[1] Pin, Refer : STM32 Device Ports, STM32 Device Pins
 * @return : void.
 */

extern void GPIO_Write(uint8_t port, uint8_t pin, uint8_t out);

/**
 * @brief  : To toggle the status of a particular pin
 * @param  : uint8_t[0] Port, uint8_t[1] Pin, Refer : STM32 Device Ports, STM32 Device Pins
 * @return : void
 */

extern void GPIO_Toggle(uint8_t port, uint8_t pin);



#endif //__GPIO_H__
