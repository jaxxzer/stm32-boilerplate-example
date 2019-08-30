#pragma once

#define USART_PERIPH USART1
#define USART_PERIPH_RCC RCC_USART1
#define USART_IRQ NVIC_USART1_IRQ

#define USART_GPIO_AF GPIO_AF1

#define USART_TX_GPIO_RCC RCC_GPIOA
#define USART_TX_GPIO GPIOA
#define USART_TX_GPIO_PIN GPIO9

#define USART_RX_GPIO_RCC RCC_GPIOA
#define USART_RX_GPIO GPIOA
#define USART_RX_GPIO_PIN GPIO10

#include <libopencm3/stm32/rcc.h>
void initializeSystemClocks() { rcc_clock_setup_in_hsi_out_48mhz(); }
