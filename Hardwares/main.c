#include "stm32f10x.h"
#include "relay.h"
#include "ir_sensor.h"
#include "servo.h"
#include "systick.h"

//Relay Pin5,6
//Servo Pin1/TIM2
//Ir Pin3,4

int people_count = 0;
int ir1_last_state = 1, ir2_last_state = 1;
void peopleCount(void);

int main(void)
{
	servo_init();
	ir_sensors_init();
	systick_init();
	relay_init();
	servo_rotate(0);
  while(1){
		if (ir1_sensor_read() == 0 || ir2_sensor_read() == 0) {
        servo_rotate(90);
			  delay_ms(5000);				
			  servo_rotate(0);
				delay_ms(1000);
				relay_on(1);
		}
  }
}

void peopleCount(void) {
	int ir1_current = ir1_sensor_read();
	int ir2_current = ir2_sensor_read();

	if (ir1_last_state == 1 && ir1_current == 0) {
		while (ir1_sensor_read() == 0);
		delay_ms(50);  
		if (ir2_sensor_read() == 0) {
			while (ir2_sensor_read() == 0); 
			people_count++; 
		}
	}

	
	if (ir2_last_state == 1 && ir2_current == 0) {
		while (ir2_sensor_read() == 0); 
		delay_ms(50); 
		if (ir1_sensor_read() == 0) {
			while (ir1_sensor_read() == 0); 
			if (people_count > 0) 
				people_count--; 
		}
	}

	ir1_last_state = ir1_current;
	ir2_last_state = ir2_current;
}
