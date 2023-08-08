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
     * Solution that overflows on 822.083.584, which is similar
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
    /* Same as above, but with only 5 additions,
     * which is better in SW. */
    uint32_t x = n;
    x = (x << 2) - (x >> 5) + 2;
    x = x + (x >> 2) + (((x >> 4) + x) >> 4);
    x = (x >> 21) + x;
    x = x >> 8;
    return x;
#endif
}

uint32_t rr, x;
uint32_t divu53(uint32_t n)
{
#if 0
    /*
     *                 11111111112222222222333
     *        12345678901234567890123456789012
     * 1/53 = 10011010100100001110011111010000
     */
    uint32_t x = n, y;
    y = x + (x >> 9);
    y = (x << 2) + y;
    y = y + (y >> 6) + 4;
    y = (x >> 2) - y;
    y = (x >> 14) - y;
    y = y + (x >> 16);
    x = y + (x >> 18);
    x = x - (x >> 26);
    x = (x >> 8);
#endif
    /*
     *                 11111111112222222222333
     *        12345678901234567890123456789012
     * 1/53 = 10011010100100001110011111010000
     *
     *                    11111111112222222222333
     *        21012345678901234567890123456789012
     * 1/53 = 10011010100100001110011111010000
     *        x x        x
     *              x x        x
     *          -
     *                        -
     */
#if 0
    uint32_t x = (n << 1) + 1, y, z;
    y = x + (x >> 9);
    y = (x << 2) + y;
    y = y + (y >> 6);

    y = (x >> 2) - y;
    y = (x >> 14) - y;
    y = y + (x >> 16);
    x = y + (x >> 18);
    x = x - (x >> 26);
    x = (x >> 8 >> 1);
#endif

#if 0
    /* Trying to shift the (y << 1) below but got
     * stucked with troncation at some point, ... */
    uint32_t x = n << 1, y, z;
    y = x + (x >> 9);
    y = (x << 1) + (y >> 1);
    y = y + (y >> 6);
    y = (x >> 3) - y;
    y = (x >> 15) - y;
    y = (y << 1) + 7;
    y = y + (x >> 16);
    x = y + (x >> 18);
    x = x - (x >> 26);
    x = (x >> 8 >> 1);
#endif

#if 0
    /*
     * Dumb version without trying factorization
     *      0b10011010100100001110011111011001
     *                 11111111112222222222333
     *        12345678901234567890123456789012
     * 1/53 = 10011010100100001110011111010000
     */
    uint32_t x = n;
    x = (x >> 1)
        + (x >> 4) + (x >> 5)
        + (x >> 7)
        + (x >> 9)
        + (x >> 12)
        + (x >> 17) + (x >> 18)  + (x >> 19)
        + (x >> 22) + (x >> 23)  + (x >> 24) + (x >> 25) + (x >> 26)
        + (x >> 28);
    x = (x >> 5);
#endif
#if 0
    uint32_t x = n, y, z;
    y = (x >> 4) + (x >> 5) + (x >> 7);
    z = ((x >> 10) - (x >> 13)) >> 6;
    x = (x >> 1) +
        + y + z + (z >> 5) + (y >> 21)
        + (x >> 9)
        + (x >> 12);
    x = (x >> 5);
#endif
#if 0
    /*
     * Dumb version without trying factorization
     *      0b10011010100100001110011111011001
     *                 11111111112222222222333
     *        12345678901234567890123456789012
     * 1/53 ~ 10011010100100001110011111010000
     */
 /* Error(222298112:4194304.000000) : expects 4194304 != has 0 */
    const uint32_t s = 2;
    uint32_t x = ((n + 1) << s);
    x = (x << 2)
        + (x >> 1)
        + (x >> 2)
        + (x >> 4)
        + (x >> 6)
        + (x >> 9)
        + (((x >> 0) - (x >> 3)) >> 13)
        + (((x >> 0) - (x >> 5)) >> 18)
        + (x >> 25)
        + (x >> 26);
    x = (x >> s);
    x = (x >> 8);
#endif
#if 0
    /* Error(889192448:16777216.000000) : expects 16777216 != has 0 */
    const uint32_t s = 2;
    uint32_t x = ((n + 1) << s), y;
    y = (x >> 1)
        + (x >> 2)
        + (x >> 4)
        + (x >> 6)
        + (x >> 9)
        + ((x - (x >> 3)) >> 13)
        + ((x - (x >> 5)) >> 18)
        + (x >> 25)
        + (x >> 26);
    x = x + (y >> s);
    x = (x >> 8);
#endif
#if 0
    /* Just inline the initial shift into the computation */
    uint32_t x = n + 1, y;
    y = (x << 1)
        + x
        + (x >> 2)
        + (x >> 4)
        + (x >> 7)
        + ((x - (x >> 3)) >> 11)
        + ((x - (x >> 5)) >> 16)
        + (x >> 23)
        + (x >> 24);
    x = (x << 2) + (y >> 2);
    x = (x >> 8);
#endif
#if 0
    /* Remove one add and one shift, barely enough, though:
     * still 11 adds and 12 shifts, not so bad for HW at least */
    uint32_t x = n + 1, y;
    y = (x << 1) + (x >> 2);
    y = x + y + (y >> 5);
    y = y
        + ((x - (x >> 3)) >> 11)
        + ((x - (x >> 5)) >> 16)
        + (x >> 23)
        + (x >> 24);
    x = (x << 2) + (y >> 2);
    x = (x >> 8);
#endif
#if 0
    /*
     *                     1111 1111 112 2222
     *       1012 3 4567 890123 4567 890 1234
     *       |||| | |||| |||||| |||| ||| ||||
     *   100 1101 0 1001 000011 1001 111 1011 000
     *       |||| | |||| |||||| |||| ||| ||||
     *       0123 4 5678 901234 5678 901 2345
     *       x00x   x00x        x00x     x00x
     *   y    y                            y
     *                       zz
     *                               ttt
     * Well, 12 adds and 13 shifts, even worse
     */
    uint32_t x = n + 1, y;
    y = (x << 1) + (x >> 2);
    y = y + (y >> 5) + (y >> 15) + (y >> 22);
    y = x + y + (x >> 12) + (x >> 13)
        + (((x - (x >> 3))) >> 17)
        + (x >> 23);
    x = (x << 2) + (y >> 2);
    x = (x >> 8);
#endif
    return x;
}

uint32_t divu7(uint32_t n)
{
    uint32_t x = n + 1;
    x = (x << 2) + (x >> 1);
    x = (x >> 6) + x;
    x = (x >> 12) + x;
    x = (x >> 24) + x;
    x = (x >> 5);
    return x;
}

uint32_t divu13(uint32_t n)
{
    uint32_t x = n + 1;
    x = (x << 2) + (x >> 1);
    x = x + (((x >> 1) + x) >> 4);
    x = (x >> 12) + x;
    x = (x >> 24) + x;
    x = (x >> 6);
    return x;
}
 
uint32_t divu81(uint32_t n)
{
    /*
     * 64/81 ~ .11001010010001011000011111100110
     *
     *                 11111111112222222222333
     *        12345678901234567890123456789012
     *        11001010010001011000011111100110
     *
     */
    uint32_t x = n, y;
    y = 6 + (x << 2) + (x << 1)
        + (x >> 13) + (x >> 14)
        + (x >> 27) + (x >> 28)

        + (x >> 2) + (x >> 4) + (x >> 7) + (x >> 11)
        + (x >> 19) + (x >> 20) + (x >> 21) + (x >> 22) + (x >> 23) + (x >> 24);
    x = (y >> 9);

    return x;
}
 

int main(int argc, char *argv[])
{
    for (uint32_t i = 0; i < 0xdeadbeef; i++) {
        uint32_t v = divu81(i);
        if (v != i/81) {
            fprintf(stdout, "Error(%8u:%f) : expects %u != has %u [%d](%u,%u)\n", i, i/81., i/81, v, rr);
        }
    }
    return 0;
}
