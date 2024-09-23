#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "bitwise.h"

// Check if the chosen bit is set
int get_bit(uint32_t val, uint8_t bit)
{
    int rv;
    if(val & (1<<bit) > 0) {
        rv = 1;
    } else {
        rv = 0;
    }
    return rv;
}

// Set specific bit in value
void set_bit(uint32_t * val, uint8_t bit)
{
    *val = *val | (1<<bit);
}

// Clear a specific bit in value
void clear_bit(uint32_t * val, uint8_t bit)
{
    *val = *val & ~(1<<bit);
}

// Invert the value of a bit in value
void toggle_bit(uint32_t * val, uint8_t bit)
{
    // (1<<bit) XOR val
    *val = *val ^ (1<<bit);
}

// Get highest set bit of a val
uint8_t highest_bit(uint32_t val)
{
    uint8_t bit = 0;
    for(int i=0; i<32; i++) {
        if((val & (1<<i)) > 0) {
            bit = i;
        }
    }
    return bit;
}

// Get the lowest set bit of a val
uint8_t lowest_bit(uint32_t val)
{
    uint8_t bit = 0;
    for(int i=0; i<32; i++) {
        if((val & (1<<i)) > 0) {
            bit = i;
            return bit;
        }
    }
    return bit;
}

// Return the number of trailing zeros from val
uint8_t trailing_zeros(uint32_t val)
{
    uint8_t rv = 0;
    for(int i=0; i<32; i++) {
        if((val & (1<<i)) == 0) {
            rv++;
        } else {
            return rv;
        }
    }
    return rv;
}

// Return the number of leading zeros from val
uint8_t leading_zeros(uint32_t val)
{
    uint8_t rv = 0;
    for(int i=0; i<32; i++) {
        if((val & (1<<(31-i))) == 0) {
            rv++;
        } else {
            return rv;
        }
    }
    return rv;
}

// Return the number of 1 bits in val
uint8_t count_ones(uint32_t val)
{
    uint8_t one_count = 0;
    for(int i=0; i<32; i++) {
        if((val & (1<<i)) > 0) {
            one_count++;
        }
    }
    return one_count;
}

// Return the number of 0 bits in val
uint8_t count_zeros(uint32_t val)
{
    uint8_t zero_count = 0;
    for(int i=0; i<32; i++) {
        if((val & (1<<i)) == 0) {
            zero_count++;
        }
    }
    return zero_count;
}

// Rotate the val to the left by n bits
void rotate_val(uint32_t * val, uint8_t bits)
{
    for(int i=0; i<bits; i++) {
        if((*val & (1<<31)) > 0) {
            (*val<<1) | 1;
        } else {
            (*val<<1);
        }
    }
}

// Prints the binary of the val
void print_binary(uint32_t val)
{
    for(int i=0; i<32; i++) {
        if(val & (1<<(31-i)) > 0) {
            printf("1");
        } else {
            print("0");
        }
    }
    printf("\n");
}

// Swaps two numbers with bitwise operations
void bit_swap(uint32_t * num1, uint32_t * num2)
{
    //0101 1010
    *num1 ^= *num2; //num1 = 1111
    *num2 ^= *num1; //num2 = 0101
    *num1 ^= *num2; //num1 = 1010
}

// Will move MS 2 bytes behind the LS
void byte_swap(uint8_t * val)
{
    *val = ((*val << 8) & 0xff00) | ((*val >> 8) & 0x00ff);
}