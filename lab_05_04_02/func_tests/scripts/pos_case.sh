#!/bin/bash

working_dir=$(dirname "$(realpath "$0")")
file_stream_in="$1"
file_stream_out_expected="$2"

if [ -n "$3" ]; then
    app_args=$(cat "$3")
else
    app_args=""
fi

executable="$working_dir/../../app.exe"

if [ -f "$file_stream_in" ] && [ -f "$file_stream_out_expected" ]; then
    "$executable" $app_args < "$file_stream_in" > "result.txt"
    if "$working_dir/comparator.sh" "result.txt" "$file_stream_out_expected" > /dev/null; then
        exit 0
    else
        exit 1
    fi
else
    exit 1
fi
