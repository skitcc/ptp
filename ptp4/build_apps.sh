#!/bin/bash


# Вывод отладочной информации

SIZES=$1
SORTS=$2
echo "SIZES : $SIZES, SORTS : $SORTS"

# Удаление всех предыдущих приложений компиляция файла с сортировками
rm -f ./apps/apps_inside/*.exe
gcc -c ./c_files/sort_variations.c -o ./c_files/sort_variations.o

# Начало блока сборки приложений для измерений внутри (мс)
echo "Creating apps dir for inside measurments..."

mkdir -p ./apps/apps_inside


echo "Building inside apps..."

for size in $SIZES; do
    for sort in $SORTS; do
        gcc -O0 -Wall -Werror -DSIZE="$size" -DSORT="$sort" ./c_files/sort_variations.o ./c_files/inside.c -o ./apps/apps_inside/size="${size}"_method="${sort}".exe -lm -lrt
    done
done
# Конец блока сборки приложений для измерений внутри (мс)

# Начало блока сборки приложений для измерений снаружи (мс)
echo "Creating apps dir for outside measurments..."

mkdir -p ./apps/apps_outside

echo "Building outside apps..."
rm -f ./apps/apps_outside/*.exe

for size in $SIZES; do
    for sort in $SORTS; do
        gcc -O0 -Wall -Werror -DSIZE="$size" -DSORT="$sort" ./c_files/sort_variations.o ./c_files/outside.c -o ./apps/apps_outside/size="${size}"_method="${sort}".exe -lm -lrt
    done
done
# Конец блока сборки приложений для измерений снаружи (мс)


# Начало сборки скриптов для измерений внутри (тики)
echo "Creating apps dir for inside_ticks measurments..."

mkdir -p ./apps/apps_inside_ticks

echo "Building inside_ticks apps..."
rm -f ./apps/apps_inside_ticks/*.exe

for size in $SIZES; do
    for sort in $SORTS; do
        gcc -O0 -Wall -Werror -DSIZE="$size" -DSORT="$sort" ./c_files/sort_variations.o ./c_files/inside_ticks.c -o ./apps/apps_inside_ticks/size="${size}"_method="${sort}".exe -lm -lrt
    done
done
# Конец сборки скриптов для измерений внутри (тики)

rm ./c_files/sort_variations.o


