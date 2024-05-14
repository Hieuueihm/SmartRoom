#include "i2c_lcd.h"

/*
P0 -> RS
P1 -> RW
P2 -> E
P3 -> Screen light // auto 1
P4 -> D4
P5 -> D5
P6 -> D6
P7 -> D7

*/

void add_slave(char RW){
	i2c_add(Slave_Address, RW);
}
void trans_slave(char data){
	i2c_start();
	add_slave(0);
	i2c_data(data);
	i2c_stop();
}
void lcd_i2c_data(unsigned char data)
{
	
	// rs high, rw low
	trans_slave(0x09);
	delay_us(10);
	// e high
	trans_slave(0x0D);
	delay_us(5);
	
	// trans data
	trans_slave(((data & 0x00f0) | 0x0D));
	delay_us(10);
	// e low
	trans_slave(((data & 0x00f0) | 0x09));
	
	delay_us(20);
	
	// e high
	trans_slave(0x0D);
	delay_us(5);
	
	trans_slave((((data << 4) & 0x00f0) | 0x0D));
	delay_us(10);
	trans_slave((((data << 4) & 0x00f0) | 0x09));
}


void lcd_i2c_cmd(unsigned char data)
{
	
	trans_slave(0x08);
	delay_us(10);
	trans_slave(0x0C);
	delay_us(5);
	trans_slave(((data & 0x00f0) | 0x0C));
	delay_us(10);
	trans_slave(((data & 0x00f0) | 0x08));
	delay_us(20);
	trans_slave(0x0C);
	delay_us(5);

	trans_slave((((data << 4) & 0x00f0) | 0x0C));
	delay_us(10);
	trans_slave((((data << 4) & 0x00f0) | 0x08));
}

void lcd_i2c_init(void)
{
  i2c_init(I2C_FM);
	delay_ms(20);

	trans_slave(0x08);
	delay_us(10);
	trans_slave(0x0C);
	delay_us(5);

	trans_slave(0x3C);
	delay_us(10);
	trans_slave(0x38);
	
	delay_ms(10);
	

	trans_slave(0x08);
	delay_us(10);
	trans_slave(0x0C);
	delay_us(5);

	trans_slave(0x3C);
	delay_us(10);

	trans_slave(0x38);
	
	delay_ms(1);
	

	
	trans_slave(0x08);
	delay_us(10);

	trans_slave(0x0C);
	delay_us(5);

	trans_slave(0x3C);
	delay_us(10);
	
	trans_slave(0x38);
	
	delay_ms(1);
	
	
	trans_slave(0x08);
	delay_us(10);

	trans_slave(0x0C);
	delay_us(5);
	
	trans_slave(0x2C);
	delay_us(10);
	trans_slave(0x28);
	
	
	lcd_i2c_cmd(0x2C); // 4 bit communication mode / 2 lines
	delay_ms(5);
	lcd_i2c_cmd(0x0C); // Display ON
	delay_ms(5);
	lcd_i2c_cmd(0x01); // Clear Display
	delay_ms(5);
	lcd_i2c_cmd(0x02); // Get back to initial address
	delay_ms(5);
}
void lcd_i2c_send(char str[])
{
	int i = 0;
		while(str[i])
		{
			lcd_i2c_data(str[i]);
			i++;
			delay_us(100);
		}
}
void lcd_i2c_msg(unsigned char line_1_2, unsigned char pos_0_16, char msg[])
{
	short pos = 0;
	if(line_1_2==1)
	{
		pos = 0;
	}
	else if(line_1_2==2)
	{
		pos = 0x40;
	}
	lcd_i2c_cmd(0x80 +pos + pos_0_16);
	delay_us(100);
	lcd_i2c_send(msg);
}

