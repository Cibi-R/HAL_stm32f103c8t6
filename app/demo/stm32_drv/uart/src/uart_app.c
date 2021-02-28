#include <app.h>

void UART1_Test_App(void)
{
    /* UART-1 Pin Configuration. No remapping programmed for UART1. */
	GPIO_Params_T PA9;  // (Tx) 
	GPIO_Params_T PA10; // (Rx)
	
	/*< Variable used for UART initialization and handling */
	UART_Params_T UART_Params;
	UART_Handle_T *UART_Handle;
	
	char UART_String[] = "UART String\n\r";
	
	/* UART-1 */
	PA9.GPIO_Port = DEVICE_PORT_A;
	PA9.GPIO_Pin  = DEVICE_PORT_PIN_09;
	PA9.GPIO_Mode = DEVICE_PIN_MODE_OUT_50Mhz;
	PA9.GPIO_Config_Func = DEVICE_PIN_CONFIG_FUNC_ALT_OUT_PUSH_PULL;
	PA9.GPIO_Callback = NULL;

	PA10.GPIO_Port = DEVICE_PORT_A;
	PA10.GPIO_Pin  = DEVICE_PORT_PIN_10;
	PA10.GPIO_Mode = DEVICE_PIN_MODE_IN;
	PA10.GPIO_Config_Func = DEVICE_PIN_CONFIG_FUNC_IN_FLOAT;
	PA10.GPIO_Callback = NULL;
	
	/*< UART_Params handle will be initialized to a default values */
	UART_Params_Init(&UART_Params);
	
	/*< Initialize the UART_params to a desired values */
	UART_Params.uart_Channel       = DEVICE_UART_CHANNEL_1;
	UART_Params.uart_OperatingMode = DEVICE_UART_MODE_TX;
	UART_Params.uart_WordLength    = DEVICE_UART_WORD_LEN_8;
	UART_Params.uart_StopBits      = DEVICE_UART_STOP_BIT_1;
	UART_Params.uart_Parity        = DEVICE_UART_PARITY_NONE;
	UART_Params.uart_Baudrate      = DEVICE_UART_BR_9600;
	UART_Params.uart_TxCallBack    = NULL;
	UART_Params.uart_RxCallBack    = NULL;
	
	// UART_Open(UART_Handle);
	
	UART1_CLOCK_ENABLE();
	
	GPIO_SetConfig(&PA9);
	GPIO_SetConfig(&PA10);
	
	/*< Initialize UART with the configured values */
	UART_Handle = UART_SetConfig(&UART_Params);
	
	UART_TxString(UART_Handle, (uint8_t*)&UART_String[0], sizeof(UART_String));
	
	// UART_Close(UART_Handle);
}


