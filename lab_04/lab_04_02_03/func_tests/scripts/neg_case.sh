#!/bin/bash

file_stream_in="$1"
working_dir=$(dirname "$0")

if [ $# -eq 1 ] && [ -f "$1" ]; then
    executable="$working_dir/../../app.exe"

    if "$executable" < "$file_stream_in" > /dev/null; then
        exit 1
    else
        exit 0
    fi
else
    exit 1
fi