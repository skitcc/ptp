#!/bin/bash


SIZES=$1
SORTS=$2
echo "SIZES : $SIZES, SORTS : $SORTS"
echo "Building inside apps..."
rm -f ./apps/apps_inside/*.exe
gcc -c ./c_files/sort_variations.c -o ./c_files/sort_variations.o
for size in $SIZES; do
    for sort in $SORTS; do
        gcc -O0 -Wall -Werror -DSIZE="$size" -DSORT="$sort" ./c_files/sort_variations.o ./c_files/inside.c -o ./apps/apps_inside/size="${size}"_method="${sort}".exe -lm -lrt
    done
done


echo "Building outside apps..."
rm -f ./apps/apps_outside/*.exe

for size in $SIZES; do
    for sort in $SORTS; do
        gcc -O0 -Wall -Werror -DSIZE="$size" -DSORT="$sort" ./c_files/sort_variations.o ./c_files/outside.c -o ./apps/apps_outside/size="${size}"_method="${sort}".exe -lm -lrt
    done
done

echo "Building inside_ticks apps..."
rm -f ./apps/apps_inside_ticks/*.exe

for size in $SIZES; do
    for sort in $SORTS; do
        gcc -O0 -Wall -Werror -DSIZE="$size" -DSORT="$sort" ./c_files/sort_variations.o ./c_files/inside_ticks.c -o ./apps/apps_inside_ticks/size="${size}"_method="${sort}".exe -lm -lrt
    done
done

rm ./c_files/sort_variations.o


