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


Status I2C_Init(unsigned short speed_mode);
Status I2C_Add(char address, char RW);
Status I2C_Write(char address, char data[]);
Status I2C_Data(char data);
Status I2C_Start();
Status I2C_Stop();



#endif


