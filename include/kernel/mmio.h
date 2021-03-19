/**
 * @file mmio.h
 * @brief Definition of MMIO functions.
 * @details Reading and writing from/to Memory Mapped IO.
 */

#include <stdint.h>

#ifndef MMIO_H
#define MMIO_H

#ifdef AARCH_32
/**
 * Memory-Mapped I/O output
 * @param reg 32-bit register address
 * @param data 32-bit data
 * @details Writes the @a data value to the register at @a reg address.
*/
void mmio_write(uint32_t reg, uint32_t data);
/**
 * Memory-Mapped I/O input
 * @param reg 32-bit register address
 * @return 32-bit data
 * @details Reads register at @a reg address and returns its @a data.
*/
uint32_t mmio_read(uint32_t reg);

#elif AARCH_64
/**
 * Memory-Mapped I/O output
 * @param reg 64-bit register address
 * @param data 32-bit data
 * @details Writes the @a data value to the register at @a reg address.
*/
void mmio_write(uint64_t reg, uint32_t data);
/**
 * Memory-Mapped I/O input
 * @param reg 64-bit register address
 * @return 32-bit data
 * @details Reads register at @a reg address and returns its @a data.
*/
uint32_t mmio_read(uint64_t reg);
#endif

/**
 * Delays @a count of clock cycles.
 * @param count Number of cycles.
*/
void delay(int32_t count);

#endif