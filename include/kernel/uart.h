/*
 * uart.h - Definition of basic UART functions
 */

#ifndef UART_H
#define UART_H

void uart_init();

void uart_putc(unsigned char c);

unsigned char uart_getc();

void uart_puts(const char* str);

void handle_uart_irq();

#endif