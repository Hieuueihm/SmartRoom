#include "dht11.h"
#include "uart.h"
#include "systick.h"
char num[10];
volatile int analog_rx = 0;


int main(void){
	systick_init();
	

	
		uart_init(UART3, BR_115200);

	while(1){
		TemperatureHumidity dht11 = readTemperatureHumidity();
		char num[50];

				snprintf(num, sizeof(num), "%.2f %.2f\n", dht11.humidity, dht11.temperature);	
			uart_send_msg(UART3, num);

			}
		

	}
		
