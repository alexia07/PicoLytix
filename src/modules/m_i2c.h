/**
 * @file m_i2c.h
 * @brief Header file for the I2C module.
 */

#ifndef M_I2C_H
#define M_I2C_H

#include "pico/stdlib.h"

/**
 * @brief Initializes the I2C interface with a custom baud rate.
 * @param baudrate_Hz The desired baud rate for I2C communication in Hertz.
 */
void m_i2c_init(uint baudrate_Hz);

#endif // M_I2C_H