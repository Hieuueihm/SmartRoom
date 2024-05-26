#ifndef DHT11_H
#define DHT11_H
#include "stm32f10x.h"
#include <stdio.h>
#include "systick.h"
void GPIOdht_config(void);
void set_GPIO_input(void);
void set_GPIO_output(void);
int read_GPIO(void);
void DHT11_Start(void);
int DHT11_CheckResponse(void);
uint8_t DHT11_ReadByte(void);

typedef struct {
    uint8_t temperature;
    uint8_t humidity;
} TemperatureHumidity;
TemperatureHumidity readTemperatureHumidity();

#endif