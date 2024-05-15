#include "uart.h"

#define baudRate 115200

void UART_Init(void) {
	
    RCC->APB2ENR |= (1 << 14);
    GPIOA->CRH &= ~(GPIO_CRH_CNF9 | GPIO_CRH_MODE9);
		GPIOA->CRH |= (1 << (4 * (9 % 8)));

    GPIOA->CRH &= ~(GPIO_CRH_CNF10);
    GPIOA->CRH |= (1 << (4 * (10 % 8)));

    USART1->BRR = SystemCoreClock / baudRate;
    USART1->CR1 |= (1 << 3) | (1 << 2);
    USART1->CR1 |= (1 << 13);
}

void UART_SendChar(char ch) {
    while (!(USART1->SR & (1 << 7)));
    USART1->DR = (ch & 0xFF);
}

void UART_SendString(const char *str) {
    while (*str) {
        while (!(USART1->SR & (1 << 7))); 
        USART1->DR = (uint8_t)(*str++); 
    }
}

char UART_ReceiveChar(void) {
    while (!(USART1->SR & (1 << 5)));
    return (char)(USART1->DR & 0xFF);
}

void UART_ReceiveString(char *buffer, uint32_t bufferSize) {
    uint32_t i = 0;
    char receivedChar;

    while (i < (bufferSize - 1)) {
        receivedChar = UART_ReceiveChar();
        if (receivedChar == '\r' || receivedChar == '\n') {
            break;
        }
        buffer[i++] = receivedChar;
    }
    buffer[i] = '\0';
}
