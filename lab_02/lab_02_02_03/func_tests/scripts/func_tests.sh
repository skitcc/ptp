#!/bin/bash

passed_tests=0
total_tests=0

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$SCRIPT_DIR" || exit

VERBOSE=false

if [ "$1" = "-v" ]; then
    VERBOSE=true
fi

for pos_test_file_in in "$SCRIPT_DIR/../data/pos_"*"_in.txt"; do
    test_num=$(basename "$pos_test_file_in" | cut -d '_' -f 2)
    pos_test_file_out="$SCRIPT_DIR/../data/pos_${test_num}_out.txt"
    "$SCRIPT_DIR/pos_case.sh" "$pos_test_file_in" "$pos_test_file_out"
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
done

if [ ! -f "$SCRIPT_DIR/../data/neg_01_in.txt" ]; then
    exit 1
fi

for neg_test_file in "$SCRIPT_DIR/../data/neg_"*"_in.txt"; do
    test_num=$(basename "$neg_test_file" | cut -d '_' -f 2)
    "$SCRIPT_DIR/neg_case.sh" "$SCRIPT_DIR/../../app.exe" < "$neg_test_file"
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
done

echo "Пройдено $passed_tests из $total_tests тестов"
exit "$((total_tests - passed_tests))"
