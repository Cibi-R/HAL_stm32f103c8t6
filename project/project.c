#include <includes.h>
#include GPIO_H
#include UART_APP_H


void Blink_Led(void);
void Delay(void);

int main(void)
{
    PORTA_CLOCK_ENABLE();
    PORTB_CLOCK_ENABLE();
    PORTC_CLOCK_ENABLE();
    PORTD_CLOCK_ENABLE();

    AFIOEN_CLOCK_ENABLE();
	
    UART_Init();
	
    while (1);
}

