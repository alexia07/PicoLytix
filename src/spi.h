/**
 * @file spi.h
 * @brief Header file for SPI control functions.
 */

#ifndef SPI_H
#define SPI_H

#include "pico/stdlib.h"

/**
 * @brief Initializes the SPI interface with a custom baud rate.
 * @param baudrate The desired baud rate for SPI communication.
 */
void spi_init_custom(uint baudrate);

#endif // SPI_H