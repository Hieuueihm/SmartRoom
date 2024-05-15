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
