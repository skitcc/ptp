#!/bin/bash

working_dir=$(dirname "$(realpath "$0")")
file_stream_in="$1"
file_stream_out_expected="$2"

if [ -n "$3" ]; then
    app_args=$(cat "$3")
else
    app_args=""
fi

if [ ! -f "$file_stream_in" ]; then
    exit 1
fi

if [ ! -f "$file_stream_out_expected" ]; then
    exit 1
fi

first_argument=$(echo "$app_args" | cut -d' ' -f1)
executable="$working_dir/../../app.exe"

compare_files() {
    if "$working_dir/comparator.sh" "out.tmp" "$file_stream_out_expected" > /dev/null 2>&1; then
        exit 0
    else
        exit 1
    fi
}

case "$first_argument" in
    p)
        file_stream_in_bin=$(echo "$app_args" | cut -d' ' -f2)
        "$executable" import "$file_stream_in" "../../$file_stream_in_bin" >/dev/null 2>&1
        code_return=$?
        if [ $code_return -ne 0 ]; then
            exit 1
        fi
        "$executable" p "../../$file_stream_in_bin" > "out.tmp" 2>/dev/null
        compare_files
        ;;
    s)
        file_stream_in_bin=$(echo "$app_args" | cut -d' ' -f2)
        "$executable" import "$file_stream_in" "../../$file_stream_in_bin" >/dev/null 2>&1
        code_return=$?
        if [ $code_return -ne 0 ]; then
            exit 1
        fi
        "$executable" s "../../$file_stream_in_bin" >/dev/null 2>&1
        cp "../../$file_stream_in_bin" "out.bin"
        "$executable" export "../../$file_stream_in_bin" "out.tmp" >/dev/null 2>&1
        compare_files
        ;;
    *)
        exit 1
esac
