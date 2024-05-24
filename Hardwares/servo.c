#include "servo.h"

#define TIM2_PERIOD         20000 // Timer2 period (20ms)
#define SERVO_MIN_PULSE     500  // Minimum pulse width for 0 degrees (0,5ms)
#define SERVO_MAX_PULSE     2500  // Maximum pulse width for 180 degrees (2,5ms)

void servo_init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    GPIOA->CRL &= ~(GPIO_CRL_MODE1 | GPIO_CRL_CNF1); //PIN A1
    GPIOA->CRL |= GPIO_CRL_MODE1_1 | GPIO_CRL_CNF1_1; 

    TIM2->PSC = SystemCoreClock / 1000000 - 1; 
    TIM2->ARR = TIM2_PERIOD - 1; 
    TIM2->CCMR1 |= TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2; // PWM mode 1
    TIM2->CCER |= TIM_CCER_CC2E; 
    TIM2->CR1 |= TIM_CR1_CEN; // Enable TIM2
}

void servo_rotate(uint16_t angle)
{
    uint16_t pulse_width;

    if(angle > 180)
        angle = 180;

    pulse_width = SERVO_MIN_PULSE + (SERVO_MAX_PULSE - SERVO_MIN_PULSE) * angle / 180;

    TIM2->CCR2 = pulse_width;
}