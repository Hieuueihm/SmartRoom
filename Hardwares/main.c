#include "stm32f10x.h"
#include "i2c.h"
#include "i2c_lcd.h"
#include "systick.h"
#include "uart.h"
#include "gpio.h"
#include "adc.h"
#include "pwm.h"
#include <stdio.h>


char num[10];
	volatile int analog_rx = 0;


int main(void){
	
	
		systick_init();
	
		//lcd_i2c_init(I2C_1);
	//	lcd_i2c_init(I2C_2);
		//lcd_i2c_msg(I2C_2, 1, 0,"AaBCddddxzD;x");
		//lcd_i2c_msg(I2C_1, 1, 0,"AaBCddddxzDzzx");
	
		pwm_init(TIM_2, CHANNEL_3);
		set_duty(TIM_2, CHANNEL_3, 15000);
	
		uart_init(UART3, BR_115200);
		adc_init(ADC_1, PortA, 1);
	


	while(1){
			
		
			
	//		if(adc_check(ADC_1, PortA, 1)){
				
		

				
		//	}
			
					analog_rx = adc_rx(ADC_1, PortA, 1);
				set_duty(TIM_2, CHANNEL_3, (analog_rx / 4096.0) * ARRD);
				snprintf(num, sizeof(num), "%d, ",   analog_rx);	

				//snprintf(num, sizeof(num), "%.2f\n",   (analog_rx / 4096.0) * ARRD);	
			uart_send_msg(UART3, num);
				delay_ms(1000);


			}
		

	}
		
