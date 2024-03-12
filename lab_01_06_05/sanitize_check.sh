#!/bin/bash

failed_tests=0
working_dir=$(dirname "$0")
app_path="$working_dir/app.exe"
tests_dir="$working_dir/func_tests/data"


asan_path="$working_dir/build_debug_asan.sh"
msan_path="$working_dir/build_debug_msan.sh"
ubsan_path="$working_dir/build_debug_ubsan.sh"


for sanitizer_path in "$asan_path" "$msan_path" "$ubsan_path"; do

    
    echo "Тестирование санитайзера: $sanitizer_path"
    
    # Извлекаем название санитайзера из пути
    sanitizer_name=$(basename "$sanitizer_path" | cut -d '_' -f 4 | cut -d '.' -f 1)

    if eval "$sanitizer_path"; then

        for test_file in "$tests_dir/pos_"*"_in.txt"; do
            if ! "$app_path" < "$test_file" > /dev/null; then
                echo "Тест \"$test_file\" не пройден с санитайзером \"$sanitizer_name\""
                ((failed_tests++))
            fi
        done
    else
        echo "Ошибка при сборке программы с санитайзером \"$sanitizer_name\""
    fi
done


if [ "$failed_tests" -eq 0 ]; then
    echo "Все тесты пройдены успешно"
else
    echo "Не пройдено тестов: $failed_tests"
fi
