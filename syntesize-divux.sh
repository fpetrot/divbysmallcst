#!/bin/bash
# Small script to generate all bit sizes for synthesis, as I
# am unable to do it within Vivado tcl for reasons I do not
# understand.

# Synthesis directory
sd=project_1/project_1.runs/synth_1
# Tcl file with everything in it
tcl=divux.tcl
rm -f ${sd}/$tcl
# For all odd number between 3 and 55, generate verilog
# for bitsize between 4 and 32 and vivado tcl file that
# runs all synthesis
g=generated_synthesis
mkdir -p $g
for i in $(seq 3 2 55); do
    # For dividend of size 4 to 32, and for a divisor of 3 to 55
    # do synthesis please !
    # Luckily enough, these are really small circuits
    d=divu$i
    for n in $(seq 4 32); do
        sed -e "s/$d/${d}_$n/" -e "s/= 66/= $n/" ${d}.v.orig > $g/${d}_$n.v
	echo "read_verilog -library xil_defaultlib /home/fpetrot/divsynth/$g/${d}_$n.v" >> ${sd}/$tcl
	echo "synth_design -top ${d}_$n -part xc7vx690tffg1761-2" >> ${sd}/$tcl
	echo "opt_design" >> ${sd}/$tcl
	echo "report_timing -from [get_ports n] -to [get_ports q] -file ${d}_${n}_time.rpt" >> ${sd}/$tcl
	echo "report_utilization -file ${d}_${n}_util.rpt" >> ${sd}/$tcl
    done
done


# Now let's go 
cd $sd
# Be shy when working
vivado -mode batch -source $tcl > /dev/null 2>&1
cd - > /dev/null
#vim:se sw=4:et
