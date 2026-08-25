/**
 * @file m_spi.h
 * @brief Header file for the SPI module.
 */

#ifndef M_SPI_H
#define M_SPI_H

#include "pico/stdlib.h"

/**
 * @brief Initializes the SPI interface with a custom baud rate.
 * @param baudrate_Hz The desired baud rate for SPI communication in Hertz.
 */
void m_spi_init(uint baudrate_Hz);

#endif // M_SPI_H