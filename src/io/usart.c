#include "usart.h"

#include <libopencm3/stm32/usart.h>

void usartInit(uint32_t usart, uint32_t baudrate)
{
    // enable transmitter + receiver
    USART_CR1(usart) |= USART_CR1_TE | USART_CR1_RE;
    usart_set_baudrate(usart, baudrate);
    usart_enable(usart);
}

void usartWrite(uint32_t usart, const char* string)
{
    int i = 0;
    uint8_t c = 0;
    do {
        c = string[i++];
        usart_send_blocking(usart, c);
    } while(c != 0);
}
