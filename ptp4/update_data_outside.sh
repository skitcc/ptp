#!/bin/bash

apps_directory="./apps/apps_outside"

mean_executable="./mean.exe"
rse_executable="./rse.exe"

REPEATS=1000

for app in "$apps_directory"/*.exe; do

    size=$(echo "$app" | cut -d'=' -f2 | cut -d'_' -f1)
    method=$(echo "$app" | cut -d'=' -f3 | cut -d'.' -f1)
    timestamp=$(date +%s)

    output_file="./data/outside_data/raw_data/size={$size}_method={$method}_{$timestamp}.txt"

    "$app" > "$output_file"

    mean=$(./mean.exe < "$output_file")

    rse=$(./rse.exe "$mean" < "$output_file")

    iterations=0
    while (( $(echo "$rse < 1.0" | bc -l) )) && ((iterations < REPEATS)); do
        if [ $iterations -gt 1 ]; then
            "$app" >> "$output_file"
            mean=$(./mean.exe < "$output_file")
            rse=$(./rse.exe "$mean" < "$output_file")
        fi
        iterations=$((iterations+1))
    done

    if ((iterations < REPEATS)); then
        echo "RSE is less than 1.0. Exiting the loop."
    else
        echo "Maximum number of iterations reached. Exiting the loop."
    fi
done
