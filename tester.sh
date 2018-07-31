#!/bin/bash
for i in codegen_samples/in/*; do
    j=${i/in/out}
    o=${j/.c/.asm}
    echo "compile ${i##*/} >>>> ${o##*/}"
    # echo "$i >>>> $o"
    $1 $i $o
    echo
done
