#include "stm32f10x.h"
#include "i2c.h"
#include "i2c_lcd.h"
#include "systick.h"




int main(void){
	
	
		systick_init();
	
		lcd_i2c_init();
		lcd_i2c_msg(1, 0,"ABCxzx");
	while(1){
	
	}
		

}
