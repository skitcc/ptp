#!/bin/bash

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$SCRIPT_DIR" || exit

gcc -std=c99 -Wall -Werror -Wvla -Wpedantic -Wextra -Wfloat-conversion -Wfloat-equal -g3 -I./inc -c ./src/*.c
gcc ./*.o -o app.exe -lm

valgrind --leak-check=full --show-leak-kinds=all ./app.exe
