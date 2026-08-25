/**
 * @file m_led.h
 * @brief Header file for the LED module.
 */

#ifndef M_LED_H
#define M_LED_H

#include "errno.h"
#include "pico/stdlib.h"

/**
 * @brief Initializes the LED blinking program.
 * @return 0 on success, negative error code on failure.
 */
error_t blink_init(void);

/**
 * @brief Blinks a specified pin at a given frequency indefinitely.
 * @param sm The state machine to use for the PIO program.
 * @param pin The GPIO pin number to blink.
 * @param freq The frequency in Hz at which to blink the pin.
 * @return 0 on success, negative error code on failure.
 */
error_t blink_pin_forever(uint8_t sm, uint8_t pin, uint32_t freq_hz);

#endif // M_LED_H