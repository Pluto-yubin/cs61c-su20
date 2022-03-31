#include "lfsr.h"
#include "bit_ops.h"
#include <bits/pthreadtypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void lfsr_calculate(uint16_t* reg)
{
    unsigned index0 = get_bit(*reg, 0);
    unsigned index2 = get_bit(*reg, 2);
    unsigned index3 = get_bit(*reg, 3);
    unsigned index5 = get_bit(*reg, 5);
    unsigned right = ((index0 ^ index2) ^ index3) ^ index5;
    *reg = *reg >> 1;
    (*reg) |= (right << 15);
    /* YOUR CODE HERE */
}
