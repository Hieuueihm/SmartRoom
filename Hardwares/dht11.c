#include "dht11.h"
#include <stdio.h>
#include "systick.h"

TemperatureHumidity readTemperatureHumidity()
{
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
   if (DHT11_CheckResponse())
   {
      uint8_t RH_integral = DHT11_ReadByte();
      uint8_t RH_decimal = DHT11_ReadByte();
      uint8_t T_integral = DHT11_ReadByte();
      uint8_t T_decimal = DHT11_ReadByte();
      uint8_t checksum = DHT11_ReadByte();

      // Ki?m tra checksum
      if (checksum == ((RH_integral + RH_decimal + T_integral + T_decimal) & 0xFF))
      {
         result.temperature = T_integral + (T_decimal / 100.0);
         result.humidity = RH_integral + (RH_decimal / 100.0);
      }
      else
      {

         result.temperature = -1.0;
         result.humidity = -1.0;
      }
   }
   else
   {
      result.temperature = -1.0;
      result.humidity = -1.0;
   }

   return result;
}

void GPIOdht_config(void)
{
   // Enable clock for GPIOA, bit2(IOPAEN)
   RCC->APB2ENR |= (1 << 2);
   // Clear MODE0 and CNF0
   GPIOA->CRL &= ~((0x3 << 0) | (0x3 << 2));
   // Output mode 10, Max speed 2Mhz
   GPIOA->CRL |= (0x2 << 0);
   // Output open drain 01
   GPIOA->CRL |= (0x1 << 2);
}

void set_GPIO_input(void)
{
   // Clear MODE0 and CNF0
   GPIOA->CRL &= ~((0x3 << 0) | (0x3 << 2));
   // Floating input
   GPIOA->CRL |= (0x1 << 2);
}

void set_GPIO_output(void)
{
   // Clear CNF0 bits
   GPIOA->CRL &= ~(0x3 << 2);
   // MODE0 = 10, CNF0 = 01 (Output open-drain)
   GPIOA->CRL |= (0x2 << 0) | (0x1 << 2);
}

int read_GPIO(void)
{
   return (GPIOA->IDR & (1 << 0)) ? 1 : 0;
}

void DHT11_Start(void)
{
   set_GPIO_output();
   // Set PA0 low
   GPIOA->BSRR = (1 << 16);
	// delay min 18ms
   delay_us(18000);
   // Set PA0 high
   GPIOA->BSRR = 1;
   delay_us(20);
   set_GPIO_input();
}

int DHT11_CheckResponse(void)
{
   int response = 0;
   delay_us(40);
   if (!read_GPIO())
   {
      delay_us(80);
      if (read_GPIO())
         response = 1;
      delay_us(50);
   }
   return response;
}

uint8_t DHT11_ReadByte(void)
{
   uint8_t i, data = 0;
   for (i = 0; i < 8; i++)
   {
      while (!read_GPIO());
      delay_us(40);
      if (!read_GPIO())
         data &= ~(1 << (7 - i));
      else
      {
         data |= (1 << (7 - i));
         while (read_GPIO());
      }
   }
   return data;
}
