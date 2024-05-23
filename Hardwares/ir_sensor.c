#include "ir_sensor.h"

#define IR1_SENSOR_GPIO_PIN     (1 << 3)  // PIN A3
#define IR2_SENSOR_GPIO_PIN     (1 << 4)  // PIN A4

void ir_sensors_init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    GPIOA->CRL &= ~(GPIO_CRL_MODE3 | GPIO_CRL_CNF3); 
    GPIOA->CRL |= GPIO_CRL_CNF3_1; 

    GPIOA->CRL &= ~(GPIO_CRL_MODE4 | GPIO_CRL_CNF4); 
    GPIOA->CRL |= GPIO_CRL_CNF4_1; 
}

uint8_t ir1_sensor_read(void)
{
    return (GPIOA->IDR & IR1_SENSOR_GPIO_PIN) ? 1 : 0; 
}

uint8_t ir2_sensor_read(void)
{
    return (GPIOA->IDR & IR2_SENSOR_GPIO_PIN) ? 1 : 0; 
}
