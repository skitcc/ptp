#!/bin/bash
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$SCRIPT_DIR" || exit
gcc -std=c99 -Werror -Wall -Wpedantic -Wextra -Wfloat-conversion -Wfloat-equal -c main.c
gcc main.o -o app.exe -lm