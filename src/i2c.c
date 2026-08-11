/**
 * @file i2c.c
 * @brief Implementation of I2C control functions.
 */

#include "hardware/i2c.h"
#include "hardware/gpio.h"

#include "../board/pico2.h"

void i2c_init_custom(uint baudrate_Hz) {
  i2c_init(I2C_PORT, baudrate_Hz);

  gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
  gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
  gpio_pull_up(I2C_SDA);
  gpio_pull_up(I2C_SCL);
  // For more examples of I2C use see
  // https://github.com/raspberrypi/pico-examples/tree/master/i2c
}