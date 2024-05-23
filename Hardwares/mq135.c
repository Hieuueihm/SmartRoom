#include "mq135.h"
#include <stdio.h>
#include "adc.h"

int MQ135_Calculate(MQ135 *sensor) {
	  adc_init(ADC_1, PortA, 1);
	  if (adc_check(ADC_1, PortA, 1)) {
    int sensorValue = adc_rx(ADC_1, PortA, 1);
    double voltageSensor = sensorValue * (sensor->Vcc / 4095.0); // Convert sensor value to voltage
    double Rs = (sensor->Vcc * sensor->RL - voltageSensor * sensor->RL) / voltageSensor;
    return (int) (sensor->ppm_smoke * (Rs / sensor->RL));
			}
		else {
			return -1;
				}
}

void MQ135_Init(MQ135 *sensor, double rl, double vcc, double ppm) {
    sensor->RL = rl;
    sensor->Vcc = vcc;
    sensor->ppm_smoke = ppm;
}

