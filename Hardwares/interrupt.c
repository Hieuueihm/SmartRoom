#include "interrupt.h"


void intr_init(){
	
	RCC->APB2ENR |= (1 << 0);
	__disable_irq();
	AFIO->EXTICR[0] |= 0x0000;
	AFIO->EXTICR[1] |= 0x0000;
	AFIO->EXTICR[2] |= 0x11;

	
	EXTI->IMR &= ~(0b1100011000);
	EXTI->IMR |= 0b1100011000;
	EXTI->FTSR |= 0b1100011000;
	EXTI->RTSR &= (~0b1100011000);



	NVIC_SetPriority(EXTI3_IRQn, 2);
	NVIC_SetPriority(EXTI4_IRQn, 2);
	NVIC_SetPriority(EXTI9_5_IRQn, 1);
	NVIC_EnableIRQ(EXTI9_5_IRQn);
	NVIC_EnableIRQ(EXTI3_IRQn);

	NVIC_EnableIRQ(EXTI4_IRQn);
	

	__enable_irq();

	

	
	
}