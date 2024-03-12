#!/bin/bash

file1="$1"
file2="$2"

if [ -f "$file1" ] && [ -f "$file2" ]; then
    grep -oE "[+-]?[0-9]+([.][0-9]+)?" "$file1" > file_new_1.txt
    grep -oE "[+-]?[0-9]+([.][0-9]+)?" "$file2" > file_new_2.txt

    if diff file_new_1.txt file_new_2.txt; then
        exit 0
    else 
        exit 1
    fi
else
    exit 1
fi