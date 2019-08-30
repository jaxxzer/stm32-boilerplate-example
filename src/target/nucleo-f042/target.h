#pragma once

#define USART_PERIPH USART1
#define USART_PERIPH_RCC RCC_USART1
#define USART_IRQ NVIC_USART1_IRQ

#define USART_GPIO_AF GPIO_AF1

// built-in stlink VCP is on USART2 PA2 (TX) and PA15 (RX)
// but it does not have LIN support needed for break detection
#define USART_TX_GPIO_RCC RCC_GPIOA
#define USART_TX_GPIO GPIOA
#define USART_TX_GPIO_PIN GPIO9

#define USART_RX_GPIO_RCC RCC_GPIOA
#define USART_RX_GPIO GPIOA
#define USART_RX_GPIO_PIN GPIO10
