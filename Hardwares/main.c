#include "stm32f10x.h"
#include "i2c.h"
#include "i2c_lcd.h"
#include "systick.h"
#include "uart.h"
#include "gpio.h"
#include "adc.h"
#include "pwm.h"
#include <stdio.h>
#include "lowpass.h"
#include "servo.h"
#include "relay.h"

char num[10];
volatile int analog_rx = 0;


int main(void){
	
	
		systick_init();
	
		//lcd_i2c_init(I2C_1);
		//lcd_i2c_init(I2C_2);
	//	lcd_i2c_msg(I2C_2, 1, 0,"AaBCddddxzD;x");
		//lcd_i2c_msg(I2C_1, 1, 0,"AaBCddddxzDzzx");
	
		//lowpass_filter lp;
		//lowpass_init(&lp, 0.3, 100);
	
	
		//pwm_init(TIM_3, CHANNEL_3);
	//	set_duty(TIM_3, CHANNEL_3, ARRD);
	
	uart_init(UART3, BR_115200);
		//servo_init();

		adc_init(ADC_1, PortA, 3);
		relay_init();

				//relay_on(1);
				//delay_ms(3000);
					//relay_on(2);




	


	while(1){
		

			analog_rx = adc_rx(ADC_1, PortA, 3);
			
			snprintf(num, sizeof(num), "%d, ",   analog_rx);	

			uart_send_msg(UART3, num);
			delay_ms(100);
		}
	}
		
