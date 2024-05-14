#ifndef I2C_H
#define I2C_H


#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "systick.h"

#define I2C_FM 0x2D
#define I2C_SM 0xB4
#define ACK 0
#define NACK 1

typedef enum{Error = 0, Success = !Error} Status;


Status i2c_init(unsigned short speed_mode);
Status i2c_add(char address, char RW);
Status i2c_write(char address, char data[]);
Status i2c_data(char data);
Status i2c_start();
Status i2c_stop();



#endif


