#include "pwm.h"

/*
PA0 -> TIM2_CH1
PA1 -> TIM2_CH2
PA2 -> TIM2_CH3
PA3 -> TIM2_CH4

PA6 -> TIM3_CH1
PA7 -> TIM3_CH2
PB0 -> TIM3_CH3
PB1 -> TIM3_CH4

PA8 -> TIM1_CH1
PA9 -> TIM1_CH2
PA10 -> TIM1_CH3
PA11 -> TIM1_CH4

*/

int pwm_init(uint8_t TIM, uint8_t CHANNEL){
	
	
	int status = 0;
	int channel = 0;
	
	switch(TIM){
		case TIM_1: 
			RCC->APB2ENR |= (1 << 11) | (1 << 0) | (1 << 2) ;
			switch (CHANNEL){
				case CHANNEL_1:
					status = 1;
					channel = 1;
					gpio_init(PortA, 8, OUT_AF_PP ,OUT50);
					break;
				case CHANNEL_2:
					channel = 2;
					gpio_init(PortA, 9, OUT_AF_PP ,OUT50);
					status = 1;
					break;
				case CHANNEL_3:
					channel = 3;
					gpio_init(PortA, 10, OUT_AF_PP ,OUT50);
					status = 1;
					break;
				case CHANNEL_4:
					channel = 4;
					status = 1;
					gpio_init(PortA, 11, OUT_AF_PP ,OUT50);
					break;
				
			}
			if(status == 1){
				TIM1->PSC = PRESCALER
				TIM1->ARR = ARRD; 
				if(channel == 1){
						TIM1->CCER |= TIM_CCER_CC1E; 
						TIM1->CCMR1 |= (1 << 5) | (1 << 6); 


				}else if(channel == 2){
						TIM1->CCER |= TIM_CCER_CC2E;
						TIM1->CCMR1 |= (1 << 13) | (1 << 14); 
					

				}
				else if(channel == 3){
						TIM1->CCER |= TIM_CCER_CC3E;
						TIM1->CCMR2 |= (1 << 5) | (1 << 6); 
					

				}else if(channel == 4){
						TIM1->CCER |= TIM_CCER_CC4E;
						TIM1->CCMR2 |= (1 << 13) | (1 << 14); 
					

				}
				TIM1->CR1 |= TIM_CR1_CEN; // Enable TIM2
			}
		
			
			break;
			case TIM_2:
				RCC->APB2ENR |= (1 << 0) | (1 << 2);
				RCC->APB1ENR |= 0x1u;
				switch (CHANNEL){
					case CHANNEL_1:
						channel = 1;
						status = 1;
						gpio_init(PortA, 0, OUT_AF_PP ,OUT50);
						break;
					case CHANNEL_2:
						channel = 2;
						gpio_init(PortA, 1, OUT_AF_PP ,OUT50);
						status = 1;
						break;
					case CHANNEL_3:
						channel = 3;
						gpio_init(PortA, 2, OUT_AF_PP ,OUT50);
						status = 1;
						break;
					case CHANNEL_4:
						channel = 4;
						status = 1;
						gpio_init(PortA, 3, OUT_AF_PP ,OUT50);
						break;
				}
				if(status == 1){
					TIM2->PSC = PRESCALER
					TIM2->ARR = ARRD; 
					if(channel == 1){
						TIM2->CCER |= TIM_CCER_CC1E; 
						TIM2->CCMR1 |= (1 << 5) | (1 << 6); 


					}else if(channel == 2){
						TIM2->CCER |= TIM_CCER_CC2E;
						TIM2->CCMR1 |= (1 << 13) | (1 << 14); 
					

					}
					else if(channel == 3){
						TIM2->CCER |= TIM_CCER_CC3E;
						TIM2->CCMR2 |= (1 << 5) | (1 << 6); 
					

					}else if(channel == 4){
						TIM2->CCER |= TIM_CCER_CC4E;
						TIM2->CCMR2 |= (1 << 13) | (1 << 14); 
				
					}
					TIM2->CR1 |= TIM_CR1_CEN; // Enable TIM2
			}
				break;
		case  TIM_3:
				RCC->APB2ENR |= (1 << 0) | (1 << 2)  | (1 << 3);
				RCC->APB1ENR |= 0x2u;
				switch (CHANNEL){
					case CHANNEL_1:
						status = 1;
						channel = 1;
						gpio_init(PortA, 6, OUT_AF_PP ,OUT50);
						break;
					case CHANNEL_2:
						gpio_init(PortA, 7, OUT_AF_PP ,OUT50);
						status = 1;
						channel = 2;
						break;
					case CHANNEL_3:
						gpio_init(PortB, 0, OUT_AF_PP ,OUT50);
						status = 1;
						channel = 3;
						break;
					case CHANNEL_4:
						status = 1;
						channel = 4;
						gpio_init(PortB, 1, OUT_AF_PP ,OUT50);
						break;
				}
				if(status == 1){
					TIM3->PSC = PRESCALER
					TIM3->ARR = ARRD; 
					if(channel == 1){
						TIM3->CCER |= TIM_CCER_CC1E; 
						TIM3->CCMR1 |= (1 << 5) | (1 << 6); 


					}else if(channel == 2){
						TIM3->CCER |= TIM_CCER_CC2E;
						TIM3->CCMR1 |= (1 << 13) | (1 << 14); 
					

					}
					else if(channel == 3){
						TIM3->CCER |= TIM_CCER_CC3E;
						TIM3->CCMR2 |= (1 << 5) | (1 << 6); 
					

					}else if(channel == 4){
						TIM3->CCER |= TIM_CCER_CC4E;
						TIM3->CCMR2 |= (1 << 13) | (1 << 14); 
				
					}
					TIM3->CR1 |= TIM_CR1_CEN; // Enable TIM2
			}
	}		
	
	return status;
}

int set_duty(uint8_t TIM, uint8_t CHANNEL, uint16_t duty){

	int status = 0;
	switch(TIM){
			case TIM_1:
				switch (CHANNEL){
					case CHANNEL_1:
						status = 1;
						TIM1->CCR1 = duty;
						break;
					case CHANNEL_2:
						status = 1;
						TIM1->CCR2 = duty;
						break;
					case CHANNEL_3:
						status = 1;

						TIM1->CCR3 = duty;
						break;
					case CHANNEL_4:
						status = 1;

						TIM1->CCR4 = duty;
						break;
				}
				
			break;
			case TIM_2:
				switch (CHANNEL){
					case CHANNEL_1:
						status = 1;

						TIM2->CCR1 = duty;
						break;
					case CHANNEL_2:
						status = 1;

						TIM2->CCR2 = duty;
						break;
					case CHANNEL_3:
						status = 1;

						TIM2->CCR3 = duty;
						break;
					case CHANNEL_4:					
						status = 1;

						TIM2->CCR4 = duty;
						break;
				}
				
				break;
			case  TIM_3:
				switch (CHANNEL){
					case CHANNEL_1:
						status = 1;

						TIM3->CCR1 = duty;
						break;
					case CHANNEL_2:
						status = 1;

						TIM3->CCR2 = duty;
						break;
					case CHANNEL_3:
						status = 1;

						TIM3->CCR3 = duty;
						break;
					case CHANNEL_4:
						status = 1;

						TIM3->CCR4 = duty;
						break;
				}
				
				break;
				
	}		
	return status;
	
	
	
}