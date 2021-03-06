/*
 * uart.h - Definition of basic UART functions
 */

#include <stddef.h>
#include <stdint.h>

#ifndef UART_H
#define UART_H

#define MBOX_CHANNELS 9

#ifdef AARCH_32
void mmio_write(uint32_t reg, uint32_t data);
uint32_t mmio_read(uint32_t reg);
#elif AARCH_64
void mmio_write(uint64_t reg, uint32_t data);
uint32_t mmio_read(uint64_t reg);
#endif

void delay(int32_t count);

extern volatile unsigned int __attribute__((aligned(16))) mbox[MBOX_CHANNELS];

void uart_init();

void uart_putc(unsigned char c);

unsigned char uart_getc();

void uart_puts(const char* str);


#endif