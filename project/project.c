#include <includes.h>
#include GPIO_H
#include UART_APP_H


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
