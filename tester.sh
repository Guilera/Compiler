#!/bin/bash
for i in {01..248}; do
    echo "test $i.c to out$i"
    ./$1 casos/$i.c casos/output/$i.txt
    echo
done
