/*
 * mbox.h - Definition of Mailbox registers addresses
 * Mailboxes are a inter-processor communication mechanism between
 * the ARM cores and the VideoCore GPU.
 */

#ifndef P_MBOX_H
#define P_MBOX_H

#include "peripherals/base.h"

enum
{
	/* The offsets for Mailbox registers (For raspi 3,4) */
	MBOX_BASE    = (MMIO_BASE + 0xB880),
	MBOX_READ    = (MBOX_BASE + 0x00),
	MBOX_STATUS  = (MBOX_BASE + 0x18),
	MBOX_WRITE   = (MBOX_BASE + 0x20)
};

#endif