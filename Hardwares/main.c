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
#include "ir_sensor.h"
#include "dht11.h"
#include "interrupt.h"

#define ACTIVE_STATE 0
#define ALARM_STATE 1
#define DOOR_OP_STATE_0 2
#define DOOR_OP_STATE_1 3



char num[50];
volatile int analog_rx = 0;
uint8_t state = 0;
char dht[50];
volatile uint8_t nop = 0;
volatile uint8_t nop_flag_ir1 = 0;
volatile uint8_t nop_flag_ir2 = 0;

char nopeople[3];

volatile uint32_t last_time = 0;


int main(void){

	
		SystemClock_Config();

		systick_init();
	pwm_init(TIM_3, CHANNEL_3);
		set_duty(TIM_3, CHANNEL_3, ARRD);

	relay_init();	
	//relay_on(1);


		lcd_i2c_init(I2C_1);
	lcd_i2c_msg(I2C_1, 1, 0, "Num Of People: ");
	snprintf(nopeople, sizeof(nopeople), "%d", nop);
							lcd_i2c_msg(I2C_1, 1, 14, nopeople);

		lowpass_filter lp;
		lowpass_init(&lp, 0.3, 100);

		//relay_on(2);
		adc_init(ADC_1, PortA, 2);

	
		servo_init();
	ir_sensors_init();

//relay_off(1);

	//			delay_ms(3000);
		//		relay_off(2);
		gpio_init(PortB, 8, IN_PUSHPULL, IN);
		gpio_init(PortB, 9, IN_PUSHPULL, IN);
		GPIOB->ODR |= (1 << 8) | (1 << 9);
		
	GPIOdht_config();

	TemperatureHumidity dht11; // = readTemperatureHumidity();

				intr_init();

		servo_rotate(0);

		delay_ms(100);
		


	while(1){
		
		
dht11 = readTemperatureHumidity();
		snprintf(dht,sizeof(dht) ,"%.2fp-%.2f oC", dht11.humidity, dht11.temperature);
		lcd_i2c_msg(I2C_1, 2, 0,dht);
		lcd_i2c_msg(I2C_1, 1, 14, nopeople);
			if(adc_check(ADC_1, PortA, 2)){
				analog_rx = adc_rx(ADC_1, PortA, 2);
				analog_rx = filt(&lp, analog_rx);
				set_duty(TIM_3, CHANNEL_3, (analog_rx / 4096.0) * ARRD);
				//delay_ms(100);

		}
			delay_ms(1000);
		switch(state){
			
		
				
			case ACTIVE_STATE:
				break;
			case ALARM_STATE:
				relay_on(2);			

				servo_rotate(90);
				delay_ms(10);
				
				break;
			case DOOR_OP_STATE_0:
				
				
			
			state = 3;
				break;
			case DOOR_OP_STATE_1:
				if(nop >= 1){
					relay_on(1);
					delay_ms(10);
				}else{
					relay_off(1);
				}
				if(get_tick() - last_time >= 5000 * 1000){
					servo_rotate(0);
					
					state = 0;
					nop_flag_ir1 = 0;
										nop_flag_ir2 = 0;

				}
				break;
			default:
				break;
			
			
		

		}
		
		/*
		
			
/*			
		dht11 = readTemperatureHumidity();
		snprintf(dht,sizeof(dht) ,"%.2f   %.2f", dht11.humidity, dht11.temperature);

					lcd_i2c_msg(I2C_1, 2, 0,dht);
//delay_ms(1000);
		//uart_send_msg(UART3, num);
		
/*
			if(adc_check(ADC_1, PortA, 2)){
				analog_rx = adc_rx(ADC_1, PortA, 2);
		set_duty(TIM_3, CHANNEL_3, (analog_rx / 4096.0) * ARRD);
				//delay_ms(100);

		}
	*/	
			//snprintf(num, sizeof(num), "%d, ",   analog_rx);	

			//uart_send_msg(UART3, num);
		//delay_ms(100);/
	/*	
		if(ir1_sensor_read() == 0  || ir2_sensor_read() == 0){

			 servo_rotate(90);
			  delay_ms(2000);				
			  servo_rotate(0);
				delay_ms(1000);

		}
		*/
		
	}

	}
	
	void EXTI3_IRQHandler(){
		if(EXTI->PR & (1 << 3)){
				servo_rotate(90);

				EXTI->PR |= (1 << 3 );
			state = DOOR_OP_STATE_0;
			
			last_time = get_tick();
			if(nop_flag_ir2 == 1){
								nop_flag_ir2 = 0;
		
				nop++;
				snprintf(nopeople, sizeof(nopeople), "%d", nop);
			}else{
				nop_flag_ir1 = 1;
			}
		


		}
		
	}

		void EXTI4_IRQHandler(){

		if(EXTI->PR & (1 << 4)){
									servo_rotate(90);

					EXTI->PR |= (1 << 4 );
									state = DOOR_OP_STATE_0;
						last_time = get_tick();


	if(nop_flag_ir1 == 1){

						nop_flag_ir1 = 0;

				nop++;
						snprintf(nopeople, sizeof(nopeople), "%d", nop);

			}else{
				nop_flag_ir2 = 1;
			}
			
			


		}
		
		
	}
		
	void EXTI9_5_IRQHandler(){
		if((EXTI -> PR & (1 << 8))		|| ((EXTI->PR) & (1 << 9))){
				EXTI->PR |= (1 << 8 ) | (1 << 9);
			state =  ALARM_STATE;
			

		}
	}


