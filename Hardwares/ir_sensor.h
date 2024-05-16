#ifndef IR_SENSOR_H
#define IR_SENSOR_H

#include "stm32f10x.h"

void ir_sensor_init(void);
uint8_t ir_sensor_read(void);

#endif
