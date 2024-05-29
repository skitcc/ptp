#!/bin/bash

generate_filename() {
    local size="$1"
    local method="$2"
    local timestamp="$3"
    echo "size={$size}_method={$method}_{$timestamp}.txt"
}


echo "Creating dirs for measurements..."

mkdir -p ./data/inside_data
mkdir -p ./data/inside_data/raw_data
mkdir -p ./data/inside_data/preproced_data

echo "Starting updating inside measurement(ms)..."
for app in $(find apps/apps_inside -name "*.exe" | sort -t'=' -k2,2n -k3,3n); do
    size=$(echo "$app" | cut -d'=' -f2 | cut -d'_' -f1)
    method=$(echo "$app" | cut -d'=' -f3 | cut -d'.' -f1)
    timestamp=$(date +%s)
    filename=$(generate_filename "$size" "$method" "$timestamp")
    case $method in
        1)
            mode="inside indexes"
            ;;
        2)
            mode="replace indexes"
            ;;
        3)
            mode="pointers"
            ;;
        *)
            ;;
    esac

    echo "Updating data for $size measurements, sorting : $mode "
    "$app" > "./data/inside_data/raw_data/$filename"
done
echo "Ending updating inside measurement..."

echo "Creating dirs for measurements..."

mkdir -p ./data/inside_ticks_data
mkdir -p ./data/inside_ticks_data/raw_data
mkdir -p ./data/inside_ticks_data/preproced_data

echo "Starting updating inside measurement(tsc)..."
for app in $(find apps/apps_inside_ticks -name "*.exe" | sort -t'=' -k2,2n -k3,3n); do
    size=$(echo "$app" | cut -d'=' -f2 | cut -d'_' -f1)
    method=$(echo "$app" | cut -d'=' -f3 | cut -d'.' -f1)
    timestamp=$(date +%s)

    filename=$(generate_filename "$size" "$method" "$timestamp")
    case $method in
        1)
            mode="indexes"
            ;;
        2)
            mode="replace indexes"
            ;;
        3)
            mode="pointers"
            ;;
        *)
            ;;
    esac

    echo "Updating data for $size measurements, sorting : $mode "
    "$app" > "./data/inside_ticks_data/raw_data/$filename"
done
echo "Ending updating inside measurement..."


echo "Creating dirs for measurements..."

mkdir -p ./data/outside_data
mkdir -p ./data/outside_data/raw_data
mkdir -p ./data/outside_data/preproced_data

echo "Starting updating outside measurement(ms)..."

REPEATS=1000

gcc -Wall -Werror ./c_files/rse.c -o rse.exe -lm
gcc -Wall -Werror ./c_files/mean.c -o mean.exe

for app in $(find apps/apps_outside -name "*.exe" | sort -t'=' -k2,2n -k3,3n); do
    size=$(echo "$app" | cut -d'=' -f2 | cut -d'_' -f1)
    method=$(echo "$app" | cut -d'=' -f3 | cut -d'.' -f1)
    timestamp=$(date +%s)
    case $method in
        1)
            mode="inside indexes"
            ;;
        2)
            mode="replace indexes"
            ;;
        3)
            mode="pointers"
            ;;
        *)
            ;;
    esac

    echo "Updating data for $size measurements, sorting : $mode "

    output_file=$(generate_filename "$size" "$method" "$timestamp")

    "$app" > "./data/outside_data/raw_data/$output_file"

    ./mean.exe < "./data/outside_data/raw_data/$output_file" > temp.txt
    (cat temp.txt; echo ""; cat "./data/outside_data/raw_data/$output_file") > temp2.txt
    ./rse.exe < "temp2.txt" > /dev/null
    code_return=$?

    iterations=0
    while [ "$code_return" -ne 1 ] && [ $iterations -lt $REPEATS ]; do
        "$app" >> "./data/outside_data/raw_data/$output_file"
        ./mean.exe < "./data/outside_data/raw_data/$output_file" > temp.txt
        cat temp.txt "./data/outside_data/raw_data/$output_file" > temp2.txt
        ./rse.exe < "temp2.txt" > /dev/null
        code_return=$?

        iterations=$((iterations+1))
    done
done

rm rse.exe mean.exe temp.txt temp2.txt
echo "Ending updating outside measurement(ms)..."
