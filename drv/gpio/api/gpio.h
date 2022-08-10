#ifndef __GPIO_H__
#define __GPIO_H__

/*****************************************************************************************************************************
 *                                                    GPIO Info STM32F103C8T6
 * ***************************************************************************************************************************
 * 48 Pin Package
 * --------------
 *
 * PORTA + P0 - P15                                               +     16
 * PORTB + P0 - P15                                               +     16 (PB2 will be mapped as a BOOT1 pin)
 * PORTC + PC13 - PC15                                            +     03
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
 *												        Macro Definitions
 ******************************************************************************************************************************/

/**
 * @brief : Enable clock for alternate IO function
 **/

#define AFIOEN_CLOCK_ENABLE()  RCC->APB2ENR |= (1<<0)

/**
 * @brief : Enable clock for GPIO ports
 **/

#define PORTA_CLOCK_ENABLE()   RCC->APB2ENR |= ((uint32_t)(1<<2))
#define PORTB_CLOCK_ENABLE()   RCC->APB2ENR |= ((uint32_t)(1<<3))
#define PORTC_CLOCK_ENABLE()   RCC->APB2ENR |= ((uint32_t)(1<<4))
#define PORTD_CLOCK_ENABLE()   RCC->APB2ENR |= ((uint32_t)(1<<5))

/**
 * @brief : Disable clock for GPIO ports
 **/

#define PORTA_CLOCK_DISABLE()   RCC->APB2ENR &= (~((uint32_t)(1<<2)))
#define PORTB_CLOCK_DISABLE()   RCC->APB2ENR &= (~((uint32_t)(1<<3)))
#define PORTC_CLOCK_DISABLE()   RCC->APB2ENR &= (~((uint32_t)(1<<4)))
#define PORTD_CLOCK_DISABLE()   RCC->APB2ENR &= (~((uint32_t)(1<<5)))

/**
 * @brief : Macro to check whether the clock is enabled for particular port
 **/

#define IsClockEnabled_PortA() (RCC->APB2ENR & (1<<2))
#define IsClockEnabled_PortB() (RCC->APB2ENR & (1<<3))
#define IsClockEnabled_PortC() (RCC->APB2ENR & (1<<4))
#define IsClockEnabled_PortD() (RCC->APB2ENR & (1<<5))

/**
 * @brief : Available ports in stm32f103c8t6 device
 **/

#define DEVICE_PORT_A            ((uint8_t) 0X00)
#define DEVICE_PORT_B            ((uint8_t) 0X01)
#define DEVICE_PORT_C            ((uint8_t) 0X02)
#define DEVICE_PORT_D            ((uint8_t) 0X03)  /*< If external oscillator is used, this pin conf should be locked*/

/**
 * @brief : Available pins in stm32f103c8t6 device
 **/
/*< Available pins count may vary for port c,d. please refer "GPIO Info STM32F103C8T6" section of above */

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

/**
 * @brief : STM32 Deivce Pin Modes
 **/

#define DEVICE_PIN_MODE_IN           ((uint8_t) 0X00)
#define DEVICE_PIN_MODE_OUT_10Mhz    ((uint8_t) 0X01)
#define DEVICE_PIN_MODE_OUT_02Mhz    ((uint8_t) 0X02)
#define DEVICE_PIN_MODE_OUT_50Mhz    ((uint8_t) 0X03)

/**
 * @brief : STM32 Device Configuration States
 **/

#define DEVICE_PIN_CONFIG_FUNC_IN_ANALOG                   ((uint8_t) 0X00)
#define DEVICE_PIN_CONFIG_FUNC_IN_FLOAT                    ((uint8_t) 0X01)
#define DEVICE_PIN_CONFIG_FUNC_IN_PULL_UP_DOWN_EN          ((uint8_t) 0X02)
#define DEVICE_PIN_CONFIG_FUNC_OUT_PUSH_PULL               ((uint8_t) 0X00)
#define DEVICE_PIN_CONFIG_FUNC_OUT_OPEN_DRAIN              ((uint8_t) 0X01)
#define DEVICE_PIN_CONFIG_FUNC_ALT_OUT_PUSH_PULL           ((uint8_t) 0X02)
#define DEVICE_PIN_CONFIG_FUNC_ALT_OUT_OPEN_DRAIN          ((uint8_t) 0X03)

/**
 * @brief : STM32 Device Configuration Error
 **/

#define DEVICE_PIN_CONFIG_FAILED   ((uint8_t) 0XFF)

/******************************************************************************************************************************
 *												           Typedefs
 ******************************************************************************************************************************/

typedef void (*GPIO_ExtInt_Handler)(void);


typedef struct GPIO_Params_Tag
{
    uint8_t GPIO_Port;          /*< Refer "STM32 Device Ports" macros for available ports */
    uint8_t GPIO_Pin;           /*< Refer "STM32 Device Pins" macros for available pins */
    uint8_t GPIO_Mode;          /*< Refer "STM32 Deivce Pin Modes" macros for available pin modes */
    uint8_t GPIO_Config_Func;   /*< Refer "STM32 Device Configuration States" macros for available configuration states*/
    uint8_t GPIO_Int;           /*< Boolean value, If this member is set to 1 (Enable/True) then GPIO_Mode, GPIO_Config_Func
                                    values will be discarded and will be configured for ext interrupt*/
    GPIO_ExtInt_Handler  GPIO_Callback;  /*< Callback function for GPIO external interrupt */
}GPIO_Params_T;


/******************************************************************************************************************************
 *												      Function declarations
 ******************************************************************************************************************************/
/**
 * @brief  : To configure a pin mode
 * @param  : It holds the configuration info for that particular pin. Refer : GPIO_Params_Tag
 * @return : uint8_t (boolean), Configuration status
 */

extern uint8_t GPIO_SetConfig(GPIO_Params_T* Pin);

/**
 * @brief  : To configure group of pins
 * @param  : Param[0]-GPIO_Params_T, pointer to an array of configuration values, Refer : GPIO_Params_Tag. Param[1] : uint8_t, Number of elements
 * @return : uint8_t (boolean), Configuration status
 */

extern uint8_t GPIO_Init(GPIO_Params_T* pinConfigArr, uint8_t numElements);

/**
 * @brief  : To read a pin's status
 * @param  : param[0]-uint8_t, Refer : STM32 Device Ports. param[1]-uint8_t, Refer : STM32 Device Pins macro
 * @return : uint8_t, Pin current status
 */

extern uint8_t GPIO_Read(uint8_t port, uint8_t pin);

/**
 * @brief  : To set the output state of a particular pin
 * @param  : param[0]-uint8_t, Refer : STM32 Device Ports. param[1]-uint8_t, Refer : STM32 Device Pins macro.
			 param[3]-uint8_t state of that pin (Possible values are True/False, Enable/Disable, 0/1)
 * @return : void.
 */

extern void GPIO_Write(uint8_t port, uint8_t pin, uint8_t out);

/**
 * @brief  : To toggle the state of a particular pin
 * @param  : param[0]-uint8_t, Refer : STM32 Device Ports. param[1]-uint8_t, Refer : STM32 Device Pins macro.
 * @return : void
 */

extern void GPIO_Toggle(uint8_t port, uint8_t pin);

/**
 * @brief  : To enable the external intrrupt of a pin
 * @param  : param[0]-GPIO_Params_T.Pin configuration values, Refer : GPIO_Params_Tag.
 * @return : uint8_t (Boolean), Configuration status
 */

extern uint8_t GPIO_Enable_Int(GPIO_Params_T pin);

/**
 * @brief  : To disable the external interrupt of a pin
 * @param  : param[0]-GPIO_Params_T.Pin configuration values, Refer : GPIO_Params_Tag.
 * @return : uint8_t (Boolean), Configuration status
 */

extern uint8_t GPIO_Disable_Int(GPIO_Params_T pin);

/**
 * @brief  : To initialize clock for all gpio ports
 * @param  : void
 * @return : void
 */

extern void GPIO_Clock_Init(void);

#endif //__GPIO_H__
