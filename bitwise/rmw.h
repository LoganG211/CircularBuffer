#ifndef RMW_H
#define RMW_H

uint32_t rmw32(uint32_t * regs, uint8_t startbit, uint8_t numbits, uint32_t val);
uint16_t rmw16(uint16_t * regs, uint8_t start_bit, uint8_t num_bits, uint16_t val);

#endif