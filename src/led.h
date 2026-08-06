/**
 * @file led.h
 * @brief Header file for LED control functions.
 */

#ifndef LED_H
#define LED_H

#include "pico/stdlib.h"

#define LED_PIN 25

void blink_init(void);
void blink_pin_forever(uint sm, uint pin, uint freq);

#endif // LED_H