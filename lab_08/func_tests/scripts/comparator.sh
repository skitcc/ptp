#!/bin/bash

SCRIPT_DIR="$(dirname "$0")"

file1="$1"
file2="$2"

if [ -f "$file1" ] && [ -f "$file2" ]; then
    sed -e 's/\r$//' "$file1" | tr -s '[:space:]' ' ' | sed 's/ *$//' > "$SCRIPT_DIR/file_new_1.txt"
    echo >> "$SCRIPT_DIR/file_new_1.txt"  # Добавить новую строку в конец

    sed -e 's/\r$//' "$file2" | tr -s '[:space:]' ' ' | sed 's/ *$//' > "$SCRIPT_DIR/file_new_2.txt"
    echo >> "$SCRIPT_DIR/file_new_2.txt"  # Добавить новую строку в конец

    if diff "$SCRIPT_DIR/file_new_1.txt" "$SCRIPT_DIR/file_new_2.txt"; then
        exit 0
    else 
        exit 1
    fi
else
    exit 1
fi
