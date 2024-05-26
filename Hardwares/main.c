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

volatile uint32_t counter = 0;

// counter 0 -> 0xFFFF  -> after 16 minutes -> reset 0
void TIM1_UP_IRQHandler(void) {
    if (TIM1->SR & TIM_SR_UIF) { // Check if update interrupt flag is set
        TIM1->SR &= ~TIM_SR_UIF; // Clear the update interrupt flag
        counter++; // Increment the counter
    }
}



#define abs(x, y) (x > y ? x - y  : y - x)


#define DOOR_OP 1
#define DOOR_CL 0

#define RELAY_1_ON 1
#define RELAY_1_OFF 0

#define RELAY_2_ON 1
#define RELAY_2_OFF 0



#define ACTIVE_STATE 0
#define ALERT_STATE 1
#define DOOR_OP_STATE 2


#define TIME_5S 20
#define TIME_3S 12
#define TIME_1S 4
#define TIME_2S 8
#define TIME_0_5S 2
#define TIME_0_25S 1


void handle_ir_open_door(void);


char num[50];
volatile int analog_rx = 0;
volatile uint8_t state = 0;
char dht[50];
volatile uint8_t nop = 0;
volatile uint8_t flag_ir1 = 0;
volatile uint8_t flag_ir2 = 0;

char nopeople[3];

volatile u16 last_time_ir1_request = 0;
volatile u16 last_time_ir2_request = 0;
volatile uint32_t last_time_open_door = 0;
volatile uint32_t last_time_fire_alarm = 0;
volatile uint32_t last_time_update_all = 0;
volatile uint32_t las_time_go_door = 0;
volatile u8 door_state = 0;


volatile u8 ir1_last_state = 1;
volatile u8 ir2_last_state = 1;
volatile u8 relay_1_state = 0;

u8 temp=0,humi=0;





int main(void){

	
		
		systick_init();
	
		relay_init();	
		lcd_i2c_init(I2C_1);
	
	
		servo_init();
		ir_sensors_init();
	
	
		// Port of flame, gas sensor	
		
		gpio_init(PortB, 8, IN_PUSHPULL, IN);
		gpio_init(PortB, 9, IN_PUSHPULL, IN);
			
		GPIOdht_config();
		TemperatureHumidity dht11; // = readTemperatureHumidity();
	
		lowpass_filter lp;
		lowpass_init(&lp, 0.1, 2);

		lcd_i2c_msg(I2C_1, 1, 0, "Num Of People: ");
		snprintf(nopeople, sizeof(nopeople), "%d", nop);
		lcd_i2c_msg(I2C_1, 1, 14, nopeople);




		servo_rotate(0);
		door_state = DOOR_CL;
		delay_ms(100);
		
	 //	intr_init();
					
		//EXTI->PR |= (1 << 8) | (1 << 9);
	pwm_init(TIM_3, CHANNEL_3);
		set_duty(TIM_3, CHANNEL_3, ARRD);
		adc_init(ADC_1, PortA, 2);

	


	while(1){		
		
		// if it detect = 0 -> alarm system
		if(gpio_read(PortB, 9) == 0 || gpio_read(PortB, 8) == 0){
				state = ALERT_STATE;
				relay_on(2);
				last_time_fire_alarm = counter;
				servo_rotate(90);
				last_time_open_door = counter;
				delay_ms(10);
			
		
		}
		
		
		if(counter - last_time_update_all >= TIME_0_25S){
		
			dht11 = readTemperatureHumidity();

			last_time_update_all = counter;
			snprintf(num, sizeof(num), "Temp:%d Humi:%d ", dht11.temperature, dht11.humidity);
			lcd_i2c_msg(I2C_1, 2, 0,num);
			lcd_i2c_msg(I2C_1, 1, 14, nopeople);
			
			analog_rx = adc_rx(ADC_1, PortA, 2);
			analog_rx =  filt(&lp, analog_rx);
			set_duty(TIM_3, CHANNEL_3, (analog_rx / 4096.0) * ARRD);		
	
		}

		handle_ir_open_door();
		
		if(nop >0 ){
			if(relay_1_state == RELAY_1_OFF){
				relay_on(1);
				relay_1_state = RELAY_1_ON;
			}
		}else if(nop  ==0 ){
			if(relay_1_state == RELAY_1_ON){
							relay_off(1);
					relay_1_state = RELAY_1_OFF;


			}
		}
		
		switch(state){
			case ACTIVE_STATE:
				if(abs(counter, last_time_open_door) < TIME_5S){
					state = DOOR_OP_STATE;
				}
				break;
			case ALERT_STATE:
				// after 5s if not fire -> turn off fire alarm system
				if(abs(counter,last_time_fire_alarm) >= TIME_5S && abs(counter, last_time_open_door) < TIME_5S)
			{
					state = DOOR_OP_STATE;
					relay_off(2);
					
				}else if(abs(counter, last_time_fire_alarm) >= TIME_5S && abs(counter, last_time_open_door) >= TIME_5S){
					relay_off(2);
					state= ACTIVE_STATE;
					servo_rotate(0);
					delay_us(100); // delay 100 micro s
				}
				break;
			case DOOR_OP_STATE:
				if(abs(counter, last_time_open_door) >= TIME_5S){
					door_state = DOOR_CL;
					servo_rotate(0);
					delay_us(100);
					state = ACTIVE_STATE;
				}
				break;
		}
			
		
			
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


void handle_ir_open_door(){
			// falling edge

		if(ir1_sensor_read() == 0 && ir1_last_state == 1){
			ir1_last_state = 0;
			if(flag_ir2 == 1){
				if(nop >0){
					nop--;
				}
				snprintf(nopeople, sizeof(nopeople), "%d", nop);
				flag_ir2 = 0;
			}else if(flag_ir2 == 0){
					if(door_state == DOOR_CL){
						servo_rotate(90);
						delay_ms(10);
						door_state = DOOR_OP;
					}
					flag_ir1 = 1;
					last_time_ir1_request = counter;				
			}
		}else if(ir1_sensor_read() == 1 && ir1_last_state == 0){
			ir1_last_state = ir1_sensor_read();
			last_time_open_door = counter;
		}
		
		
		if(ir2_sensor_read() == 0 && ir2_last_state == 1){
			ir2_last_state = 0;
			if(flag_ir1 == 1){
				
				nop++;
				snprintf(nopeople, sizeof(nopeople), "%d", nop);
				flag_ir1 = 0;
			}else if(flag_ir1 == 0){
					if(door_state == DOOR_CL){
						servo_rotate(90);
						delay_ms(10);
						door_state = DOOR_OP;
					}
					flag_ir2 = 1;
					last_time_ir2_request = counter;				
			}
		}else if(ir2_sensor_read() == 1 && ir2_last_state == 0){
			ir2_last_state = ir2_sensor_read();
			last_time_open_door = counter;
		}
				// people stand in front of the door but not go

		if(counter - last_time_ir1_request >= TIME_2S)
		{
			flag_ir1 = 0;
		}
		if(counter - last_time_ir2_request >= TIME_2S){
			flag_ir2 = 0;
		}
}