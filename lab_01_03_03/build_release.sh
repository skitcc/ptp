#!/bin/bash
gcc -std=c99 -Werror -Wall -Wpedantic -Wextra -Wfloat-conversion -Wfloat-equal -c main.c
gcc main.o -o app.exe -lm