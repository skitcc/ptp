#!/bin/bash
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$SCRIPT_DIR" || exit
gcc main.c --coverage -o app.exe -lm
./func_tests/scripts/func_tests.sh
gcov main.c