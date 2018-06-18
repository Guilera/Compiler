#!/bin/bash
i=1
for file in casos/*.c; do
    echo "test $i"
    ./$1 $file casos/output/out$i.txt
    echo
    i=$((i + 1))
done
