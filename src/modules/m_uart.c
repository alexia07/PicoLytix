/**
 * @file m_uart.c
 * @brief Implementation of the UART module.
 */

#include "m_uart.h"

#include "hardware/gpio.h"
#include "hardware/uart.h"
#include "pico/stdlib.h"
#include <stdio.h>

#include "board/pico2.h"
#include "config/conf_board.h"

static struct context {
  bool is_initialized;
} context = {
    .is_initialized = false,
};

error_t m_uart_init(void) {
  if (context.is_initialized) {
    printf("m_uart: Warning: UART module already initialized.\n");
    return -EALREADY;
  }

  uint32_t actual_baud_rate = uart_init(UART_ID, UART_BAUD_RATE);
  gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
  gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

  // Use some the various UART functions to send out data
  // In a default system, printf will also output via the default UART

  // Send out a string, with CR/LF conversions
  // uart_puts(UART_ID, " Hello, UART!\n");
  context.is_initialized = true;
  printf("m_uart: UART module initialized with baud rate %u.\n",
         actual_baud_rate);
  return 0;
}

// For more examples of UART use see
// https://github.com/raspberrypi/pico-examples/tree/master/uart