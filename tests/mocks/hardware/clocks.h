/**
 * @file clocks.h
 * @brief Mock header for the Pico SDK hardware/clocks.h, providing essential
 * types and functions for testing.
 */

#ifndef _HARDWARE_CLOCKS_H
#define _HARDWARE_CLOCKS_H

#include <stdint.h>

typedef enum { clk_sys, clk_ref, clk_usb, clk_peri } clock_index_t;

uint32_t clock_get_hz(clock_index_t clk);

#endif // _HARDWARE_CLOCKS_H