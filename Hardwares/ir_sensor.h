#ifndef IR_SENSOR_H
#define IR_SENSOR_H

#include "stm32f10x.h"
#include "gpio.h"
void ir_sensors_init(void);
uint8_t ir1_sensor_read(void);
uint8_t ir2_sensor_read(void);

#endif