#include "unity.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

/* ============================================================
   1. DEFINE MISSING TYPES (Mocking the Pico SDK Types)
   ============================================================ */

// Standard Pico types
typedef unsigned int uint;

// Mock Enums
typedef enum { clk_sys, clk_usb, clk_peri } clock_index_t;

typedef enum {
  GPIO_FUNC_SIO,
  GPIO_FUNC_SPI,
  GPIO_FUNC_I2C,
  GPIO_FUNC_UART,
  GPIO_FUNC_PIO0
} gpio_function_t;

// Mock Structs
typedef struct {
  int id;
} i2c_inst_t;

// Global mock instances
static i2c_inst_t i2c0_obj = {.id = 0};
static i2c_inst_t i2c1_obj = {.id = 1};

/* ============================================================
   2. MOCK VARIABLES (To track calls)
   ============================================================ */
static int mock_write_call_count = 0;
static int mock_read_call_count = 0;
static int mock_gpio_set_function_count = 0;

/* ============================================================
   3. MOCK IMPLEMENTATIONS (Fake Hardware Functions)
   ============================================================ */

int i2c_write_blocking(i2c_inst_t *i2c, uint8_t addr, const uint8_t *src,
                       size_t len, bool nostop) {
  mock_write_call_count++;
  printf("   [MOCK] i2c_write_blocking(addr: 0x%02X, len: %zu)\n", addr, len);
  return len; // Simulate success
}

int i2c_read_blocking(i2c_inst_t *i2c, uint8_t addr, uint8_t *buf, size_t len,
                      bool nostop) {
  mock_read_call_count++;
  printf("   [MOCK] i2c_read_blocking(addr: 0x%02X, len: %zu)\n", addr, len);
  return len; // Simulate success
}

void gpio_set_function(uint pin, gpio_function_t func) {
  mock_gpio_set_function_count++;
  // printf("   [MOCK] gpio_set_function(pin: %d, func: %d)\n", pin, func);
}

void gpio_pull_up(uint pin) {
  // Do nothing
}

uint32_t clock_get_hz(clock_index_t clk) {
  // Return a fake clock speed (125 MHz)
  return 125000000;
}

void sleep_ms(uint32_t ms) {
  // Do nothing (or use usleep if you want real delays)
}

/* ============================================================
   4. TEST CASES
   ============================================================ */

void setUp(void) {
  // Reset counters before each test
  mock_write_call_count = 0;
  mock_read_call_count = 0;
  mock_gpio_set_function_count = 0;
}

void tearDown(void) {
  // Nothing to clean up
}

void test_types_compile_correctly(void) {
  printf("Running: test_types_compile_correctly\n");

  // Verify our mock types work
  uint pin = 25;
  uint32_t freq = 1000000;

  TEST_ASSERT_EQUAL(25, pin);
  TEST_ASSERT_EQUAL(1000000, freq);
}

void test_mock_i2c_write(void) {
  printf("Running: test_mock_i2c_write\n");

  uint8_t data[] = {0x01, 0x02, 0x03};

  // Act
  int result = i2c_write_blocking(&i2c0_obj, 0x50, data, 3, false);

  // Assert
  TEST_ASSERT_EQUAL(3, result);
  TEST_ASSERT_EQUAL(1, mock_write_call_count);
}

void test_mock_clock_speed(void) {
  printf("Running: test_mock_clock_speed\n");

  uint32_t sys_clk = clock_get_hz(clk_sys);

  TEST_ASSERT_EQUAL(125000000, sys_clk);
}

/* ============================================================
   5. MAIN RUNNER
   ============================================================ */
int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_types_compile_correctly);
  RUN_TEST(test_mock_i2c_write);
  RUN_TEST(test_mock_clock_speed);

  return UNITY_END();
}