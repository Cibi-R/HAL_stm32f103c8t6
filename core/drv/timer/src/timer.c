#include <includes.h>
#include TIMER_H

void TIM2_IRQHandler(void)
{
	/* Clear pending interrupt */
	TIM2->SR &= 0XFFFE;

	/* Clear TIM2 Interrupt pending state*/
	NVIC->ICPR[0] |= (1 << 28);
}

void Timer_2_Interrupt_Init(void)
{
	/* Enable clock for Timer 2 */
	RCC->APB1ENR |= (1<<0);
	
	/* Enable interrupt on Update event */
	TIM2->DIER   |= (1<<0);
	
	/* Set Prescalar value to 59999 */
	TIM2->PSC = 59999;
	
	/* Set Auto Reload Register to 10 to generate interrupt for every 10ms */
	TIM2->ARR = 10;
	
	/* Enable TIM2 interrupt in Cortex M3*/
	NVIC->ISER[0] |= (1<<28);
	
	/* Enable Timer Counter */
	TIM2->CR1 |= (1<<0);
}
