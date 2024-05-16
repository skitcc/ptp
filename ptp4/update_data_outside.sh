#!/bin/bash

apps_directory="./apps/apps_outside"

mean_executable="./mean.exe"
rse_executable="./rse.exe"

REPEATS=1000

gcc -Wall -Werror rse.c -o rse.exe -lm
gcc -Wall -Werror mean.c -o mean.exe

for app in "$apps_directory"/*.exe; do

    size=$(echo "$app" | cut -d'=' -f2 | cut -d'_' -f1)
    method=$(echo "$app" | cut -d'=' -f3 | cut -d'.' -f1)
    timestamp=$(date +%s)

    output_file="./data/outside_data/raw_data/size={$size}_method={$method}_{$timestamp}.txt"

    "$app" > "$output_file"

    $(./mean.exe < "$output_file" > "temp.txt")
    $(cat temp.txt "$output_file" > temp2.txt)
    rse=$(./rse.exe < temp2.txt)
    code_return="$(echo "$?")"

    iterations=0
    while [ "$code_return" -ne "1" -a $iterations -lt $REPEATS ]; do
        if [ $iterations -gt 30 ]; then
            "$app" >> "$output_file"
            $(./mean.exe < "$output_file" > "temp.txt")
            $(cat temp.txt "$output_file" > temp2.txt)
            rse=$(./rse.exe < temp2.txt)
            code_return="$(echo "$?")"
        fi
        iterations=$((iterations+1))
    done

    if ((iterations < REPEATS)); then
        echo "RSE is less than 1.0. Exiting the loop."
    else
        echo "Maximum number of iterations reached. Exiting the loop."
    fi
done

rm rse.exe mean.exe temp.txt temp2.txt
