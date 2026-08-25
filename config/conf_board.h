/**
 * @file conf_board.h
 * @brief Board configuration header file.
 */

#ifndef CONF_BOARD_H
#define CONF_BOARD_H

#define UART_BAUD_RATE 115200
#define SPI_BAUD_RATE 1000000 // 1 MHz
#define I2C_BAUD_RATE 400000  // 400 kHz

#define WATCHDOG_TIMEOUT_MS (10 * 1000)

#endif // CONF_BOARD_H