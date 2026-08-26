/**
 * @file gpio.h
 * @brief Mock header for the Pico SDK hardware/gpio.h, providing essential
 * types and functions for testing.
 */

#ifndef _HARDWARE_GPIO_H
#define _HARDWARE_GPIO_H

#include "common.h"
#include <stdbool.h>
#include <stdint.h>

typedef enum {
  GPIO_FUNC_SIO = 0,
  GPIO_FUNC_SPI = 1,
  GPIO_FUNC_I2C = 2,
  GPIO_FUNC_UART = 3,
  GPIO_FUNC_PIO0 = 5,
  GPIO_FUNC_NULL = 0x1F
} gpio_function_t;

enum gpio_override {
  GPIO_OVERRIDE_NORMAL = 0,
  GPIO_OVERRIDE_INVERT = 1,
  GPIO_OVERRIDE_LOW = 2,
  GPIO_OVERRIDE_HIGH = 3
};

// Function prototypes
void gpio_init(uint pin);
void gpio_set_dir(uint pin, bool out);
void gpio_put(uint pin, bool value);
bool gpio_get(uint pin);
void gpio_set_function(uint pin, gpio_function_t func);
void gpio_pull_up(uint pin);
void gpio_pull_down(uint pin);

#endif // _HARDWARE_GPIO_H