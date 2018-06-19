#!/bin/bash
for i in {01..99} do;
	echo "rename $file to $(printf "%02i%s.c" "$file")"
    mv casos/$i.c casos/$(printf "%03i.c" "$i")
done
