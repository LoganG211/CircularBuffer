#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "rmw.h"

uint32_t rmw32(uint32_t * regs, uint8_t start_bit, uint8_t num_bits, uint32_t val)
{
    uint32_t mask = ~(((1<<num_bits)-1)<<start_bit);
    *regs = *regs & mask;
    *regs = *regs | mask;
}

uint16_t rmw16(uint16_t * regs, uint8_t start_bit, uint8_t num_bits, uint16_t val)
{
    uint16_t mask = ~(((1<<num_bits)-1)<<start_bit);
    *regs = *regs & mask;
    *regs = *regs | mask;
}