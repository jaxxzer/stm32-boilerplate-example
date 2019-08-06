#pragma once

#include <inttypes.h>

void usartInit(uint32_t usart, uint32_t baudrate);
void usartWrite(uint32_t usart, const char* string);
