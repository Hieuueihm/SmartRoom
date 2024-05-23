#include "stm32f10x.h"
#include "relay.h"
#include "gpio.h"

#define RELAY_GPIO_PIN1     (1 << 0) // Pin A0
#define RELAY_GPIO_PIN2     (1 << 1) // Pin A1

void relay_init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
		gpio_init(PortA, 0,OUT_GP_PP , OUT10);
			gpio_init(PortA, 1,OUT_GP_PP , OUT10);

}

void relay_on(uint8_t relay_num)
{
    switch(relay_num)
    {
        case 1:
            GPIOA->BSRR |= RELAY_GPIO_PIN1; 
            break;
        case 2:
            GPIOA->BSRR |= RELAY_GPIO_PIN2;
            break;
        default:
            break;
    }
}

void relay_off(uint8_t relay_num)
{
    switch(relay_num)
    {
        case 1:
            GPIOA->BRR = 1 << 0; 
            break;
        case 2:
            GPIOA->BRR = 1 << 1; 
            break;
        default:
            break;
    }
}
