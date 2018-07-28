#!/bin/bash
i=1
for file in casos/*; do
    echo "test $i $file"
    echo
    i=$((i + 1))
done
