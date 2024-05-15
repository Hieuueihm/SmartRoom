#include "stm32f10x.h"
#include "i2c.h"
#include "i2c_lcd.h"
#include "systick.h"
#include "uart.h"




int main(void){
	
	
		systick_init();
	
		lcd_i2c_init();
		lcd_i2c_msg(1, 0,"AaBCddddxzDx");
		uart_init(UART3, BR_115200);
	while(1){
			uart_send_msg(UART3, "test");
			delay_ms(500);

	}
		

}
