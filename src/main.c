#include "io/usart.h"

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>

#include <target.h>

void initUsart();

int main()
{
    initUsart();

    while(1) {
        usartWrite(USART_PERIPH, "hello world\r\n");
    }

}

void initUsart()
{
    rcc_periph_clock_enable(USART_TX_GPIO_RCC);

    gpio_mode_setup(USART_TX_GPIO, GPIO_MODE_AF, GPIO_PUPD_NONE, USART_TX_GPIO_PIN);

    gpio_set_af(USART_TX_GPIO, USART_TX_GPIO_AF, USART_TX_GPIO_PIN);

    rcc_periph_clock_enable(USART_PERIPH_RCC);

    // higher clock speed setup necessary for faster baudrates
    usartInit(USART_PERIPH, 9600);
}
