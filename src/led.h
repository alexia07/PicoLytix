/**
 * @file led.h
 * @brief Header file for LED control functions.
 */

#ifndef LED_H
#define LED_H

#include "pico/stdlib.h"

/**
 * @brief Initializes the LED blinking program.
 */
void blink_init(void);

/**
 * @brief Blinks a specified pin at a given frequency indefinitely.
 * @param sm The state machine to use for the PIO program.
 * @param pin The GPIO pin number to blink.
 * @param freq The frequency in Hz at which to blink the pin.
 */
void blink_pin_forever(uint sm, uint pin, uint freq);

#endif // LED_H