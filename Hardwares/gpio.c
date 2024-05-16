#include "gpio.h"


void gpio_init(unsigned short PORT, unsigned short PIN, unsigned short CNF, unsigned short MODE){
	if(PORT == PortA){
		RCC->APB2ENR = (1 << 2); // enable GPIOB
		if(PIN < 8){
			GPIOA->CRL |= (MODE) << (PIN * 4);
			GPIOA->CRL |=  (CNF) << (PIN * 4 + 2);
		}
		else{
			GPIOA->CRH |= (MODE) << ((PIN - 8)* 4);
			GPIOA->CRH |=  (CNF) << ((PIN - 8) * 4 + 2);	
		}
		
	}
	else if(PORT == PortB){
		RCC->APB2ENR = (1 << 3); // enable GPIOB
		if(PIN < 8 ){
			GPIOB->CRL |= (MODE) << (PIN * 4);
			GPIOB->CRL |=  (CNF) << (PIN * 4 + 2);
		}
		else{
			GPIOB->CRH |= (MODE) << ((PIN-8)* 4);
			GPIOB->CRH |=  (CNF) << ((PIN-8) * 4 + 2);	
		}
	}
		
	
}

void gpio_write(unsigned short PORT, unsigned short PIN, unsigned short PinState){
		if(PORT == PortA){
			if (PinState != GPIO_PIN_RESET)
			{
				GPIOA->BSRR = PIN;

			}
			else
			{
				GPIOA->BSRR = (uint32_t)PIN << 16u;
			}
		}else if(PORT == PortB){
			if (PinState != GPIO_PIN_RESET)
			{
				GPIOB->BSRR = PIN;

			}
			else
			{
				GPIOB->BSRR = (uint32_t)PIN << 16u;
			}
		}
	
	
}

uint8_t gpio_read(unsigned short PORT, unsigned short PIN){
	uint8_t result;
	if(PORT == PortA){
		if ((GPIOA->IDR & PIN) != (uint32_t)GPIO_PIN_RESET)
		{
			result = GPIO_PIN_SET;
	 }
	  else
	 {
		 result = GPIO_PIN_RESET;
	 }
	}else if(PORT == PortB){
		if ((GPIOB->IDR & PIN) != (uint32_t)GPIO_PIN_RESET)
		{
			result = GPIO_PIN_SET;
	 }
	  else
	 {
		 result = GPIO_PIN_RESET;
	 }
	}
	
	 return result;
}


