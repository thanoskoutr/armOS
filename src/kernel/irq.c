/*
 * irq.h - Implementation of interrupt handling functions.
 *
 */

#include <stdint.h>
#include <kernel/printk.h>
#include <kernel/mmio.h>
#include <peripherals/irq.h>

#include <peripherals/aux.h>
#include <kernel/uart.h>

/*
 * String array, for the invalid exception type messages.
 */
const char entry_error_messages[16][32] = {
	"SYNC_INVALID_EL1t",
	"IRQ_INVALID_EL1t",
	"FIQ_INVALID_EL1t",
	"ERROR_INVALID_EL1T",

	"SYNC_INVALID_EL1h",
	"IRQ_INVALID_EL1h",
	"FIQ_INVALID_EL1h",
	"ERROR_INVALID_EL1h",

	"SYNC_INVALID_EL0_64",
	"IRQ_INVALID_EL0_64",
	"FIQ_INVALID_EL0_64",
	"ERROR_INVALID_EL0_64",

	"SYNC_INVALID_EL0_32",
	"IRQ_INVALID_EL0_32",
	"FIQ_INVALID_EL0_32",
	"ERROR_INVALID_EL0_32"
};

void enable_interrupt_controller()
{
	/* Enable System Timer 1 interrupts */
	// mmio_write(IRQ0_SET_EN_1, SYSTEM_TIMER_IRQ_1);

	/* Enable AUX interrupts (for mini UART) */
#if defined(MODEL_0) || defined(MODEL_2) || defined(MODEL_3)
	mmio_write(IRQ0_SET_EN_1, AUX_IRQ);
#elif defined(MODEL_4)
	mmio_write(IRQ0_SET_EN_0, AUX_IRQ);
#endif
}

#ifdef AARCH_32
#elif AARCH_64
void show_invalid_entry_message(int type, uint64_t esr, uint64_t address)
{
	printk("%s, ESR: %x, address: %x\n", \
			entry_error_messages[type], esr, address);
}
#endif

void handle_irq()
{
	/* Enable AUX interrupts (for mini UART) */
	uint32_t irq;

#if defined(MODEL_0) || defined(MODEL_2) || defined(MODEL_3)
	irq = mmio_read(IRQ0_PENDING_1);
#elif defined(MODEL_4)
	irq = mmio_read(IRQ0_PENDING_0);
#endif
	/* While we have a valid value from the interrupt */
	while (irq) {
		/* Check which interrupt is it */

		if (irq & SYSTEM_TIMER_IRQ_1) {
			/* Remove the bit we handled */
			irq &= ~SYSTEM_TIMER_IRQ_1;
		}
		if (irq & AUX_IRQ) {
			/* Remove the bit we handled */
			irq &= ~AUX_IRQ;
			handle_uart_irq();
		}
		else {
			printk("Unknown pending irq: %x\n", irq);
		}
	}
}