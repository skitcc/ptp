#!/bin/bash

SCRIPT_DIR="$(dirname "$0")"

file1="$1"
file2="$2"

if [ -f "$file1" ] && [ -f "$file2" ]; then
    grep -oE "Result: *" "$file1" > "$SCRIPT_DIR/file_new_1.txt"
    grep -oE "Result: *" "$file2" > "$SCRIPT_DIR/file_new_2.txt"

    if diff "$SCRIPT_DIR/file_new_1.txt" "$SCRIPT_DIR/file_new_2.txt"; then
        exit 0
    else 
        exit 1
    fi
else
    exit 1
fi
