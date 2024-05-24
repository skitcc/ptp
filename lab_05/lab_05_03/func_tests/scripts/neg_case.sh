#!/bin/bash

working_dir=$(dirname "$(realpath "$0")")
file_stream_in="$1"

if [ -n "$2" ]; then
    app_args=$(cat "$2")
else
    app_args=""
fi

executable="$working_dir/../../app.exe"

if [ -f "$file_stream_in" ]; then
    if "$executable" $app_args < "$file_stream_in" > /dev/null; then
        exit 1
    else
        exit 0
    fi
else
    exit 1
fi
