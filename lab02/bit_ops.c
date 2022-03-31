#include "bit_ops.h"
#include <limits.h>
#include <stdio.h>
// add something
// Return the nth bit of x.
// Assume 0 <= n <= 31
unsigned get_bit(unsigned x,
    unsigned n)
{
    return (x >> n) & 1;
}
// Set the nth bit of the value of x to v.
// Assume 0 <= n <= 31, and v is 0 or 1
void set_bit(unsigned* x,
    unsigned n,
    unsigned v)
{
    // get the mask that all bits are 1 expect the nth one
    // the nth one is v
    int mask = INT_MAX - ((v ^ 1) << n);
    *x = *x & mask;
    *x = *x | (v << n);
}
// Flip the nth bit of the value of x.
// Assume 0 <= n <= 31
void flip_bit(unsigned* x,
    unsigned n)
{
    set_bit(x, n, get_bit(*x, n) ^ 1);
}
