#include "stm32f10x.h"
#include <stdio.h>

// Define the MQ135 structure
typedef struct {
    double RL; // RL
    double Vcc; // 3.3 hoac 5
    double ppm_smoke; // Maximum concentration of smoke in ppm
} MQ135;
void MQ135_Init(MQ135 *sensor, double rl, double vcc, double ppm);
int MQ135_ReadAnalog() ;
int MQ135_Calculate(MQ135 *sensor);
void GPIO_Config(void);
void SystemClock_Config(void);
void delay_us(uint32_t microseconds);