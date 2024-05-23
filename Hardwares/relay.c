#include "stm32f10x.h"
#include "relay.h"

#define RELAY_GPIO_PIN1     (1 << 5) // Pin A5
#define RELAY_GPIO_PIN2     (1 << 6) // Pin A6

void relay_init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    GPIOA->CRL &= ~(GPIO_CRL_MODE5 | GPIO_CRL_CNF5 | GPIO_CRL_MODE6 | GPIO_CRL_CNF6);  
    GPIOA->CRL |= GPIO_CRL_MODE5_0 | GPIO_CRL_MODE6_0;
}

void relay_on(uint8_t relay_num)
{
    switch(relay_num)
    {
        case 1:
            GPIOA->BSRR = RELAY_GPIO_PIN1; 
            break;
        case 2:
            GPIOA->BSRR = RELAY_GPIO_PIN2;
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
