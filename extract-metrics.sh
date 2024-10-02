#!/bin/bash
# Extract the resources and timing from the report files

# Synthesis directory
sd=project_1/project_1.runs/synth_1
rm -f luts nanos
{
for i in $(seq 3 2 55); do
    d=divu$i
    grep "as Logic" ${sd}/${d}_*_util.rpt|sed "s/_\([0-9]\+\)_/ \1 /"|sort -k 2 -n|awk '{print "(", $2, ",", $8, ")"}'|sed "s/ //g"|xargs echo -e "#$d\n"
done
} > luts

{
for i in $(seq 3 2 55); do
    d=divu$i
    grep "Data Path Delay" ${sd}/${d}_*_time.rpt|sed "s/_\([0-9]\+\)_/ \1 /"|sort -k 2 -n|awk '{print "(", $2, ",", $7, ")"}'|sed "s/ns//"|sed "s/ //g"|xargs echo -e "#$d\n"
done
} > nanos
