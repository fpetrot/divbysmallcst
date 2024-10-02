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

To check the validity of the approach and when to remove
parts of the expressions when the bitsize authorizes it,
one can perform a systemc implementation using sc_int<>,
as show for the 25 case in `divu25.cpp`.
Running `make check` runs the division by 25 for bitsizes
1 to 32.

I've translated the routines in verilog hdl and thanks to
a few scripts, verified them all and synthesized them too.
Hopefully, this might be reported in a paper one of these
days, ...
