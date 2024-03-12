#!/bin/bash
clang -fsanitize=undefined -fno-omit-frame-pointer -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-conversion -Wfloat-equal -g main.c -o app.exe
