#!/bin/bash

if [[ $# != 2 ]]; then
    exit 1
else
    SIZES=$1
    SORTS=$2
fi

for size in $SIZES; do
    for sort in $SORTS; do
        ./build_app_outside.sh "$size" "$sort"
    done
done
