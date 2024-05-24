
#include "ir_sensor.h"

#define IR1_SENSOR_GPIO_PIN     (1 << 3)  // PIN A3
#define IR2_SENSOR_GPIO_PIN     (1 << 4)  // PIN A4

void ir_sensors_init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    gpio_init(PortA, 3, IN_PUSHPULL, IN);
    gpio_init(PortA, 4, IN_PUSHPULL, IN);
	
	GPIOA->ODR |= (1 << 3) | (1 << 4); // pull up;
	
}

uint8_t ir1_sensor_read(void)
{
    return (GPIOA->IDR & IR1_SENSOR_GPIO_PIN) ? 1 : 0; 
}

uint8_t ir2_sensor_read(void)
{
    return (GPIOA->IDR & IR2_SENSOR_GPIO_PIN) ? 1 : 0; 
}
