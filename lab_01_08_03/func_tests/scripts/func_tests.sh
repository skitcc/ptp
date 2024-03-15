#!/bin/bash

failed_tests=0
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$SCRIPT_DIR" || exit


if [ "$1" = "-v" ]; then
    VERBOSE=true
else
    VERBOSE=false
fi


for pos_test_file_in in "$SCRIPT_DIR/../data/pos_"*"_in.txt"; do
    test_num=$(basename "$pos_test_file_in" | cut -d '_' -f 2)
    pos_test_file_out="$SCRIPT_DIR/../data/pos_${test_num}_out.txt"
    "$SCRIPT_DIR/pos_case.sh" "$pos_test_file_in" "$pos_test_file_out"
    pos_test_exit_code=$?
    if [ "$pos_test_exit_code" -eq 0 ]; then
        if [ "$VERBOSE" == true ]; then
            echo "Позитивный тест $test_num пройден"
        fi
    else
        if [ "$VERBOSE" == true ]; then
            echo "Позитивный тест $test_num не пройден"
        fi
        ((failed_tests++))
    fi
done

if [ ! -f "$SCRIPT_DIR/../data/neg_01_in.txt" ]; then
    exit 1
fi

for neg_test_file in "$SCRIPT_DIR/../data/neg_"*"_in.txt"; do
    test_num=$(basename "$neg_test_file" | cut -d '_' -f 2)
    "$SCRIPT_DIR/neg_case.sh" "$SCRIPT_DIR/../../app.exe" < "$neg_test_file"
    neg_test_exit_code=$?
    if [ "$neg_test_exit_code" -eq 0 ]; then
        if [ "$VERBOSE" == true ]; then
            echo "Негативный тест $test_num пройден"
        fi
    else
        if [ "$VERBOSE" == true ]; then
            echo "Негативный тест $test_num не пройден"
        fi
        ((failed_tests++))
    fi
done




exit "$failed_tests"
