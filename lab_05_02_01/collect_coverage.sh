#!/bin/bash
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$SCRIPT_DIR" || exit
gcc -std=c99 -Wall --coverage -O0 -Werror -Wvla -Wpedantic -Wextra -Wfloat-conversion -Wfloat-equal -lm -g3 -c ./*.c
gcc ./*.o --coverage -o app.exe -lm
./func_tests/scripts/func_tests.sh
gcov ./*.c
