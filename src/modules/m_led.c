/**
 * @file m_led.c
 * @brief Implementation of the LED module.
 */

#include "m_led.h"

#include "hardware/clocks.h"
#include "hardware/pio.h"
#include <stdio.h>

#include "blink.pio.h"

static PIO pio = pio0;
static uint offset;

void blink_init(void) { offset = pio_add_program(pio, &blink_program); }

void blink_pin_forever(uint sm, uint pin, uint freq) {
  blink_program_init(pio, sm, offset, pin);
  pio_sm_set_enabled(pio, sm, true);
  const uint clock_freq_hz = clock_get_hz(clk_sys);

  printf("Blinking pin %d at %d Hz\n", pin, freq);

  // PIO counter program takes 3 more cycles in total than we pass as
  // input (wait for n + 1; mov; jmp)
  pio->txf[sm] = (clock_freq_hz / (2 * freq)) - 3;
}

// For more pio examples see
// https://github.com/raspberrypi/pico-examples/tree/master/pio