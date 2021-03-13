/*
 * uart.h - Definition of basic UART functions
 */

#ifndef UART_H
#define UART_H

#define MAX_INPUT_LENGTH 80

void uart_init();

void uart_putc(unsigned char c);

unsigned char uart_getc();

void uart_puts(const char* str);

char *uart_gets();

void handle_uart_irq();

#endif