#include "dht11.h"
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
#include "systick.h"
#include "i2c_lcd.h"


#define ACTIVE_STATE 0
#define ALARM_STATE 1
#define DOOR_OP_STATE 2


char num[50];
volatile int analog_rx = 0;
volatile uint8_t state = 0;
char dht[50];
volatile uint8_t nop = 0;
volatile uint8_t nop_flag_ir1 = 0;
volatile uint8_t nop_flag_ir2 = 0;

char nopeople[3];

volatile uint32_t last_time_open_door = 0;
volatile uint32_t last_time_fire_alarm = 0;
volatile uint32_t last_time_update_all = 0;
volatile uint32_t counter = 0;
volatile uint32_t las_time_go_door = 0;

void TIM1_UP_IRQHandler(void) {
    if (TIM1->SR & TIM_SR_UIF) { // Check if update interrupt flag is set
        TIM1->SR &= ~TIM_SR_UIF; // Clear the update interrupt flag
        counter++; // Increment the counter
    }
}

int main(void){

	
		
		systick_init();
		pwm_init(TIM_3, CHANNEL_3);
		set_duty(TIM_3, CHANNEL_3, ARRD);

	relay_init();	

	
	
		lcd_i2c_init(I2C_1);
	lcd_i2c_msg(I2C_1, 1, 0, "Num Of People: ");
	snprintf(nopeople, sizeof(nopeople), "%d", nop);
							lcd_i2c_msg(I2C_1, 1, 14, nopeople);

		lowpass_filter lp;
		lowpass_init(&lp, 0.1, 2);
		//relay_on(2);
		adc_init(ADC_1, PortA, 2);

	
		servo_init();
	ir_sensors_init();

//relay_off(1);

	//			delay_ms(3000);
		//		relay_off(2);
		gpio_init(PortB, 8, IN_PUSHPULL, IN);
		gpio_init(PortB, 9, IN_PUSHPULL, IN);
			DHT11_Init();

		servo_rotate(0);

		delay_ms(100);
		
	 u8 temp=0,humi=0;
	 		//	intr_init();
					
					//EXTI->PR |= (1 << 8) | (1 << 9);

	


	while(1){			
		if(counter - last_time_update_all >= 1){
						analog_rx = adc_rx(ADC_1, PortA, 2);
			analog_rx = filt(&lp, analog_rx);
		set_duty(TIM_3, CHANNEL_3, (analog_rx / 4096.0) * ARRD);
					DHT11_Read_Data(&temp,&humi);

			last_time_update_all = counter;
			snprintf(num, sizeof(num), "%d %d %d", temp, humi, counter);
				lcd_i2c_msg(I2C_1, 2, 0,num);
			lcd_i2c_msg(I2C_1, 1, 14, nopeople);
			
	
				//delay_ms(100);
		if(ir1_sensor_read() == 0 && nop_flag_ir2 == 0){
				servo_rotate(90);
				delay_ms(100);
				nop_flag_ir1 = 1;
		}else if(ir1_sensor_read()== 0 && nop_flag_ir2 == 1){
				nop--;
				snprintf(nopeople, sizeof(nopeople), "%d", nop);
				relay_off(1);
				nop_flag_ir2 = 0;
		}
		if(ir2_sensor_read() == 0 && nop_flag_ir1 == 1){
				nop++;
				snprintf(nopeople, sizeof(nopeople), "%d", nop);
				relay_on(1);
				nop_flag_ir1 = 0;
		}else if(ir2_sensor_read() == 0 && nop_flag_ir1 == 0){
				nop_flag_ir2 = 1;
				servo_rotate(90);
				delay_ms(100);
		}
		
			

		}
		
		if(gpio_read(PortB, 9) == 0 || gpio_read(PortB, 8) == 0){
			
		
		}
		
	
					
		

		
	
	

		/*
		
		if()
		DHT11_Read_Data(&temp,&humi);
			
		
		lcd_i2c_msg(I2C_1, 1, 14, nopeople);
		
		delay_ms(1000);
		switch(state){		
			case ACTIVE_STATE:
				break;
			case ALARM_STATE:
			
				break;
			case DOOR_OP_STATE:
			
				if(counter - last_time_go_door >= 5){

						servo_rotate(0);
					
						delay_ms(1000);
						state = ACTIVE_STATE;
					}else{
								
		
							if(nop >= 1){
								relay_on(1);
							}else{
									relay_off(1);
						}
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
/*
	void EXTI3_IRQHandler(){
		if(EXTI->PR & (1 << 3)){
			servo_rotate(90);
			EXTI->PR |= (1 << 3 );
			state = DOOR_OP_STATE;
			last_time_open_door = counter;
			if(nop_flag_ir2 == 1){
				nop_flag_ir2 = 0;
				nop--;
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
				state = DOOR_OP_STATE;
			last_time_open_door = counter;
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
		
		if((EXTI -> PR & (1 << 8)) || ((EXTI->PR) & (1 << 9))){
					EXTI->PR |= (1 << 8 ) | (1 << 9);

			last_time_fire_alarm = counter;
			servo_rotate(90);
			relay_on(2);
			

		}
	}



*/