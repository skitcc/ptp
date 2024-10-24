#!/bin/bash

working_dir=$(dirname "$(realpath "$0")")

file_stream_in="$1"
file_stream_out_expected="$2"

add_args_temp=()

if [ -n "$3" ]; then
    if [ -f "$3" ]; then
        add_args=()
        IFS=" " read -r -a add_args_temp <<< "$(cat "$3")"
    fi
fi

add_args=()
for arg in "${add_args_temp[@]}"; do
    if [[ "$arg" == ./* ]]; then
        add_args+=("../../${arg}")
    else
        add_args+=("$arg")
    fi
done

executable="$working_dir/../../app.exe"
if [ ! -f "$executable" ]; then
    exit 1
fi

compare_files() {
    if "$working_dir/comparator.sh" "res.txt" "$file_stream_out_expected"; then
        exit 0
    else
        exit 1
    fi
}

# Запуск программы через Valgrind и запись результата в файл
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
    "$executable" "${add_args[@]}" < "$file_stream_in"

compare_files
