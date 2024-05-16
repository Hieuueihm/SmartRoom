#ifndef SERVO_H
#define SERVO_H

#include "stm32f10x.h"

void servo_init(void);
void servo_rotate(uint16_t angle);

#endif /* SERVO_H */
