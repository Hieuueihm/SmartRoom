#include "i2c_lcd.h"

/*
P0-> RS (LCD cmd wire)
P1-> RW (LCD cmd wire)
P2-> E (LCD cmd wire)
P3-> Screen light --> Must always be 1
P4-> D4 (LCD Data wire)
P5-> D5 (LCD Data wire)
P6-> D6 (LCD Data wire)
P7-> D7 (LCD Data wire)

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
	// data 
	trans_slave(((data & 0x00f0) | 0x0C)); // 00001100
	delay_us(10);
	trans_slave(((data & 0x00f0) | 0x08)); // 00001000
	delay_us(20);
	trans_slave(0x0C); //00001100
	delay_us(5);

	trans_slave((((data << 4) & 0x00f0) | 0x0C));
	delay_us(10);
	trans_slave((((data << 4) & 0x00f0) | 0x08));
}

void lcd_i2c_init(void)
{
	//d7-d6-d5-d4-light-en-rw-rs
  i2c_init(I2C_FM);
	delay_ms(20);

	trans_slave(0x08); // 00001000
	delay_us(10);
	// enable high
	trans_slave(0x0C); // 00001100
	delay_us(5);	
	trans_slave(0x3C); // 00111100
	delay_us(10);
	trans_slave(0x38); // 00111000
	delay_ms(1);
	
	trans_slave(0x08); // 00001000
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
	
	trans_slave(0x2C); //00101100
	delay_us(10);
	trans_slave(0x28); // 00101000
	
	
	lcd_i2c_cmd(0x2C); //00101100 // 4 bit communication mode // 2 lines-display N = 1
	delay_ms(5);
	lcd_i2c_cmd(0x0C); // Display ON
	delay_ms(5);
	
	lcd_i2c_cmd(0x01); // Clear Display // rs = 1	
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

