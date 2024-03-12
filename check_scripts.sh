#!/bin/bash

error_count=0

check_file() {
    local file="$1"
    echo "Проверка файла: $file"
    shellcheck "$file"
    if [ $? -ne 0 ]; then
        ((error_count++))
    fi
}


cd ./lab_01_01/


echo "Проверка скриптов в директории scripts/"
for script in scripts/*.sh; do
    if [ -f "$script" ]; then
        check_file "$script"
    fi
done


echo "Проверка скриптов в директории func_tests/"
for script in func_tests/*.sh; do
    if [ -f "$script" ]; then
        check_file "$script"
    fi
done

if [ "$error_count" -eq 0 ]; then
    echo "Проверка завершена успешно. Ошибок не найдено."
else
    echo "Проверка завершена. Найдено $error_count ошибок."
fi
