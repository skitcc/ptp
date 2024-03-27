#!/bin/bash

working_dir=$(dirname "$0")
file_stream_in="$1"
file_stream_out_expected="$2"
executable="$working_dir/../../app.exe"
"$executable" < "$file_stream_in" > "result.txt"

if [ $# -eq 2 ] && [ -f "$file_stream_in" ] && [ -f "$file_stream_out_expected" ]; then
   if "$working_dir/comparator.sh" "result.txt" "$file_stream_out_expected" > /dev/null; then
        exit 0
    else
        exit 1
    fi
    
else
    exit 1
fi
