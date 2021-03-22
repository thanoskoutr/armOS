/**
 * \ingroup peripherals
 * @file mbox.h
 * @brief Definition of Mailbox registers addresses
 * @details Mailboxes are a inter-processor communication mechanism between
 * the ARM cores and the VideoCore GPU.
 */

#ifndef P_MBOX_H
#define P_MBOX_H

#include <peripherals/base.h>

/**
 * \ingroup peripherals
 * The offsets for Mailbox registers (For raspi 3,4).
 */
enum
{
	MBOX_BASE    = (MMIO_BASE + 0xB880), /**< The base address for Mailbox registers */
	MBOX_READ    = (MBOX_BASE + 0x00),   /**< Reads messages from the GPU */
	MBOX_STATUS  = (MBOX_BASE + 0x18),   /**< Status for READ and WRITE registers */
	MBOX_WRITE   = (MBOX_BASE + 0x20)    /**< Writes messages to the GPU */
};

#endif