/**
 * @file m_uart.h
 * @brief Header file for the UART module.
 */

#ifndef M_UART_H
#define M_UART_H

#include "errno.h"

/**
 * @brief Initializes the UART module with the specified baud rate.
 * This function configures the UART interface, sets the TX and RX pins,
 * and prepares the UART for communication. It also checks if the UART module
 * has already been initialized to prevent re-initialization.
 * @return 0 on success, negative error code on failure.
 */
error_t m_uart_init(void);

#endif // M_UART_H