#!/bin/bash

# Получаем директорию текущего скрипта
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$SCRIPT_DIR" || exit 1

# Папки проекта
SRC_DIR="./src"
INC_DIR="./inc"
OUT_DIR="./out"
TESTS_DIR="./func_tests/scripts"

# Убедимся, что папка для объектных файлов существует
mkdir -p "$OUT_DIR"

# Компиляция всех .c файлов из папки src с указанием заголовков в inc
gcc -std=c99 -Wall --coverage -O0 -Werror -Wvla -Wpedantic -Wextra -Wfloat-conversion -Wfloat-equal -I"$INC_DIR" -g3 -c "$SRC_DIR"/*.c -o "$OUT_DIR"

# Линковка объектных файлов и создание исполняемого файла с покрытием кода
gcc "$OUT_DIR"/*.o --coverage -o app.exe -lm

# Запуск функциональных тестов
"$TESTS_DIR/func_tests.sh"

# Запуск gcov для генерации отчета о покрытии кода для всех файлов .c в папке src
gcov -o "$OUT_DIR" "$SRC_DIR"/*.c

# Перемещение отчетов gcov в папку out (если нужно сохранить их)
mv *.gcov "$OUT_DIR"
