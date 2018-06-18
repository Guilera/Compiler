#!/bin/bash
i=1
for file in casos/*.c; do
	echo "rename $file to $i"
    mv $file casos/$(printf "%02i%s.c" "$i")
    i=$((i + 1))
done
