#include "uart.h"



void uart_init(unsigned short usart, unsigned short br)
{
 /// If using USART1 clock speed 72Mhz, else 36Mhz
		RCC->APB2ENR |= 1;

	if(usart == UART1)
	{
	RCC->APB2ENR |= (1 << 14); 
		gpio_init(PortA,9,OUT50,OUT_AF_PP);
	gpio_init(PortA,10,IN,IN_PUSHPULL);
	if(br == BR_9600){
		USART1->BRR = 0b1110101000110; 
		
	}else if(br == BR_115200){
		USART1->BRR = 0b000001001110001; 
	
	}
	USART1->CR1 |= (1 << 3);
	USART1->CR1 |= (1 << 2);
	USART1->CR1 |= (1 << 13);
	USART1->CR1 |=(1 << 5);
	}
	else if (usart == UART2){
		RCC->APB1ENR |= (1<< 17);
	gpio_init(PortA,2,OUT50,OUT_AF_PP);
	gpio_init(PortA,3,IN,IN_PUSHPULL);
	if(br == BR_9600){
		USART2->BRR = 0b111010100011; 
		
	}else if(br == BR_115200){
		USART2->BRR = 0b100111000; 

	}
	USART2->CR1 |= (1 << 3);
	USART2->CR1 |= (1 << 2);
	USART2->CR1 |= (1 << 13);
	USART2->CR1 |=(1 << 5);

	}
	else if (usart == UART3)
	{
	RCC->APB1ENR |= (1 << 18);
	gpio_init(PortB,10,OUT50,OUT_AF_PP);
	gpio_init(PortB,11,IN,IN_PUSHPULL);
	if(br == BR_9600){
		USART3->BRR = 0b111010100011; 
	}else if(br == BR_115200){
		USART3->BRR = 0b100111000;
	}
	USART3->CR1 |= (1 << 3);
	USART3->CR1 |= (1 << 2);
	USART3->CR1 |= (1 << 13);
	USART3->CR1 |=(1 << 5);
	}
}

void uart_tx(unsigned short usart, char c){
	if(usart == UART1)
		{
			while((USART1->SR & (1<<6)) == 0x00)
			{};
			USART1->DR = c;
		}
	else if(usart == UART2)
		{
			while((USART2->SR & (1<<6)) == 0x00)
			{};
			USART2->DR = c;
		}
		if(usart == UART3)
		{
			while((USART3->SR & (1<<6)) == 0x00)
			{};
			USART3->DR = c;
		}
}

char uart_rx(unsigned short usart)
{
	char c;
	if(usart == UART1)
		{
		while((USART1->SR & (1 << 5)) == 0x00)
		{};
		c = USART1->DR;
		}
	else if(usart == UART1)
		{
		while((USART2->SR & (1 << 5)) == 0x00)
		{};
		c = USART2->DR;
		}
		if(usart == UART1)
		{
		while((USART3->SR & (1 << 5)) == 0x00)
		{};
		c = USART3->DR;
		}
		return c;
}

void uart_send_msg(unsigned short uart, char str[])
{
	int i = 0;
	while(str[i] != '\0')
	{
		uart_tx(uart,str[i]);
		i++;
	}
}
