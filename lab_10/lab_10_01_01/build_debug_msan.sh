#!/bin/bash
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$SCRIPT_DIR" || exit

clang -fsanitize=memory -fPIE -fno-omit-frame-pointer -std=c99 -Wall -Werror -Wpedantic -Wvla -Wextra -Wfloat-conversion -Wfloat-equal -g -c -I./inc ./src/*.c
clang ./*.o -o app.exe -lm -fsanitize=memory -fPIE -pie
