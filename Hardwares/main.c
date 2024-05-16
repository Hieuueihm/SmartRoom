#include "stm32f10x.h"
#include "i2c.h"
#include "i2c_lcd.h"
#include "systick.h"
#include "uart.h"

#include "gpio.h"




int main(void){
	
	
		systick_init();
	
		//lcd_i2c_init(I2C_1);
	//	lcd_i2c_init(I2C_2);
		//lcd_i2c_msg(I2C_2, 1, 0,"AaBCddddxzD;x");
		//lcd_i2c_msg(I2C_1, 1, 0,"AaBCddddxzDzzx");
		uart_init(UART3, BR_115200);
	while(1){
			uart_send_msg(UART3, "tDeCstD");
			delay_ms(500);

	}
		

}
