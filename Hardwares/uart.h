#ifndef UART_H
#define UART_H

#include "stm32f10x.h"

void UART_Init(void);
void UART_SendChar(char ch);
void UART_SendString(const char *str);
char UART_ReceiveChar(void);
void UART_ReceiveString(char *buffer, uint32_t bufferSize);

#endif
