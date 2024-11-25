#!/bin/bash

file_stream_in="$1"
current_dir=$(dirname "$0")
add_args=''

if [ -n "$2" ]; then
    if [ -f "$2" ]; then
        add_args=()
        IFS=" " read -r -a add_args <<< "$(cat "$2")"
    fi
fi

if [ -n "$USE_VALGRIND" ]; then
    if valgrind --log-file=file.log --quiet "$current_dir/../../app.exe" "${add_args[@]}" < "$file_stream_in" > /dev/null; then
    
        return_code=$?
        content_file=$(cat "file.log")

        if [ -z "$content_file" ]; then
            if [ $return_code -ne 0 ]; then
                if "$current_dir/comparator.sh"; then
                    exit 0
                else
                    exit 4
                fi
            else
                exit 1
            fi
        else
            if [ $return_code -ne 0 ]; then
                exit 2
            else
                exit 3
            fi
        fi
    fi
else
    if "$current_dir/../../app.exe" "${add_args[@]}" < "$file_stream_in" > /dev/null; then
        
        return_code=$?

        # "$current_dir/comparator.sh"
        # comparator_return_code=$?

        if [ "$return_code" == 0 ]; then
            # if [ "$comparator_return_code" -eq 0 ]; then
            #     exit 0
            # else
            #     exit 4
            # fi
            exit 0
        else
            exit 1
        fi
    fi
fi