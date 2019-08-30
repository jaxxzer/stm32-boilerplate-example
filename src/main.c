#include "io/usart.h"

#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/usart.h>

#include <target.h>

void usartLineBreakISR(uint32_t usart) {
    switch (usart) {
    case USART1:
    case USART2:
    default:
        usartStartAutoBaud(usart);
        break;
    }
}

void initUsart();

int main()
{
    initializeSystemClocks();

    initUsart();

    usartWrite(USART_PERIPH, "hello world\r\n");

    char c;

    while(1) {
        char c = usart_recv_blocking(USART_PERIPH);
        usart_send_blocking(USART_PERIPH, c);
    }

}

void initUsart()
{
    rcc_periph_clock_enable(USART_TX_GPIO_RCC);
    gpio_mode_setup(USART_TX_GPIO, GPIO_MODE_AF, GPIO_PUPD_NONE, USART_TX_GPIO_PIN);
    gpio_set_af(USART_TX_GPIO, USART_GPIO_AF, USART_TX_GPIO_PIN);

    rcc_periph_clock_enable(USART_RX_GPIO_RCC);
    gpio_mode_setup(USART_RX_GPIO, GPIO_MODE_AF, GPIO_PUPD_NONE, USART_RX_GPIO_PIN);
    gpio_set_af(USART_RX_GPIO, USART_GPIO_AF, USART_RX_GPIO_PIN);

    rcc_periph_clock_enable(USART_PERIPH_RCC);

    usartEnableLineBreakDetection(USART_PERIPH);

    usartInit(USART_PERIPH, 9600);

    nvic_enable_irq(USART_IRQ);

    usartLineBreakISREnable(USART_PERIPH);
}
