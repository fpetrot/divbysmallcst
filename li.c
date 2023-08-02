#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*
 * Li, S. Y. (1985).
 * Fast constant division routines.
 * IEEE Transactions on Computers, 100(9), 866-869.
 * Implementation of the cookbook in C
 */

uint32_t divu3(uint32_t n)
{
   uint32_t x = n;
   x = (x << 2) + x + 5;
   x = (x >> 4) + x;
   x = (x >> 8) + x;
   x = (x >> 16) + x;
   x = (x >> 4);
   return x;
}

uint32_t divu5(uint32_t n)
{
   uint32_t x = n;
   x = (x << 1) + x + 3;
   x = (x >> 4) + x;
   x = (x >> 8) + x;
   x = (x >> 16) + x;
   x = (x >> 4);
   return x;
}

uint32_t divu7(uint32_t n)
{
   uint32_t x = n;
   x = x + 1;
   x = (x << 2) + (x >> 1);
   x = (x >> 6) + x;
   x = (x >> 24) + x;
   x = (x >> 5);
   return x;
}

uint32_t divu9(uint32_t n)
{
   uint32_t x = n, y;
   x = x + 1;
   x = (x << 1) + x + (x >> 1);
   x = (x >> 6) + x;
   x = (x >> 12) + x;
   x = (x >> 24) + x;
   x = (x >> 5);
   return x;
}

uint32_t divu11(uint32_t n)
{
   uint32_t x = n, y;
   x = x + 1;
   y = (x << 2) + x;
   x = y + (y >> 4) + (x >> 1);
   x = (x >> 10) + x;
   x = (x >> 20) + x;
   x = (x >> 6);
   return x;
}

uint32_t divu13(uint32_t n)
{
   uint32_t x = n;
   x = x + 1;
   x = (x << 2) + (x >> 1);
   x = x + (((x >> 1) + x) >> 4);
   x = (x >> 12) + x;
   x = (x >> 24) + x;
   x = (x >> 6);
   return x;
}

uint32_t divu15(uint32_t n)
{
   uint32_t x = n;
   x = x + 1;
   x = (x << 2) + (x >> 2);
   x = (x >> 8) + x;
   x = (x >> 16) + x;
   x = (x >> 6);
   return x;
}

uint32_t divu17(uint32_t n)
{
   uint32_t x = n;
   x = (x << 2) + x + 5;
   x = (x >> 1) + x;
   x = (x >> 8) + x;
   x = (x >> 16) + x;
   x = (x >> 7);
   return x;
}

uint32_t divu19(uint32_t n)
{
   uint32_t x = n;
   x = (x << 1) + x + 2;
   x = (x >> 3) + x;
   x = x - (x >> 9);
   x = (x >> 18) + x;
   x = (x >> 6);
   return x;
}

uint32_t divu21(uint32_t n)
{
   uint32_t x = n;
   x = (x << 1) + x + 3;
   x = (x >> 6) + x;
   x = (x >> 12) + x;
   x = (x >> 24) + x;
   x = (x >> 6);
   return x;
}

uint32_t divu23(uint32_t n)
{
   uint32_t x = n;
   x = x + 1;
   x = (((x >> 3) + x) >> 1) + x + (x << 2);
   x = (x >> 11) + x;
   x = (x >> 22) + x;
   x = (x >> 7);
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

uint32_t divu27(uint32_t n)
{
   uint32_t x = n, y;
   y = (x << 1) + x + 15;
   /* Typo in the paper, y was assigned */
   x = (y >> 2) + (x << 2);
   x = x - (x >> 9);
   x = (x >> 18) + x;
   x = (x >> 7);
   return x;
}

uint32_t divu29(uint32_t n)
{
   uint32_t x = n, y;
   y = (x >> 2) + (x << 2) + 3;
   y = (y >> 5) + y;
   x = (x >> 5) + y;
   x = x - (x >> 14);
   x = (x >> 28) + x;
   x = (x >> 7);
   return x;
}

uint32_t divu31(uint32_t n)
{
   uint32_t x = n;
   x = x + 1;
   x = (x << 2) + (x >> 3);
   x = (x >> 10) + x;
   x = (x >> 20) + x;
   x = (x >> 7);
   return x;
}

uint32_t divu33(uint32_t n)
{
   uint32_t x = n, y;
   x = x + 1;
   y = (x << 1) + x;
   y = (y >> 2) + y;
   x = (x >> 3) + y;
   x = (x >> 10) + x;
   x = (x >> 20) + x;
   x = (x >> 7);
   return x;
}

uint32_t divu35(uint32_t n)
{
   uint32_t x = n, y;
   x = x + 1;
   y = (x << 1) + x;
   x = (x >> 2) + y;
   x = (x >> 3) + x;
   x = (x >> 12) + x;
   x = (x >> 24) + x;
   x = (x >> 7);
   return x;
}

uint32_t divu37(uint32_t n)
{
   uint32_t x = n, y;
   x = (x << 2) + x + 4;
   y = (x >> 3) + x;
   y = (y >> 7) + y;
   x = (x >> 2) + y;
   x = x - (x >> 18);
   x = (x >> 8);
   return x;
}

uint32_t divu39(uint32_t n)
{
   uint32_t x = n, y;
   x = x + 1;
   y = (x << 1) + x;
   y = (x >> 2) + y;
   x = (x >> 5) + y;
   x = (x >> 12) + x;
   x = (x >> 24) + x;
   x = (x >> 7);
   return x;
}

uint32_t divu41(uint32_t n)
{
   uint32_t x = n, y;
   y = (x << 1) + x + 2;
   x = (x >> 3) + y;
   x = x - (x >> 10);
   x = (x >> 20) + x;
   x = (x >> 7);
   return x;
}

uint32_t divu43(uint32_t n)
{
   uint32_t x = n;
   x = (x << 1) + x + 2;
   x = x - (x >> 7);
   x = (x >> 14) + x;
   x = (x >> 28) + x;
   x = (x >> 7);
   return x;
}

uint32_t divu45(uint32_t n)
{
   uint32_t x = n, y;
   x = x + 1;
   y = (x << 2) + x;
   y = (y >> 3) + y;
   x = (x >> 4) + y;
   x = (x >> 12) + x;
   x = (x >> 24) + x;
   x = (x >> 8);
   return x;
}

uint32_t divu47(uint32_t n)
{
   uint32_t x = n;
   x = ((x + 9) >> 1) + x + (x << 2) - (x >> 4)
       + (((((((x >> 4) + x) >> 1) + x) >> 3) + x) >> 7);
   x = (x >> 23) + x;
   x = (x >> 8);
   return x;
}

uint32_t divu49(uint32_t n)
{
   uint32_t x = n;
   x = (x << 2) + x + 5 - (x >> 7) + (((x >> 4) + x) >> 2);
   x = (x >> 21) + x;
   x = (x >> 8);
   return x;
}

uint32_t divu51(uint32_t n)
{
   uint32_t x = n;
   x = (x << 2) + x + 5;
   x = (x >> 8) + x;
   x = (x >> 16) + x;
   x = (x >> 8);
   return x;
}

uint32_t divu53(uint32_t n)
{
   uint32_t x = n, y;
   x = x + 1;
   y = x + (x >> 9);
   y = (x << 2) + y;
   y = y + (y >> 6);
   y = (x >> 2) - y;
   y = (x >> 14) - y;
   y = y + (x >> 16);
   x = y + (x >> 18);
   x = x - (x >> 26);
   x = (x >> 8);
   return x;
}

uint32_t divu55(uint32_t n)
{
   uint32_t x = n, y;
   y = x - (x >> 3);
   y = x - (y >> 4) + 148;
   y = x + (y >> 2);
   y = x + (y >> 2);
   x = x + (y >> 3);
   x = (x >> 20) + x;
   x = (x >> 6);
   return x;
}

typedef struct checkdiv {
   uint32_t n;
    uint32_t (*fct)(uint32_t);
} checkdiv;

checkdiv tests[] = {
   /* Thanks vi macro: map q "ayy"ap0^A^Aw^A^A */
   {3, divu3},
   {5, divu5},
   {7, divu7},
   {9, divu9},
   {11, divu11},
   {13, divu13},
   {15, divu15},
   {17, divu17},
   {19, divu19},
   {21, divu21},
   {23, divu23},
   {25, divu25},
   {27, divu27},
   {29, divu29},
   {31, divu31},
   {33, divu33},
   {35, divu35},
   {37, divu37},
   {39, divu39},
   {41, divu41},
   {43, divu43},
   {45, divu45},
   {47, divu47},
   {49, divu49},
   {51, divu51},
   {53, divu53},
   {55, divu55},
};

int main(void)
{
   for (int j = 0; j < sizeof tests / sizeof *tests; j++) {
      uint32_t n = tests[j].n;
      uint32_t(*divu) (uint32_t) = tests[j].fct;
      fprintf(stderr, "Checking divu%d\n", n);
      for (uint32_t i = 0; i < 1000; i++) {
         uint32_t v = divu(i);
         /* print first number to overflow and then exits */
         if (v != i / n) {
            fprintf(stderr, "Error(%u:%f) : expects %u != has %u\n", i, (float) i / n, i / n, v);
            break;
         }
      }
   }
   return 0;
}
