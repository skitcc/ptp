#!/bin/bash

# Получаем директорию скрипта
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# Переходим в директорию скрипта
cd "$SCRIPT_DIR" || exit

# Компиляция исходных файлов с указанием директории заголовочных файлов
clang -fsanitize=address -fno-omit-frame-pointer -std=c99 -Wall -Werror -Wpedantic -Wextra -Wvla -Wfloat-conversion -Wfloat-equal -g -I./inc -c ./src/*.c

# Сборка исполняемого файла
clang ./*.o -o app.exe -lm -fsanitize=address
