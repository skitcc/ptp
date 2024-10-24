#!/bin/bash

passed_tests=0
total_tests=0
passed_pos_tests=0
passed_neg_tests=0
total_pos_tests=0
total_neg_tests=0
failed_mem_tests=0
failed_mem_pos_tests=0
failed_mem_neg_tests=0

# Цветовые коды
GREEN="\033[0;32m"
RED="\033[0;31m"
YELLOW="\033[0;33m"
NC="\033[0m" # No Color

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR" || exit

VERBOSE=false

if [ "$1" = "-v" ]; then
    VERBOSE=true
fi

# Файл для временного хранения вывода Valgrind
valgrind_output="valgrind_report.txt"

# Очистка файла отчета Valgrind
> "$valgrind_output"

run_test() {
    local test_type=$1
    local test_num=$2
    local test_in=$3
    local test_out=$4
    local test_args=$5
    local test_script="$SCRIPT_DIR/${test_type}_case.sh"

    # Запуск теста с использованием Valgrind
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
        "$test_script" "$test_in" "$test_out" "$test_args" > /dev/null 2>> "$valgrind_output"
    return_code=$?

    # Проверка результата и утечек памяти
    if grep -q "ERROR SUMMARY: 0 errors" "$valgrind_output"; then
        memory_status="${GREEN}MEMORY PASSED${NC}"
    else
        memory_status="${RED}MEMORY FAILED${NC}"
        ((failed_mem_tests++))
        if [ "$test_type" == "pos" ]; then
            ((failed_mem_pos_tests++))
        else
            ((failed_mem_neg_tests++))
        fi
    fi

    return $return_code
}

# Запуск позитивных тестов
for pos_test_file_in in "$SCRIPT_DIR/../data/pos_"*"_in.txt"; do
    test_num=$(basename "$pos_test_file_in" | cut -d '_' -f 2)
    pos_test_file_out="$SCRIPT_DIR/../data/pos_${test_num}_out.txt"
    pos_args="$SCRIPT_DIR/../data/pos_${test_num}_args.txt"

    if [ -f "$pos_test_file_in" ] && [ -f "$pos_test_file_out" ] && [ -f "$pos_args" ]; then
        run_test "pos" "$test_num" "$pos_test_file_in" "$pos_test_file_out" "$pos_args"
        pos_test_exit_code=$?
        ((total_tests++))
        ((total_pos_tests++))

        if [ "$pos_test_exit_code" -eq 0 ]; then
            ((passed_tests++))
            ((passed_pos_tests++))
            echo -e "${GREEN}Позитивный тест $test_num пройден${NC} - $memory_status"
        else
            echo -e "${RED}Позитивный тест $test_num не пройден${NC} - $memory_status"
        fi
    else
        echo -e "${YELLOW}Пропущен позитивный тест $test_num из-за отсутствия файлов${NC}"
    fi
done

# Проверка наличия негативного теста
if [ ! -f "$SCRIPT_DIR/../data/neg_01_in.txt" ]; then
    echo "Отсутствует файл neg_01_in.txt, негативные тесты пропущены"
    echo -e "${GREEN}Пройдено $passed_tests из $total_tests тестов${NC}"
    exit "$((total_tests - passed_tests))"
fi

# Запуск негативных тестов
for neg_test_file_in in "$SCRIPT_DIR/../data/neg_"*"_in.txt"; do
    test_num=$(basename "$neg_test_file_in" | cut -d '_' -f 2)
    neg_args="$SCRIPT_DIR/../data/neg_${test_num}_args.txt"

    if [ -f "$neg_test_file_in" ] && [ -f "$neg_args" ]; then
        run_test "neg" "$test_num" "$neg_test_file_in" "" "$neg_args"
        neg_test_exit_code=$?
        ((total_tests++))
        ((total_neg_tests++))

        if [ "$neg_test_exit_code" -eq 0 ]; then
            ((passed_tests++))
            ((passed_neg_tests++))
            echo -e "${GREEN}Негативный тест $test_num пройден${NC} - $memory_status"
        else
            echo -e "${RED}Негативный тест $test_num не пройден${NC} - $memory_status"
        fi
    else
        echo -e "${YELLOW}Пропущен негативный тест $test_num из-за отсутствия файлов${NC}"
    fi
done

# Итоговый отчет о тестах
echo -e "${GREEN}Пройдено $passed_tests из $total_tests тестов${NC}"
echo -e "${GREEN}Позитивные тесты: пройдено $passed_pos_tests из $total_pos_tests${NC}"
echo -e "${GREEN}Негативные тесты: пройдено $passed_neg_tests из $total_neg_tests${NC}"

# Итоговый отчет о памяти
echo -e "${RED}Тесты с ошибками памяти: $failed_mem_tests из $total_tests${NC}"
echo -e "${RED}Ошибки памяти в позитивных тестах: $failed_mem_pos_tests из $total_pos_tests${NC}"
echo -e "${RED}Ошибки памяти в негативных тестах: $failed_mem_neg_tests из $total_neg_tests${NC}"

# Выводим отчет Valgrind в консоль
echo "Отчет Valgrind сохранен в $valgrind_output"

exit "$((total_tests - passed_tests))"
