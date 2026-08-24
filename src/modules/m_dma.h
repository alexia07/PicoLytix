/**
 * @file m_dma.h
 * @brief Header file for the DMA module.
 */

#ifndef M_DMA_H
#define M_DMA_H

#include "errno.h"

/**
 * @brief Initializes the DMA module and performs a simple data transfer.
 * This function claims a DMA channel, configures it for an 8-bit transfer from
 * a source buffer to a destination buffer, and waits for the transfer to
 * complete. It prints the contents of the destination buffer after the
 * transfer.
 * @return 0 on success, negative error code on failure.
 */
error_t m_dma_init(void);

#endif // M_DMA_H