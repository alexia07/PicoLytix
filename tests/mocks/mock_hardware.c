/**
 * @file mock_hardware.c
 * @brief Mock implementations of Pico SDK hardware functions for unit testing.
 */

#include "hardware/clocks.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

// --- Global State ---
static bool gpio_state[30] = {0};

// --- GPIO Mocks ---
void gpio_init(uint pin) { (void)pin; }
void gpio_set_dir(uint pin, bool out) {
  (void)pin;
  (void)out;
}
void gpio_put(uint pin, bool value) {
  if (pin < 30)
    gpio_state[pin] = value;
}
bool gpio_get(uint pin) { return (pin < 30) ? gpio_state[pin] : false; }
void gpio_set_function(uint pin, gpio_function_t func) {
  (void)pin;
  (void)func;
}
void gpio_pull_up(uint pin) { (void)pin; }
void gpio_pull_down(uint pin) { (void)pin; }

// --- I2C Mocks ---

i2c_inst_t i2c0_inst = {.id = 0};
i2c_inst_t i2c1_inst = {.id = 1};

int i2c_write_blocking(i2c_inst_t *i2c, uint8_t addr, const uint8_t *src,
                       size_t len, bool nostop) {
  (void)i2c;
  (void)addr;
  (void)src;
  (void)nostop;
  return (int)len;
}

int i2c_read_blocking(i2c_inst_t *i2c, uint8_t addr, uint8_t *buf, size_t len,
                      bool nostop) {
  (void)i2c;
  (void)addr;
  (void)nostop;
  if (buf && len > 0)
    memset(buf, 0xAA, len);
  return (int)len;
}

uint i2c_init(i2c_inst_t *i2c, uint baudrate) {
  (void)i2c;
  return baudrate;
}

// --- Clocks Mocks ---
uint32_t clock_get_hz(clock_index_t clk) {
  if (clk == clk_sys)
    return 125000000;
  if (clk == clk_usb)
    return 48000000;
  return 0;
}

// --- Stdlib Mocks ---
void sleep_ms(uint32_t ms) { (void)ms; }
void panic(const char *fmt, ...) { (void)fmt; }