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
     * This is an approximation of 32/49 with
     * (((1/32+1/128+1/512+1/8192)*127)
     * + ((1/32+1/128+1/512+1/8192)*127/(2^21)))/8
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

/*
 * 64/81 ~ .11001010010001011000011111100110
 *
 *          decimal: 106048575 = 3³×5²×157109
 *          157108 = 2²×7×31×181
 *          180 = 2²×3²x5
 *
 *                   11111111112222222222333
 *          12345678901234567890123456789012
 *          110010100100010110000111111-----
 *          1000101  1000101
 *           1              1
 *                              1 -   1
 *
 *                   11111111112222222222333
 *          12345678901234567890123456789012
 *          ||||||||||||||||||||||||||||||||
 *          110010100100010110000111111-----
 *
 *          001101011011101001111000000-----
 */
uint32_t divu81(uint32_t n)
{
    uint32_t x = n, y;
    y = (x >> 1) + (x >> 5) + (x >> 7);
    x = y + (y >> 9)
        + (x >> 2) + (x >> 17)
        + ((x - (x >> 6)) >> 21);
    x = (x >> 6);

    uint32_t r = n - (x << 6) - (x << 4) - x;

    return x + (r > 80);
}

int32_t divs81(int32_t n)
{
    /*
     * Same approach as with div, but substract n-1 before
     * rounding towards 0
     */
    int32_t x = n, y;

    x = x + (x >> 31 & 80);
    y = (x >> 1) + (x >> 5) + (x >> 7);
    x = y + (y >> 9)
        + (x >> 2) + (x >> 17)
        + ((x - (x >> 6)) >> 21);
    x = (x >> 6);

    int32_t r = n - (x << 6) - (x << 4) - x;

    rr = r;

    /*
     * Condition is kind of a hack deduced by observing when the
     * cases that fail.
     * FIXME: understand that and simplify the expression.
     * Harder than the expected x + (r > 80)
     */
    return x - (r < -80) + (r > 80) + (r > 0 && n < 0);
}

/*
 * 64/121 ~ .10000111011001111010101101011111
 * works for 32 bits: .10000111011001111010101101
 * decimal: 35495597
 *
 *           11111111112222222222333
 *  12345678901234567890123456789012
 *  ||||||||||||||||||||||||||||||||
 * .10000111011001111010101101------
 *         101      101 101101
 *       111111  111111 111111
 *  1       0        0   0  0
 */
uint32_t divu121(uint32_t n)
{
    uint32_t x = n, y;
#if 0
    /* Simple version simply using the strides of ones:
     * 11 adds and 12 shifts */
    x = (x >> 1)
        + ((x - (x >> 3)) >> 5)
        + (x >> 10) + (x >> 11)
        + ((x - (x >> 4)) >> 13)
        + (x >> 19)
        + (x >> 21)
        + (x >> 23)
        + (x >> 24)
        + (x >> 26);
    x = (x >> 6);

    uint32_t r = n - (x << 7) + (x << 3) - x;
    return x + (r > 120);
#elif 0
    /* Version seeking for repetitive 101 patterns:
     * 10 adds and 12 shifts */
    y = (x >> 1) + (x >> 3);
    y = (y >> 7) + (y >> 16) + (y >> 20) + (y >> 23);
    x = y
        + (x >> 1)
        + (x >> 6) + (x >> 7)
        + (x >> 11)
        + ((x - (x >> 3)) >> 13);
    x = (x >> 6);

    uint32_t r = n - (x << 7) + (x << 3) - x;
    return x + (r > 120);
#else
    /* Version with 111111 pattern and subs, essentially:
     * 8 adds and 9 shifts, but needs a more complex adjustment,
     * one shift and one add.
     * Still better than the previous version, though. */
    y = (x - (x >> 6));
    y = (y >> 5) + (y >> 13) + (y >> 20);
    x = y
        + (x >> 1)
        - (x >> 9)
        - (x >> 18)
        - (x >> 22)
        - (x >> 25);
    x = (x >> 6);

    int32_t r = n - (x << 7) + (x << 3) - x;
    x += (r > 120) + (r >> 31);
    return x;
#endif
}

int32_t divs121(int32_t n)
{
    int32_t x = n + (n >> 31 & 120);
#if 0
    x = (x >> 1)
        + (x >> 6) + (x >> 7) + (x >> 8)
        + (x >> 10) + (x >> 11)
        + (x >> 14) + (x >> 15) + (x >> 16) + (x >> 17)
        + (x >> 19)
        + (x >> 21)
        + (x >> 23)
        + (x >> 24)
        + (x >> 26);
#else
    int32_t y;
    y = (x - (x >> 6));
    y = (y >> 5) + (y >> 13) + (y >> 20);
    x = y
        + (x >> 1)
        - (x >> 9)
        - (x >> 18)
        - (x >> 22)
        - (x >> 25);
#endif
    x = (x >> 6);

    int32_t r = n - (x << 7) + (x << 3) - x;
    rr = r;

    /* Yet another adjustment, very dependent from the truncations
     * that occur, I am afraid. */
    return x + (r > 120) - (r < 0 && n > 0) - (r < -120) + (r > 0 && n < 0);
}

/*
 * 128/169 ~ .11000001111001001011101111010101
 *   decimal : 25414007
 *
 *            11111111112222222222333
 *   12345678901234567890123456789012
 *   ||||||||||||||||||||||||||||||||
 *  .1100000111100100101110111-------
 *   0011111000011011010001000
 */
uint32_t divu169(uint32_t n)
{
    uint32_t x = n, y;
#if 0
    x = (x >> 1) + (x >> 2)
        + (x >> 8) + (x >> 9) + (x >> 10) + (x >> 11)
        + (x >> 14)
        + (x >> 17)
        + (x >> 19) + (x >> 20) + (x >> 21)
        + (x >> 23) + (x >> 24) + (x >> 25);
#elif 0
    y = (x - (x >> 3));
    x = (x >> 1) + (x >> 2)
        + ((x >> 7) - (x >> 11))
        + (x >> 14)
        + (x >> 17)
        + (y >> 18)
        + (y >> 22);
#else
    y = ((x >> 2) - (x >> 7))
        + ((x >> 11) - (x >> 18))
        + (x >> 22)
        - (x >> 14)
        - (x >> 17);
    x = ~y;
#endif
    x = (x >> 7);

    uint32_t r = n - x * 169;
    return x + (r > 168);
}

/*
 * 32/49 ~ .10100111001011110000010100111
 *   decimal : 350609575
 *
 *            11111111112222222222333
 *   12345678901234567890123456789012
 *   ||||||||||||||||||||||||||||||||
 *  .10100111001011110000010100111---
 *  .1010011100101111
 *   101  101  101101
 *         1       1
 */
uint32_t divx49(uint32_t n)
{
    uint64_t x = n, y;
#if 0
    y = (x >> 1)
        + (x >> 3)
        + (x >> 6)
        + (x >> 7)
        + (x >> 8)
        + (x >> 11)
        + (x >> 13)
        + (x >> 14)
        + (x >> 15)
        + (x >> 16);
    x = y + (y >> 21);
    x = (x >> 5);
#elif 0
    y = (x >> 1) + (x >> 3);
    x = y + (y >> 5) + (y >> 10) + (y >> 13)
        + (x >> 7)
        + (x >> 15);
    x = x + (x >> 21);
    x = (x >> 5);
#else
    x = (x << 2) - (x >> 5) + 1;
    x = x + (x >> 2) + (((x >> 4) + x) >> 4) + 1;
    x = (x >> 21) + x;
    x = x >> 8;
    return x;
#endif

    uint32_t r = n - x * 49;
    return x + (r > 48);
}

int main(int argc, char *argv[])
{
#if 1
    uint32_t i = 0xffffffff;
    do {
        i++;
        int32_t v = divx49(i);

        if (v != i/49) {
            fprintf(stdout, "%s(%8d:%f) : expects %d != has %d [%d]\n", v != i/49 ? "Error" : "     ", i, i/49., i/49, v, rr);
        }
        if (i == 2147483647) {
            printf("----------------------------------------------------\n");
        }
    } while (i < 0xffffffff);
#endif

#if 0
    uint32_t j = 0xffffffff;
    do {
        int32_t i = (int32_t)++j;
        int32_t v = divs121(i);

        if (v != i/121) {
            fprintf(stdout, "%s(%8d:%f) : expects %d != has %d [%d]\n", v != i/121 ? "Error" : "     ", i, i/121., i/121, v, rr);
        }
        if (j == 2147483647) {
            printf("----------------------------------------------------\n");
        }
    } while (j < 0xffffffff);
#endif

    return 0;
}
