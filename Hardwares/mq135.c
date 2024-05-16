#include "mq135.h"
#include <stdio.h>

// Read analog value from the sensor
int MQ135_ReadAnalog() {
    ADC1->SQR3 |= (1 << 0); 
    ADC1->CR2 |= ADC_CR2_ADON; 
    while (!(ADC1->SR & ADC_SR_EOC)); 
    int analogValue = ADC1->DR; 
    return analogValue; 
}
int MQ135_Calculate(MQ135 *sensor) {
    int sensorValue = MQ135_ReadAnalog();
    double voltageSensor = sensorValue * (sensor->Vcc / 4095.0); // Convert sensor value to voltage
    double Rs = (sensor->Vcc * sensor->RL - voltageSensor * sensor->RL) / voltageSensor;
    return (int) (sensor->ppm_smoke * (Rs / sensor->RL));
}

void GPIO_Config(void) {
    RCC->APB2ENR |= (1 << 2);
    GPIOA->CRL &= ~((0x3 << 4) | (0x3 << 6));
    GPIOA->CRL |= (0x0 << 4); 
}
void SystemClock_Config(void) {
    RCC->CR |= RCC_CR_HSEON;
    while (!(RCC->CR & RCC_CR_HSERDY));
    RCC->CFGR |= RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL9;
    RCC->CR |= RCC_CR_PLLON;
    while (!(RCC->CR & RCC_CR_PLLRDY));
    RCC->CFGR |= RCC_CFGR_SW_PLL;
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
    SystemCoreClockUpdate();
}
void delay_us(uint32_t microseconds) {
    SysTick->LOAD = (SystemCoreClock / 1000000) * microseconds - 1;
    SysTick->VAL = 0;
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;
    while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0);
    SysTick->CTRL = 0;
}
void MQ135_Init(MQ135 *sensor, double rl, double vcc, double ppm) {
    GPIO_Config();
    USART1_Config();
    SystemClock_Config();
    sensor->RL = rl;
    sensor->Vcc = vcc;
    sensor->ppm_smoke = ppm;
}

