#include "dht11.h"
#include <stdio.h>
#include "systick.h"


TemperatureHumidity readTemperatureHumidity() {
    TemperatureHumidity result;
	DHT11_Start();
	   /*    uint8_t RH_integral = DHT11_ReadByte();
        uint8_t RH_decimal = DHT11_ReadByte();
        uint8_t T_integral = DHT11_ReadByte();
        uint8_t T_decimal = DHT11_ReadByte();
        uint8_t checksum = DHT11_ReadByte();
	      result.temperature = T_integral + (T_decimal / 100.0);
        result.humidity = RH_integral + (RH_decimal / 100.0);
	*/
    if (DHT11_CheckResponse()) {
        uint8_t RH_integral = DHT11_ReadByte();
        uint8_t RH_decimal = DHT11_ReadByte();
        uint8_t T_integral = DHT11_ReadByte();
        uint8_t T_decimal = DHT11_ReadByte();
        uint8_t checksum = DHT11_ReadByte();
        
        // Ki?m tra checksum
        if (checksum == ((RH_integral + RH_decimal + T_integral + T_decimal) & 0xFF)) {
            result.temperature = T_integral + (T_decimal / 100.0);
            result.humidity = RH_integral + (RH_decimal / 100.0);
        } else {

            result.temperature = -1.0;
            result.humidity = -1.0;
        }
    }  else {
        result.temperature = -1.0;
        result.humidity = -1.0;
    } 
    
    return result; 
}

void GPIOdht_config(void) {
	// Enable clock for GPIOA, bit2(IOPAEN)
	RCC->APB2ENR |= (1<<2); 
	// Clear MODE0 and CNF0
	GPIOA->CRL &= ~((0x3 << 0) | (0x3 << 2));
	// Output mode 10, Max speed 2Mhz
	GPIOA->CRL |= (0x2<<0);
	// Output open drain 01
	GPIOA->CRL |= (0x1<<2);
	
}

void set_GPIO_input(void) {
	// Clear MODE0 and CNF0
	GPIOA->CRL &= ~((0x3<<0)|(0x3<<2)); 
	// Floating input
	GPIOA->CRL |= (0x1<<2);
}

void set_GPIO_output(void) {
	// Clear CNF0 bits
	GPIOA->CRL &= ~(0x3 << 2); 
	// MODE0 = 10, CNF0 = 01 (Output open-drain)
	GPIOA->CRL |= (0x2 << 0) | (0x1 << 2);  
}

int read_GPIO(void) {
   return (GPIOA->IDR & (1 << 0)) ? 1 : 0;
}

void DHT11_Start(void) {
   set_GPIO_output();
   // Set PA0 low
   GPIOA->BSRR = (1 << 16); 
   delay_uis(18000);    
   // Set PA0 high	
   GPIOA->BSRR = 1;          
   delay_uis(20);           
   set_GPIO_input();
}


int DHT11_CheckResponse(void) {
   int response = 0;
   delay_uis(40);
   if (!read_GPIO()) {
      delay_uis(80);
      if (read_GPIO()) response = 1;
      delay_uis(50);
   }
   return response;
}

uint8_t DHT11_ReadByte(void) {
   uint8_t i, data = 0;
   for (i = 0; i < 8; i++) {
     while (!read_GPIO());
       delay_uis(40);
       if (!read_GPIO()) data &= ~(1 << (7 - i));  
       else {
          data |= (1 << (7 - i));  
          while (read_GPIO()); 
       }
   }
   return data;
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
void delay_uis(uint32_t microseconds) {
   SysTick->LOAD = (SystemCoreClock / 1000000) * microseconds - 1; 
   SysTick->VAL = 0; 
	 // Enable SysTick
   SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk; 
   while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0);
	 // disable SysTick
	 SysTick->CTRL = 0; 
}