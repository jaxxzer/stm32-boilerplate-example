#pragma once

#include <inttypes.h>

void usartInit(uint32_t usart, uint32_t baudrate);

void usartWrite(uint32_t usart, const char* string);
void usartRead(uint32_t usart, char* byte, uint16_t length);

void usartStartAutoBaud(uint32_t usart);

void usartEnableLineBreakDetection(uint32_t usart);
void usartLineBreakISREnable(uint32_t usart);
void usartLineBreakISRDisable(uint32_t usart);

void usartISR(uint32_t usart);
void usartLineBreakISR(uint32_t usart);
