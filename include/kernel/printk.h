/*
 * printk.h - Definition of printk
 * Prints a kernel message to the serial console
 */

#include <stdarg.h>

#ifndef PRINTK_H
#define PRINTK_H

/*
 * printk - print a kernel message
 * @fmt: format string
 * The formats supported by this implementation are: 'd' 'c' 's', 'x'.
 * To be supported: u', 'l', 'll'.
 */
int printk(const char *fmt, ...);


#endif