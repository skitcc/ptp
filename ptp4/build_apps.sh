#!/bin/bash


SIZES=$1
SORTS=$2
echo "SIZES : $SIZES, SORTS : $SORTS"

echo "Creating apps dir for inside measurments..."

mkdir -p ./apps/apps_inside


echo "Building inside apps..."
rm -f ./apps/apps_inside/*.exe
gcc -c ./c_files/sort_variations.c -o ./c_files/sort_variations.o
for size in $SIZES; do
    for sort in $SORTS; do
        gcc -O0 -Wall -Werror -DSIZE="$size" -DSORT="$sort" ./c_files/sort_variations.o ./c_files/inside.c -o ./apps/apps_inside/size="${size}"_method="${sort}".exe -lm -lrt
    done
done


echo "Creating apps dir for outside measurments..."

mkdir -p ./apps/apps_outside

echo "Building outside apps..."
rm -f ./apps/apps_outside/*.exe

for size in $SIZES; do
    for sort in $SORTS; do
        gcc -O0 -Wall -Werror -DSIZE="$size" -DSORT="$sort" ./c_files/sort_variations.o ./c_files/outside.c -o ./apps/apps_outside/size="${size}"_method="${sort}".exe -lm -lrt
    done
done

echo "Creating apps dir for inside_ticks measurments..."

mkdir -p ./apps/apps_inside_ticks

echo "Building inside_ticks apps..."
rm -f ./apps/apps_inside_ticks/*.exe

for size in $SIZES; do
    for sort in $SORTS; do
        gcc -O0 -Wall -Werror -DSIZE="$size" -DSORT="$sort" ./c_files/sort_variations.o ./c_files/inside_ticks.c -o ./apps/apps_inside_ticks/size="${size}"_method="${sort}".exe -lm -lrt
    done
done

rm ./c_files/sort_variations.o


