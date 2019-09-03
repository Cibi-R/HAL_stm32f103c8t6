#include <includes.h>
#include GPIO_H
#include UART_APP_H

void Delay()
{
	unsigned char i;
	
	for (i=0; i<10; i++)
	{
		
	}
}

int main(void)
{
    PORTA_CLOCK_ENABLE();
    PORTB_CLOCK_ENABLE();
    PORTC_CLOCK_ENABLE();
    PORTD_CLOCK_ENABLE();

    AFIOEN_CLOCK_ENABLE();

	Delay();
	
    UART_Init();
	
    while (1);
}
