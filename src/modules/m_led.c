/**
 * @file m_led.c
 * @brief Implementation of the LED module.
 */

#include "m_led.h"

#include "hardware/clocks.h"
#include "hardware/pio.h"
#include <stdio.h>

#include "blink.pio.h"
#include "board/pico2.h"

const uint8_t PIO_COMPENSATION = 3;
const uint8_t PIO_SM_COUNT = 4;

static struct context {
  PIO pio;
  uint32_t offset;
  bool is_initialized;
} context = {
    .pio = pio0,
    .offset = 0,
    .is_initialized = false,
};

error_t blink_init(void) {
  if (context.is_initialized) {
    printf("m_led: Warning: LED module already initialized.\n");
    return 0;
  }

  int rc = pio_add_program(context.pio, &blink_program);

  if (rc < 0) {
    printf("m_led: Error: Cannot add blink program at %p to PIO: %d\n",
           &blink_program, rc);
    return -EIO;
  }

  context.offset = (uint32_t)rc;
  context.is_initialized = true;
  return 0;
}

error_t blink_pin_forever(uint8_t sm, uint8_t pin, uint32_t freq_hz) {
  if (freq_hz == 0) {
    printf("m_led: Error: Frequency cannot be zero.\n");
    return -EINVAL;
  }

  if (!context.is_initialized) {
    printf(
        "m_led: Error: LED module not initialized. Call blink_init() first.\n");
    return -ENODEV;
  }

  if (pin >= NUM_GPIO) {
    printf("m_led: Error: Pin %u is out of range (0-%u).\n", pin, NUM_GPIO - 1);
    return -EINVAL;
  }

  blink_program_init(context.pio, sm, context.offset, pin);
  pio_sm_set_enabled(context.pio, sm, true);
  const uint32_t clock_freq_hz = clock_get_hz(clk_sys);

  if (clock_freq_hz == 0) {
    printf("m_led: Error: System clock frequency is zero.\n");
    return -EIO;
  }

  uint32_t ticks = (clock_freq_hz / (2 * freq_hz));
  if (ticks <= PIO_COMPENSATION) {
    printf("m_led: Error: Frequency %u Hz is too high for system clock "
           "frequency %u "
           "Hz.\n",
           freq_hz, clock_freq_hz);
    return -EINVAL;
  }

  printf("m_led: Blinking pin %u at %u Hz\n", pin, freq_hz);

  // PIO counter program takes 3 more cycles in total than we pass as
  // input (wait for n + 1; mov; jmp)
  pio_sm_put(context.pio, sm, ticks - PIO_COMPENSATION);

  if (sm >= PIO_SM_COUNT) {
    printf("m_led: Error: State machine %u is out of range (0-%d).\n", sm,
           PIO_SM_COUNT - 1);
    return -EINVAL;
  }
  return 0;
}

// For more pio examples see
// https://github.com/raspberrypi/pico-examples/tree/master/pio