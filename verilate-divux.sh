#!/bin/bash
# Script to generate all bit sizes for simulation using verilator

# Simulation directory
sd=generate_simulation
mkdir -p $sd
# For all odd number between 3 and 55, generate verilog
# for bitsize between 4 and 32 and vivado tcl file that
# runs all synthesis
for i in $(seq 3 2 55); do
    # For dividend of size 4 to 32, and for a divisor of 3 to 55
    # do simulation please !
    # Luckily enough, these are really small circuits
    d=divu$i
    for n in 31 32; do #$(seq 4 32); do
        sed -e "s/$d/${d}_$n/" -e "s/= 66/= $n/" ${d}.v.orig > $sd/${d}_$n.v
        sed -e "s/@N@/$i/g" -e "s/@B@/$n/g" tb_divux.cpp > $sd/tb_${d}_$n.cpp
    done
done

# Now let's go 
cd $sd
for i in $(seq 3 2 55); do
    d=divu$i
    for n in $(seq 4 32); do
        verilator -Wall --trace -cc ${d}_$n.v --exe tb_${d}_$n.cpp -Wno-WIDTH
        make -C obj_dir -f V${d}_$n.mk V${d}_$n
        ./obj_dir/V${d}_$n
    done
done
#vim:se sw=4:et
