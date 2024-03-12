#!/bin/bash

working_dir=$(dirname "$0")
failed_tests=0

for pos_test_file_in in "$working_dir/../data/pos_"*"_in.txt"; do
    test_num=$(basename "$pos_test_file_in" | cut -d '_' -f 2)
    pos_test_file_out="$working_dir/../data/pos_${test_num}_out.txt"
    "$working_dir/pos_case.sh" "$pos_test_file_in" "$pos_test_file_out"
    pos_test_exit_code=$?
    if [ "$pos_test_exit_code" -eq 0 ]; then
        echo "Позитивный тест $test_num пройден"
    else
        echo "Позитивный тест $test_num не пройден"
        ((failed_tests++))
    fi
done

if [ ! -f "$working_dir/../data/neg_01_in.txt" ]; then
    exit 1
fi

for neg_test_file in "$working_dir/../data/neg_"*"_in.txt"; do
    test_num=$(basename "$neg_test_file" | cut -d '_' -f 2)
    "$working_dir/neg_case.sh" "$working_dir/../../app.exe" < "$neg_test_file"
    neg_test_exit_code=$?
    if [ "$neg_test_exit_code" -eq 0 ]; then
        echo "Негативный тест $test_num пройден"
    else
        echo "Негативный тест $test_num не пройден"
        ((failed_tests++))
    fi
done

exit "$failed_tests"
