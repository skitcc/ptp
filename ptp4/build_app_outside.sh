#!/bin/bash

# rm ./apps/*

size=$1
sort=$2


if [[ $# != 2 ]]; then
    exit 1
fi


gcc -O0 -Wall -Werror -DSIZE=$size -DSORT=$sort outside.c -o ./apps/apps_outside/size=${size}_method=${sort}.exe -lm -lrt
