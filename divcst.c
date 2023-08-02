#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <assert.h>

/*
 * Implementation of division by small integer constants.
 * From :
 * Li, S. Y. (1985).
 * Fast constant division routines.
 * IEEE Transactions on Computers, 100(9), 866-869.
 */

uint32_t divu9(uint32_t n)
{
    uint32_t x = n;

    x = x + 1;
    x = (x << 1) + x + (x >> 1);
    x = (x >> 6) + x;
    x = (x >> 12) + x;
    x = (x >> 24) + x;
    x = (x >> 5);
    return x;
}

uint32_t divu25(uint32_t n)
{
    uint32_t x = n, y;

    y = x + 1;
    x = (y << 2) + x + (y >> 3);
    x = x - (x >> 10);
    x = (x >> 20) + x;
    x = (x >> 7);
    return x;
}

/* test to make sure I understood correctly */
uint32_t divu47(uint32_t n)
{
    uint32_t x = n;
    x = ((x + 9) >> 1) + x + (x << 2) - (x >> 4)
        + (((((((x >> 4) + x) >> 1) + x) >> 3) + x) >> 7);
    x = (x >> 23) + x;
    x = (x >> 8);
    return x;
}

/* Original algorithm fails */
uint32_t divu49(uint32_t n)
{
#if 0
    /* Li routine happens to fail, ... */
    uint32_t x = n;
    x = (x << 2) + x + 5 - (x >> 7) + (((x >> 4) + x) >> 2);
    x = (x >> 21) + x;
    x = (x >> 8);
    return x;
#endif
#if 0
    /*
     * Dumb version without trying factorization
     * 1/49 = (101001110010111100000)*
     */
    uint32_t x = n;
    x = (x >> 1) + (x >> 3)
        + (x >> 6) + (x >> 7) + (x >> 8)
        + (x >> 11)
        + (x >> 13) + (x >> 14)  + (x >> 15) + (x >> 16);
    x = x + (x >> 21);
    x = (x >> 5);
    uint32_t r = n - ((((x << 1) + x) << 4) + x);
    return x + (r > 48);
#endif
#if 0
    uint32_t x = n;
    x = x * 337;
    x = x * 127;
    x = (x >> 21) + x;
    x = (x >> 8);
    x = (x >> 5);
    return x;
#endif
#if 0
    /* This works, but only with 64 bits, which is overkill */
    uint64_t x = n + 1, y;
    x = (x << 2) + x + (((x >> 4) + x) >> 2);
    x = (x << 7) - x;
    x = (x >> 5);
    x = (x >> 21) + x;
    x = (x >> 10);
    return x;
#endif
#if 0
    /* This works on 32 bit but fails a bit early */
    uint32_t x = n + 1;
    x = ((x << 7) - x) >> 5;
    x = (x << 2) + x + (((x >> 4) + x) >> 2);
    x = (x >> 21) + x;
    x = (x >> 10);
    return x;
#endif
#if 0
    /*
     * Solution that overflows on 82.208.3584, which is similar
     * to the divide 47 that Li proposes.
     * 6 additions, but 2 with 1, which makes it 4 in HW.
     */
    uint32_t x = n;
    x = (x << 2) - (x >> 5) + 1;
    x = x + (x >> 2) + (((x >> 4) + x) >> 4) + 1;
    x = (x >> 21) + x;
    x = x >> 8;
    return x;
#endif
#if 1
    /* Same as above, but with only 5 additions, this time with 3
     * which is better in SW. */
    uint32_t x = n;
    x = (x << 2) - (x >> 5) + 3;
    x = x + (x >> 2) + (((x >> 4) + x) >> 4);
    x = (x >> 21) + x;
    x = x >> 8;
    return x;
#endif
}

int main(int argc, char *argv[])
{
    for (uint32_t i = 0; i < 0xdeadbeef; i++) {
        uint32_t v = divu49(i);
        if (v != i/49) {
            fprintf(stderr, "Error(%u:%f) : expects %u != has %u\n", i, i/49., i/49, v);
        }
    }
    return 0;
}
