#include "adc.h"

/*
PA0 -> ADC12_IN0
PA1 -> ADC12_IN1
PA2 -> ADC12_IN2
PA3 -> ADC12_IN3
PA4 -> ADC12_IN4
PA5 -> ADC12_IN5
PA6 -> ADC12_IN6
PA7 -> ADC12_IN7
PB0 -> ADC12_IN8
PB1 -> ADC12_IN9

*/

uint8_t adc_init(uint8_t adc, short port, short pin)
	{
	char channel;
	uint8_t result = 0;
	if(port == PortA)
	{
		if(pin < 8)
		{
			result = 1;
			channel = pin;
		}else if(pin >= 8){
			return result;
		}
	}
	else if (port == PortB)
	{
		if(pin<2)
		{
		result = 1;
		channel = 8 + pin;
		}else{
			return result;
		}
	}

	gpio_init(port,pin,IN,IN_ANA);
	if(adc == ADC_1)
	{
			RCC->APB2ENR |= (1 << 9);
			ADC1->CR2 = 0;
			ADC1->SQR3 = channel;
			ADC1->CR2 |= 1;
			delay_ms(100);
			ADC1->CR2 |= 1;
			ADC1->CR2 |= 2;

	}
	else if(adc == ADC_2)
	{
			RCC->APB2ENR |= (1 << 10);
			ADC2->CR2 = 0;
			ADC2->SQR3 = channel;
			ADC2->CR2 |= 1;
			delay_ms(100);
			ADC2->CR2 |= 1;
			ADC2->CR2 |= 2;
		
	}

	return result ;
}
uint8_t adc_check(uint8_t adc, short port, short pin){
	uint8_t check = 0;
	if(adc == ADC_1)

		{
			//	ADC1->CR2 |= 4;
				//while((ADC1 -> CR2 & (4)) == 1){}


			// ADC1->CR2 |= (1 << 2);
			if(ADC1->SR & 2)
			{
				check  = 1;
			}
		}
		else if(adc == ADC_2)
		{
			//ADC2->CR2 |= 4;
		
			//while((ADC2 -> CR2 & (4)) == 1){}
			// ADC2->CR2 |= (1 << 2);
			if(ADC2->SR & 2)
			{
				check  = 1;
			}
		}
	
	
	return check;
}
int adc_rx(uint8_t adc, short port, short pin){
	int data = 0;
	if(adc == ADC_1)
	{
		data = ADC1->DR;
	} 
	else if(adc == ADC_2)
	{
		data = ADC2->DR;
	}
	
	return data;
	
}
