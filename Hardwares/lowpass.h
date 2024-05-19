#ifndef LOWPASS_H
#define LOWPASS_H

#include "stm32f10x.h"

#define PI 3.14159265358979323846
typedef struct LowPassFilter {
    float a[1];
    float b[2];
    float omega0;
    float dt;
    float x[2]; 
    float y[2]; 
} lowpass_filter;


// first order 
void lowpass_init(lowpass_filter *lp , float f0, float fs);
float filt(lowpass_filter * lp, float xn); // xn is current value 
#endif		