#!/bin/bash

working_dir=$(dirname "$(realpath "$0")")
file_stream_in="$1"

if [ ! -f "$file_stream_in" ]; then
    echo "Ошибка: входной файл $file_stream_in не существует."
    exit 1
fi


if [ -n "$2" ]; then
    app_args=$(cat "$2")
else
    app_args=""
fi

first_argument=$(echo "$app_args" | cut -d' ' -f1)

executable="$working_dir/../../app.exe"

case "$first_argument" in
    p)
        file_stream_in_bin=$(echo "$app_args" | cut -d' ' -f2)
        "$executable" import "$file_stream_in" "../../$file_stream_in_bin"
        code_return=$?
        "$executable" p "../../$file_stream_in_bin" > "out.tmp"
        compare_files
        ;;
    s)
        file_stream_in_bin=$(echo "$app_args" | cut -d' ' -f2)
        "$executable" import "$file_stream_in" "../../$file_stream_in_bin"
        "$executable" s "../../$file_stream_in_bin"
        cp "../../$file_stream_in_bin" "out.bin"
        "$executable" export "../../$file_stream_in_bin" "out.tmp"
        compare_files
        ;;
esac


if [ -f "$file_stream_in" ]; then
    if "$executable" $app_args < "$file_stream_in" > /dev/null; then
        exit 1
    else
        exit 0
    fi
else
    exit 1
fi
