/**
 * @file m_spi.c
 * @brief Implementation of the SPI module.
 */

#include "m_spi.h"

#include "hardware/gpio.h"
#include "hardware/spi.h"

#include "board/pico2.h"

void m_spi_init(uint baudrate_Hz) {
  spi_init(SPI_PORT, baudrate_Hz);
  gpio_set_function(SPI_MISO, GPIO_FUNC_SPI);
  gpio_set_function(SPI_CS, GPIO_FUNC_SIO);
  gpio_set_function(SPI_SCK, GPIO_FUNC_SPI);
  gpio_set_function(SPI_MOSI, GPIO_FUNC_SPI);

  // Chip select is active-low, so we'll initialise it to a driven-high state
  gpio_set_dir(SPI_CS, GPIO_OUT);
  gpio_put(SPI_CS, 1);
  // For more examples of SPI use see
  // https://github.com/raspberrypi/pico-examples/tree/master/spi
}