#ifndef DHT11_H
#define DHT11_H
#include "stm32f10x.h"
#include <stdio.h>
#include "systick.h"
#include "gpio.h"
void GPIOdht_config(void);
void set_GPIO_input(void);
void set_GPIO_output(void);
int read_GPIO(void);
void DHT11_Start(void);
int DHT11_CheckResponse(void);
uint8_t DHT11_ReadByte(void);
void SystemClock_Config(void);
typedef struct DHT11
{
    float temperature;
    float humidity;
} TemperatureHumidity;

TemperatureHumidity readTemperatureHumidity();

#endif