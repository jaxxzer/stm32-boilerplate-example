#include "usart.h"

#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/vector.h>
#include <libopencm3/stm32/usart.h>

void usart1_isr()
{
    usartISR(USART1);
}

void usart2_isr()
{
    usartISR(USART2);
}

void usartISR(uint32_t usart)
{
    if (USART_ISR(usart) & USART_ISR_LBDF) {
        usartLineBreakISR(usart);
        USART_ICR(usart) |= USART_ICR_LBDCF;
    }
}

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

void usartRead(uint32_t usart, char* byte, uint16_t length) {

    while(length--) {
      *byte++ = usart_recv_blocking(usart);
    }
}

void usartStartAutoBaud(uint32_t usart) {
    USART_CR2(usart) |= USART_CR2_ABREN;

    // this next write is necessary to trigger subsequent autobaudrate sequences
    // it is not strictly necessary for the first autodetection sequence,
    // but it doesn't hurt

    // aaayyy wtf the datasheet autobaudrate functional description says do this
    // USART_ISR(usart) &= ~USART_ISR_ABRF;

    // the register description for USART_ISR_ARBF says do this
    USART_RQR(usart) |= USART_RQR_ABKRQ;
}

// note the usart must support lin mode
// these bits can only be written when usart is disabled (UE = 0)
void usartEnableLineBreakDetection(uint32_t usart)
{
    USART_CR2(usart) |= USART_CR2_ABRMOD_FRAME_0x55 | USART_CR2_LBDL | USART_CR2_LINEN;
}

void usartLineBreakISREnable(uint32_t usart) {
    USART_CR2(usart) |= USART_CR2_LBDIE;
}

void usartLineBreakISRDisable(uint32_t usart) {
    USART_CR2(usart) &= ~USART_CR2_LBDIE;
}
