#!/bin/bash

if [[ $# != 2 ]]; then
    exit 1
fi

rm -f ./apps/apps_inside/*.exe
SIZES=$1
SORTS=$2


for size in $SIZES; do
    for sort in $SORTS; do
        ./build_app_outside.sh "$size" "$sort"
    done
done
