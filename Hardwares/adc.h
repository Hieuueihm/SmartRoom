#ifndef ADC_H
#define ADC_H

#include "stm32f10x.h"
#include "gpio.h"
#include "systick.h"

#define ADC_1 1
#define ADC_2 2

uint8_t adc_init(uint8_t adc, short port, short pin);
uint8_t adc_check(uint8_t adc, short port, short pin);
int adc_rx(uint8_t adc, short port, short pin);




#endif