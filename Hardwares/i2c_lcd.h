#ifndef I2C_LCD_H_
#define I2C_LCD_H_
#include "i2c.h"

#define Slave_Address 0x4E


void add_slave(char RW);
void trans_slave(char data);


void lcd_i2c_cmd(unsigned char data);
void lcd_i2c_data(unsigned char data);
void lcd_i2c_init(void);

void lcd_i2c_send(char str[]);

void lcd_i2c_msg( unsigned char line_1_2, unsigned char pos_0_16, char msg[]);

#endif