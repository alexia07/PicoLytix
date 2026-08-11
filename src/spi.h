/**
 * @file spi.h
 * @brief Header file for SPI control functions.
 */

#ifndef SPI_H
#define SPI_H

#include "pico/stdlib.h"

/**
 * @brief Initializes the SPI interface with a custom baud rate.
 * @param baudrate_Hz The desired baud rate for SPI communication in Hertz.
 */
void spi_init_custom(uint baudrate_Hz);

#endif // SPI_H