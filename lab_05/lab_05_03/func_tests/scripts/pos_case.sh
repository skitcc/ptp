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
    echo "Ошибка: входной файл $file_stream_in не существует."
    exit 1
fi

if [ ! -f "$file_stream_out_expected" ]; then
    echo "Ошибка: ожидаемый выходной файл $file_stream_out_expected не существует."
    exit 1
fi

first_argument=$(echo "$app_args" | cut -d' ' -f1)
executable="$working_dir/../../app.exe"

compare_files() {
    if "$working_dir/comparator.sh" "out.tmp" "$file_stream_out_expected" > /dev/null; then
        exit 0
    else
        exit 1
    fi
}

case "$first_argument" in
    c)
        second_argument=$(echo "$app_args" | cut -d' ' -f2)
        file_stream_in_bin=$(echo "$app_args" | cut -d' ' -f3)
        "$executable" import "$file_stream_in" "../../$file_stream_in_bin"
        "$executable" c "$second_argument" "../../$file_stream_in_bin" 
        cp "../../$file_stream_in_bin" "out.bin"
        "$executable" export "../../$file_stream_in_bin" "out.tmp"
        compare_files
        ;;
    p)
        file_stream_in_bin=$(echo "$app_args" | cut -d' ' -f2)
        "$executable" import "$file_stream_in" "../../$file_stream_in_bin"
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
