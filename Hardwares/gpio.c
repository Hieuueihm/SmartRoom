#include "gpio.h"


void gpio_init(unsigned short PORT, unsigned short PIN, unsigned short CNF, unsigned short MODE){
	if(PORT == PortA){
		RCC->APB2ENR = (1 << 2); // enable GPIOB
		if(PIN < 8){
			
			GPIOA->CRL &= ~(uint32_t)((0b1111) << (PIN) * 4); // clear 4 bit in config register


			GPIOA->CRL |= (MODE) << (PIN * 4);
			GPIOA->CRL |=  (CNF) << (PIN * 4 + 2);
		}
		else{
			GPIOA->CRH &= ~(uint32_t)((0xb1111) << ((PIN- 8)) * 4); // clear 4 bit in config register

			GPIOA->CRH |= (MODE) << ((PIN - 8)* 4);
			GPIOA->CRH |=  (CNF) << ((PIN - 8) * 4 + 2);	
		}
		
	}
	else if(PORT == PortB){
		RCC->APB2ENR = (1 << 3); // enable GPIOB
		if(PIN < 8 ){
			GPIOB->CRL &= ~(uint32_t)((0xF) << (PIN) * 4); // clear 4 bit in config register

			GPIOB->CRL |= (MODE) << (PIN * 4);
			GPIOB->CRL |=  (CNF) << (PIN * 4 + 2);
		}
		else{
			GPIOB->CRH &= ~(uint32_t)((0xF) << ((PIN-8)) * 4); // clear 4 bit in config register

			GPIOB->CRH |= (MODE) << ((PIN-8)* 4);
			GPIOB->CRH |=  (CNF) << ((PIN-8) * 4 + 2);	
		}
	}else if(PORT == PortC){
		RCC->APB2ENR = (1 << 4); // enable GPIOB
		if(PIN < 8 ){
			GPIOC->CRL &= ~(uint32_t)((0xF) << (PIN * 4) *4); // clear 4 bit in config register

			GPIOC->CRL |= (MODE) << (PIN * 4);
			GPIOC->CRL |=  (CNF) << (PIN * 4 + 2);
		}
		else{
			GPIOC->CRH &= ~(uint32_t)((0xF) << ((PIN-8)) * 4); // clear 4 bit in config register

			GPIOC->CRH |= (MODE) << ((PIN-8)* 4);
			GPIOC->CRH |=  (CNF) << ((PIN-8) * 4 + 2);	
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
		else if(PORT == PortC){
			if (PinState != GPIO_PIN_RESET)
			{
				GPIOC->BSRR = PIN;

			}
			else
			{
				GPIOC->BSRR = (uint32_t)PIN << 16u;
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
	else if(PORT == PortC){
		if ((GPIOC->IDR & PIN) != (uint32_t)GPIO_PIN_RESET)
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


