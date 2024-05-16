#!/bin/bash

# rm ./apps/*

size=$1
sort=$2


if [[ $# != 2 ]]; then
    exit 1
fi

# rm ./apps/apps_inside/*.exe
gcc -c sort_variations.c -o sort_variations.o
gcc -O0 -Wall -Werror -DSIZE=$size -DSORT=$sort sort_variations.o inside.c -o ./apps/apps_inside/size=${size}_method=${sort}.exe -lm -lrt
rm sort_variations.o