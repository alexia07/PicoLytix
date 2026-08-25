#include "hardware/i2c.h"
#include "pico/stdlib.h"
#include "unity.h"
#include <stdio.h>

/* ============================================================
   REQUIRED HOOKS: Unity calls these before/after every test
   ============================================================ */

void setUp(void) {
  // Reset state before each test
  // Example: gpio_state_reset();
}

void tearDown(void) {
  // Clean up after each test
  // Example: free_memory();
  // MUST exist even if empty!
}

/* ============================================================
   TEST CASES
   ============================================================ */

void test_gpio_mock_works(void) {
  printf("Running: test_gpio_mock_works\n");

  gpio_init(25);
  gpio_set_dir(25, true);
  gpio_put(25, true);

  bool state = gpio_get(25);

  TEST_ASSERT_TRUE(state);
}

void test_i2c_mock_works(void) {
  printf("Running: test_i2c_mock_works\n");

  uint8_t buffer[4];
  int result = i2c_read_blocking(&i2c0, 0x50, buffer, 4, false);

  TEST_ASSERT_EQUAL(4, result);
  TEST_ASSERT_EQUAL(0xAA, buffer[0]);
}

void test_clock_mock_works(void) {
  printf("Running: test_clock_mock_works\n");
  TEST_ASSERT_EQUAL(125000000, clock_get_hz(clk_sys));
}

/* ============================================================
   MAIN RUNNER
   ============================================================ */
int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_gpio_mock_works);
  RUN_TEST(test_i2c_mock_works);
  RUN_TEST(test_clock_mock_works);

  return UNITY_END();
}