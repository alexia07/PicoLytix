/**
 * @file i2c.h
 * @brief Header file for I2C control functions.
 */

#ifndef I2C_H
#define I2C_H

#include "pico/stdlib.h"

/**
 * @brief Initializes the I2C interface with a custom baud rate.
 * @param baudrate_Hz The desired baud rate for I2C communication in Hertz.
 */
void i2c_init_custom(uint baudrate_Hz);

#endif // I2C_H