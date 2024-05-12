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

void Add_Slave(char RW){
	I2C_Add(Slave_Address, RW);
}
void Trans_Slave(char data){
	I2C_Start();
	Add_Slave(0);
	I2C_Data(data);
	I2C_Stop();
}
void lcd_i2c_data(unsigned char data)
{
	
	// rs high, rw low
	Trans_Slave(0x09);
	DelayUs(10);
	// e high
	Trans_Slave(0x0D);
	DelayUs(5);
	
	// trans data
	Trans_Slave(((data & 0x00f0) | 0x0D));
	DelayUs(10);
	// e low
	Trans_Slave(((data & 0x00f0) | 0x09));
	
	DelayUs(20);
	
	// e high
	Trans_Slave(0x0D);
	DelayUs(5);
	
	Trans_Slave((((data << 4) & 0x00f0) | 0x0D));
	DelayUs(10);
	Trans_Slave((((data << 4) & 0x00f0) | 0x09));
}


void lcd_i2c_cmd(unsigned char data)
{
	
	Trans_Slave(0x08);
	DelayUs(10);
	Trans_Slave(0x0C);
	DelayUs(5);
	Trans_Slave(((data & 0x00f0) | 0x0C));
	DelayUs(10);
	Trans_Slave(((data & 0x00f0) | 0x08));
	DelayUs(20);
	Trans_Slave(0x0C);
	DelayUs(5);

	Trans_Slave((((data << 4) & 0x00f0) | 0x0C));
	DelayUs(10);
	Trans_Slave((((data << 4) & 0x00f0) | 0x08));
}

void lcd_i2c_init(void)
{
  I2C_Init(I2C_FM);
	DelayMs(20);

	Trans_Slave(0x08);
	DelayUs(10);
	Trans_Slave(0x0C);
	DelayUs(5);

	Trans_Slave(0x3C);
	DelayUs(10);
	Trans_Slave(0x38);
	
	DelayMs(10);
	

	Trans_Slave(0x08);
	DelayUs(10);
	Trans_Slave(0x0C);
	DelayUs(5);

	Trans_Slave(0x3C);
	DelayUs(10);

	Trans_Slave(0x38);
	
	DelayMs(1);
	

	
	Trans_Slave(0x08);
	DelayUs(10);

	Trans_Slave(0x0C);
	DelayUs(5);

	Trans_Slave(0x3C);
	DelayUs(10);
	
	Trans_Slave(0x38);
	
	DelayMs(1);
	
	
	Trans_Slave(0x08);
	DelayUs(10);

	Trans_Slave(0x0C);
	DelayUs(5);
	
	Trans_Slave(0x2C);
	DelayUs(10);
	Trans_Slave(0x28);
	
	
	lcd_i2c_cmd(0x2C); // 4 bit communication mode / 2 lines
	DelayMs(5);
	lcd_i2c_cmd(0x0C); // Display ON
	DelayMs(5);
	lcd_i2c_cmd(0x01); // Clear Display
	DelayMs(5);
	lcd_i2c_cmd(0x02); // Get back to initial address
	DelayMs(5);
}
void lcd_i2c_send(char str[])
{
	int i = 0;
		while(str[i])
		{
			lcd_i2c_data(str[i]);
			i++;
			DelayUs(100);
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
	DelayUs(100);
	lcd_i2c_send(msg);
}

