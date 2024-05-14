#include "stm32f10x.h" 
#include "systick.h"

void systick_init(void)
{
	SysTick->CTRL = 0;
	SysTick->LOAD = 0x00FFFFFF;
	SysTick->VAL = 0;
	SysTick->CTRL = 5;
}
static void Delaymicro(void)
{
	SysTick->LOAD = 72;
	SysTick->VAL = 0;
	while((SysTick->CTRL & 0x00010000) == 0);
}

void delay_us(unsigned long t)
{
	for(;t>0;t--)
		{
			Delaymicro();
		}
}


static void DelayMillis(void)
{
	SysTick->LOAD = 0x11940;
	SysTick->VAL = 0;
	while((SysTick->CTRL & 0x00010000) == 0);
}

void delay_ms(unsigned long t)
{
	for(;t>0;t--)
		{
			DelayMillis();
		}
}

