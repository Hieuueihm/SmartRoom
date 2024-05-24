#include "systick.h"

void systick_init(void)
{
	
	
	RCC->APB1ENR |= (1 << 2);
	    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

	TIM4->PSC = (SystemCoreClock / 1000000) - 1;
	
	TIM4->ARR = 0xFFFF;
	TIM4->CR1 |= (1 << 0);
	while(!(TIM4->SR & (1 << 0)));
	
  TIM1->PSC = (SystemCoreClock / 2000) - 1; // Prescaler to get 2 kHz time base
   TIM1->ARR = 500 - 1; // Auto-reload value for 1 second overflow
    TIM1->DIER |= TIM_DIER_UIE; // Enable update interrupt
    TIM1->CR1 |= TIM_CR1_CEN; // Enable TIM1

    // Enable TIM1 update interrupt in NVIC
    NVIC_EnableIRQ(TIM1_UP_IRQn);
	 

	
}


void delay_us(unsigned long t)
{
	TIM4->CNT = 0;
	while(TIM4->CNT < t);
}



void delay_ms(unsigned long t)
{
 for(int i = 0; i < t; i++){
	 delay_us(1000);
 }
}

