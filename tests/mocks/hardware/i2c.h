/**
 * @file i2c.h
 * @brief Mock header for the Pico SDK hardware/i2c.h, providing essential types
 * and functions for testing.
 */

#ifndef _HARDWARE_I2C_H
#define _HARDWARE_I2C_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef unsigned int uint;

typedef struct {
  int id;
} i2c_inst_t;

extern i2c_inst_t i2c0_inst;
extern i2c_inst_t i2c1_inst;

#define i2c0 (&i2c0_inst)
#define i2c1 (&i2c1_inst)

int i2c_read_blocking(i2c_inst_t *i2c, uint8_t addr, uint8_t *buf, size_t len,
                      bool nostop);
int i2c_write_blocking(i2c_inst_t *i2c, uint8_t addr, const uint8_t *src,
                       size_t len, bool nostop);

uint i2c_init(i2c_inst_t *i2c, uint baudrate);

#endif // _HARDWARE_I2C_H