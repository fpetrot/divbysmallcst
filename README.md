# Dividing integers by small constants

This repository provides an implementation in C of the
routines given in the paper: 

<cite>Li, S. Y. (1985). Fast constant division routines.
IEEE Transactions on Computers, 100(9), 866-869.</cite>

It uses shifts and add to perform division, based on the
reciprocical of the divisor, following a trial and error
approch to minimize the number of shifts and adds.
The file `binrecip.bc` computes that value using `bc`.

As explained in the paper these implementations overflow
more or less when the dividend is such that bit 30 is set.
This is due to the fact that no remainder is calculated,
which at the end of the day eats 2 bits.
Typically, all routines start with `x = (x << 2) + ...`.

Exact routines can be extracted form these ones, with a
correcting step as explained in Section 10-10 of
Hacker's Delight.
It boils down to not shift left at all and computing the
excessive truncature, using again shift and add to multiply.

This might be useful for software, but as far as hardware is
concerned, just adding three upper bits is certainly a better
solution, as the adders will only slightly increase and
this will spare the correction step, which requires
usually 3 or 4 full fledge adders.

Some of the routines in the paper are not "always" working,
they are off by one when the division is exact, mainly.
I have enclosed them in preprocessor directives that are
not activated by default, and I give the corrected versions
that I came up with, often using one more shift and add.
The routines have been exhaustively tested for 32-bit
`uint32_t` until they overflow. 
This amounts to less than two minutes for all of them on
my laptop (which was not Li's situation in 1985).

Runtimes on x86 compared to using a multiply high and a
correction is about 2x, ..., and this is exact for all
integers.
Then, on your computer just use your compiler and your all set!

However, when it comes to specialized implementations,
such as tiny processors without multiplier (these beasts
exist) or dedicated hardware in which shifts by constants
are free, or lack of DSPs on your FPGA, this approach might
prove useful.

The important file is `li.c` that contains the cookbook,
and the function `checkall` that checks it all, assuming
the host processor divider is correct.

I've translated the routines in verilog hdl and thanks to
a few scripts, verified them all using Verilator, that is
pretty fast on these simple stuffs, and synthesized them
using AMD's Vivado for the Virtex7.
The routines for 3, 5, 11 and 23 have been extended to 64
bits to be compared with other division by constant
proposals.

Hopefully, this might be reported in a paper one of these
days, ...

Good news: the paper I've written on the subject has been accepted as
a short contribution to the ARITH'2025 conference!
Thanks to the arithmetic community for its openness, as I am by no
mean an arithmetitian.

I've added a li64.c file that extends the routines to 64 bits and
unfortunately a few of them fail much before 2^61 because of truncation,
so there is still work to do for larger dividend size.

To compile for 64 bits:

    gcc -O3 li64.c -o li64 -Dloop=10000 -lm

The check is not exhaustive, but randomized, it gives, for a given
run, the following results:

    Checking divu3
    Error @ 0x4f7e61c7d4871684 (5728123286953858692:1909374509400457216.000000) : expects 1909374428984619564 != has 679591490737316123
    Checking divu5
    Error @ 0x213d0ea30aa46874 (2395086670251976820:479017358925496320.000000) : expects 479017334050395364 != has 479017334050395363
    Checking divu7
    Error @ 0x57371ab2d6ac18b2 (6284521160426920114:897788696193925120.000000) : expects 897788737203845730 != has 312177814228939330
    Checking divu9
    Error @ 0x4bae6f6165ac8b4e (5453418662900566862:605935429228691456.000000) : expects 605935406988951873 != has 20324484014045473
    Checking divu11
    Error @ 0x4c8be8b41606cc0c (5515758028806605836:501432518365413376.000000) : expects 501432548073327803 != has 194888413906111403
    Checking divu13
    Error @ 0x4108c484b812a524 (4686211486581957924:360477807744122880.000000) : expects 360477806660150609 != has 45148848135201009
    Checking divu15
    Error @ 0x4feed52d55c195b2 (5759775364142437810:383985022748590080.000000) : expects 383985024276162520 != has 94624332923855828
    Checking divu17
    Error @ 0x3411a40f681252f6 (3751960350653829878:220703543114334208.000000) : expects 220703550038460581 != has 3683031524230562
    Checking divu19
    Error @ 0x542205e5d61a5f54 (6062414533091811156:319074460449636352.000000) : expects 319074449110095324 != has 31405925543474636
    Checking divu21
    Error @ 0x8039d882919e093c (9239654165827684668:439983562268082176.000000) : expects 439983531706080222 != has 147178070218627022
    Checking divu23
    Error @ 0x3c02468d34b1c5e4 (4324096164517496292:188004170383491072.000000) : expects 188004181065978099 != has 43818589869420783
    Checking divu25
    Error @ 0x3b213ada833764b8 (4260751432647926968:170430057561456640.000000) : expects 170430057305917078 != has 26455469413549846
    Checking divu27
    Error @ 0x417633b86f985dd2 (4717014526956428754:174704237215744000.000000) : expects 174704241739126990 != has 30869979955816646
    Checking divu29
    Error @ 0x  18f557428949ff (7025154568309247:242246708363264.000000) : expects 242246709252043 != has 242246709252042
    Checking divu31
    Error @ 0x6d3d9a1c0c17ec12 (7871617168966151186:253923122284068864.000000) : expects 253923134482779070 != has 109667071345265470
    Checking divu33
    Error @ 0x4eb47c718302c964 (5671294657737443684:171857412632870912.000000) : expects 171857413870831626 != has 27601350733318026
    Checking divu35
    Error @ 0x   1e9421e2ea63a (537945160197690:15369861332992.000000) : expects 15369861719934 != has 15369861719933
    Checking divu37
    Error @ 0x3dfd0254a212da2c (4466728967941052972:120722399590088704.000000) : expects 120722404538947377 != has 21010274410787639
    Checking divu39
    Error @ 0x    39f932b5c49e (63742460413086:1634422095872.000000) : expects 1634422061874 != has 1634422061873
    Checking divu41
    Error @ 0x52bc4842f906b64a (5961719459214702154:145407801433260032.000000) : expects 145407791688163467 != has 1433203795796235
    Checking divu43
    Error @ 0x610071f2ac654a1c (6989711908767353372:162551438273150976.000000) : expects 162551439738775659 != has 19553423663507817
    Checking divu45
    Error @ 0x3ebbc2309455159c (4520420164899247516:100453778905366528.000000) : expects 100453781442205500 != has 19369192107218460
    Checking divu47
    Error @ 0x4d1605f5fcc6f742 (5554633744474109762:118183695961030656.000000) : expects 118183696690938505 != has 46126094063074953
    Checking divu49
    Error @ 0x   1ee86aa072e60 (543737122336352:11096676106240.000000) : expects 11096675966048 != has 11096675966047
    Checking divu51
    Error @ 0x3fa4d3d2cfee75c8 (4586023222955111880:89922020879368192.000000) : expects 89922023979511997 != has 17581851141435324
    Checking divu53
    Error @ 0x       148ce2ff9 (5516439545:104083768.000000) : expects 104083765 != has 104083764
    Checking divu55
    Error @ 0x      6ad4b549bc (458835184060:8342458368.000000) : expects 8342457892 != has 8342457891

As can be seen, truncation errors occur for 29, 35, 39, 49, 53, 55, so the handling of the bit pattern is not fully satisfactory.
