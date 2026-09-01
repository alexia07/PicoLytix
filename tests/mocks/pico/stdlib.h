/**
 * @file stdlib.h
 * @brief Mock header for the Pico SDK stdlib.h, providing essential types and
 * functions for testing.
 */

#ifndef TESTS_PICO_STDLIB_H
#define TESTS_PICO_STDLIB_H

#include "hardware/clocks.h"
#include "hardware/gpio.h"
#include <stdbool.h>
#include <stdint.h>

// Common functions (declared here, implemented in mock_hardware.c)
void sleep_ms(uint32_t ms);
void panic(const char *fmt, ...);

#endif // TESTS_PICO_STDLIB_H