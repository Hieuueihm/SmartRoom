#include "stm32f10x.h"
#include <stdio.h>

void GPIOdht_config(void);
void set_GPIO_input(void);
void set_GPIO_output(void);
int read_GPIO(void);
void DHT11_Start(void);
int DHT11_CheckResponse(void);
uint8_t DHT11_ReadByte(void);
void SystemClock_Config(void);
void delay_uis(uint32_t microseconds);
typedef struct
{
    float temperature;
    float humidity;
} TemperatureHumidity;
TemperatureHumidity readTemperatureHumidity();