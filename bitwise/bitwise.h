#ifndef BITWISE_H
#define BITWISE_H

// Contains references to all chosen bitwise functions

void set_bit(uint32_t * val, uint8_t bit);
void clear_bit(uint32_t * val, uint8_t bit);
void toggle_bit(uint32_t * val, uint8_t bit);
uint8_t highest_bit(uint32_t val);
uint8_t lowest_bit(uint32_t val);
uint8_t trailing_zeros(uint32_t val);
uint8_t leading_zeros(uint32_t val);
uint8_t count_ones(uint32_t val);
uint8_t count_zeros(uint32_t val);
void rotate_val(uint32_t * val, uint8_t bits);
void print_binary(uint32_t val);
void bit_swap(uint32_t * num1, uint32_t * num2);
void byte_swap(uint8_t * val);

#endif