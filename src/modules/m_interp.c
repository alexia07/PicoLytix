/**
 * @file m_interp.c
 * @brief Implementation of the Interpolator module.
 *
 * This module provides functions to configure and use the hardware interpolator
 * on the Raspberry Pi Pico. The interpolator can be used for various
 * applications, such as signal processing, data interpolation, and more.
 */

#include "hardware/interp.h"
#include "pico/stdlib.h"
#include <stdio.h>

void m_interp_init(void) {
  // Interpolator example code
  interp_config cfg = interp_default_config();
  // Now use the various interpolator library functions for your use case
  // e.g. interp_config_clamp(&cfg, true);
  interp_config_set_shift(&cfg, 2);
  // Then set the config
  interp_set_config(interp0, 0, &cfg);
  // For examples of interpolator use see
  // https://github.com/raspberrypi/pico-examples/tree/master/interp
}