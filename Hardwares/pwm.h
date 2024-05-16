#ifndef PWM_H
#define PWM_H


#include "stm32f10x.h"
#include "gpio.h"

#define PRESCALER SystemCoreClock / 1000000 - 1; 
#define ARRD 20000 - 1

#define TIM_1 0
#define TIM_2 1
#define TIM_3 2

#define CHANNEL_1 0
#define CHANNEL_2 1
#define CHANNEL_3 2
#define CHANNEL_4 3

int pwm_init(uint8_t TIM, uint8_t CHANNEL);

int set_duty(uint8_t TIM, uint8_t CHANNEL, uint16_t duty);


#endif