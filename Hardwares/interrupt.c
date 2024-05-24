#include "interrupt.h"


void intr_init(){
	// enable intr cho chân ir // a3 a4
	// 2 chân pb2, pb1
	
	RCC->APB2ENR |= (1 << 0);
	//a3 a4 // b4 b5
	AFIO->EXTICR[0] |= 0x0000;
	AFIO->EXTICR[1] |= 0x0000;
	AFIO->EXTICR[2] |= (1 << 0) | (1 << 4);


	EXTI->IMR |= 0x318;
	EXTI->RTSR |= 0x318;
	EXTI->FTSR &= (~0x318);


	NVIC_SetPriority(EXTI3_IRQn, 2);

	NVIC_EnableIRQ(EXTI3_IRQn);
	NVIC_SetPriority(EXTI4_IRQn, 2);

	NVIC_EnableIRQ(EXTI4_IRQn);
	
		NVIC_SetPriority(EXTI9_5_IRQn, 1);

	NVIC_EnableIRQ(EXTI9_5_IRQn);

	

	
	
}