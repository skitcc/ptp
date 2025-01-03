#!/bin/bash

passed_tests=0
total_tests=0

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR" || exit

VERBOSE=false

if [ "$1" = "-v" ]; then
    VERBOSE=true
fi

# Файл для временного хранения вывода Valgrind
valgrind_output="valgrind_report.txt"

# Запуск позитивных тестов
for pos_test_file_in in "$SCRIPT_DIR/../data/pos_"*"_in.txt"; do
    test_num=$(basename "$pos_test_file_in" | cut -d '_' -f 2)
    pos_test_file_out="$SCRIPT_DIR/../data/pos_${test_num}_out.txt"
    pos_args="$SCRIPT_DIR/../data/pos_${test_num}_args.txt"
    
    if [ -f "$pos_test_file_in" ] && [ -f "$pos_test_file_out" ] && [ -f "$pos_args" ]; then
        # valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes "$SCRIPT_DIR/pos_case.sh" "$pos_test_file_in" "$pos_test_file_out" "$pos_args" > /dev/null 2> "$valgrind_output"
        "$SCRIPT_DIR/pos_case.sh" "$pos_test_file_in" "$pos_test_file_out" "$pos_args"
        pos_test_exit_code=$?
        ((total_tests++))
        
        if [ "$pos_test_exit_code" -eq 0 ]; then
            if [ "$VERBOSE" == true ]; then
                echo "Позитивный тест $test_num пройден"
            fi
            ((passed_tests++))
        else
            if [ "$VERBOSE" == true ]; then
                echo "Позитивный тест $test_num не пройден"
            fi
        fi
    else
        if [ "$VERBOSE" == true ]; then
            echo "Пропущен позитивный тест $test_num из-за отсутствия файлов"
        fi
    fi
done

# Проверка наличия негативного теста
if [ ! -f "$SCRIPT_DIR/../data/neg_01_in.txt" ]; then
    echo "Отсутствует файл neg_01_in.txt, негативные тесты пропущены"
    echo "Пройдено $passed_tests из $total_tests тестов"
    exit "$((total_tests - passed_tests))"
fi

# Запуск негативных тестов
for neg_test_file in "$SCRIPT_DIR/../data/neg_"*"_in.txt"; do
    test_num=$(basename "$neg_test_file" | cut -d '_' -f 2)
    neg_args="$SCRIPT_DIR/../data/neg_${test_num}_args.txt"
    
    if [ -f "$neg_test_file" ] && [ -f "$neg_args" ]; then
        valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes "$SCRIPT_DIR/neg_case.sh" "$neg_test_file" "$neg_args" > /dev/null 2>> "$valgrind_output"
        neg_test_exit_code=$?
        ((total_tests++))

        if [ "$neg_test_exit_code" -eq 0 ]; then
            if [ "$VERBOSE" == true ]; then
                echo "Негативный тест $test_num пройден"
            fi
            ((passed_tests++))
        else
            if [ "$VERBOSE" == true ]; then
                echo "Негативный тест $test_num не пройден"
            fi
        fi
    else
        if [ "$VERBOSE" == true ]; then
            echo "Пропущен негативный тест $test_num из-за отсутствия файлов"
        fi
    fi
done

# Итоговый отчет о тестах
echo "Пройдено $passed_tests из $total_tests тестов"

# Выводим отчет Valgrind в консоль
echo "Отчет Valgrind сохранен в $valgrind_output"

# Удаление временного файла
# rm "$valgrind_output" # убираем, если хотим оставить отчет

exit "$((total_tests - passed_tests))"
