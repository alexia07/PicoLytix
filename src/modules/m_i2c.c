/**
 * @file m_i2c.c
 * @brief Implementation of the I2C module.
 */

#include "m_i2c.h"

#include "hardware/gpio.h"
#include "hardware/i2c.h"

#include "board/pico2.h"

void m_i2c_init(uint baudrate_Hz) {
  i2c_init(I2C_PORT, baudrate_Hz);

  gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
  gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
  gpio_pull_up(I2C_SDA);
  gpio_pull_up(I2C_SCL);
  // For more examples of I2C use see
  // https://github.com/raspberrypi/pico-examples/tree/master/i2c
}