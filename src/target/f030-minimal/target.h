#pragma once

#include <libopencm3/stm32/usart.h>

#define USART_PERIPH USART2
#define USART_PERIPH_RCC RCC_USART2

#define USART_TX_GPIO_RCC RCC_GPIOA
#define USART_TX_GPIO GPIOA
#define USART_TX_GPIO_PIN GPIO2
#define USART_TX_GPIO_AF GPIO_AF1
