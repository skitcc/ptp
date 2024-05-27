#!/bin/bash

working_dir=$(dirname "$(realpath "$0")")
file_stream_in="$1"

if [ -n "$2" ]; then
    app_args=$(cat "$2")
else
    app_args=""
fi

first_argument=$(echo "$app_args" | cut -d' ' -f1)
executable="$working_dir/../../app.exe"

case "$first_argument" in
    c)
        "$executable" "$app_args" >/dev/null 2>&1
        code_return=$?
        if [ $code_return -ne 0 ]; then
            # echo "3"
            exit 0
        fi
        ;;
    p | s)
        file_stream_in_bin=$(echo "$app_args" | cut -d' ' -f2)
        # echo "$file_stream_in_bin"
        "$executable" import "$file_stream_in" "../../$file_stream_in_bin" >/dev/null 2>&1
        code_return=$?
        # echo "$code_return"
        # echo "../../$file_stream_in_bin"
        if [ $code_return -ne 0 ]; then
            # echo "0"
            exit 0
        fi
        "$executable" "$first_argument" "../../$file_stream_in_bin" >/dev/null 2>&1
        code_return=$?
        if [ $code_return -ne 0 ]; then
            # echo "1"
            exit 0
        fi
        ;;
    
    *)
        "$executable" "$app_args" >/dev/null 2>&1
        code_return=$?
        if [ $code_return -ne 0 ]; then
            # echo "2"
            exit 0
        fi
esac

exit 0
