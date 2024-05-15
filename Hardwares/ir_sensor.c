#include "ir_sensor.h"

#define IR_SENSOR_GPIO_PIN     (1 << 3)  //PIN A3

void ir_sensor_init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    GPIOA->CRL &= ~(GPIO_CRL_MODE3 | GPIO_CRL_CNF3);  //PIN A3
    GPIOA->CRL |= GPIO_CRL_CNF3_1; 
}

uint8_t ir_sensor_read(void)
{
    return (GPIOA->IDR & IR_SENSOR_GPIO_PIN) ? 1 : 0;
}
