/*
 * mmio.h - Definition of functions for:
 * reading and writing from/to Memory Mapped IO
 */

#include <stdint.h>

#ifndef MMIO_H
#define MMIO_H

#ifdef AARCH_32
void mmio_write(uint32_t reg, uint32_t data);
uint32_t mmio_read(uint32_t reg);

#elif AARCH_64
void mmio_write(uint64_t reg, uint32_t data);
uint32_t mmio_read(uint64_t reg);
#endif

void delay(int32_t count);

#endif