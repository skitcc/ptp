#!/bin/bash

working_dir=$(dirname "$(realpath "$0")")


add_args_temp=()
if [ -n "$2" ]; then
    if [ -f "$2" ]; then
        add_args=()
        IFS=" " read -r -a add_args_temp <<< "$(cat "$2")"
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

"$executable" "${add_args[@]}" > /dev/null
code_return=$?
if [ $code_return -ne 0 ]; then
    exit 0
fi

