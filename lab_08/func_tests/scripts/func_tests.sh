#!/bin/bash

current_dir=$(dirname "$0")

# Обработка флагов командной строки
USE_VALGRIND=false
for arg in "$@"; do
    if [[ "$arg" == "--check-memory" ]]; then
        USE_VALGRIND=true
    fi
done

i_pos=0
i_neg=0

GREEN="\033[0;32m"
RED="\033[0;31m"
YELLOW="\033[0;33m"
NC="\033[0m"

arr_pos_in=()
arr_pos_out=()
arr_neg_in=()
arr_neg_args=()
arr_pos_args=()
mapfile -t arr_pos_in <<< "$(find "$current_dir/../data" -name "pos_[0-9][0-9]_in.txt" | sort)"
mapfile -t arr_pos_out <<< "$(find "$current_dir/../data" -name "pos_[0-9][0-9]_out.txt" | sort)"
mapfile -t arr_neg_in <<< "$(find "$current_dir/../data" -name "neg_[0-9][0-9]_in.txt" | sort)"
mapfile -t arr_neg_args <<< "$(find "$current_dir/../data" -name "neg_[0-9][0-9]_args.txt" | sort)"
mapfile -t arr_pos_args <<< "$(find "$current_dir/../data" -name "pos_[0-9][0-9]_args.txt" | sort)"

len_pos=${#arr_pos_args[@]}

# Запуск позитивных тестов
for ((i=0; i<len_pos; i++)); do  
    if [ "$USE_VALGRIND" = true ]; then
        "$current_dir/./pos_case.sh" "${arr_pos_in[i]}" "${arr_pos_out[i]}" "${arr_pos_args[i]}" --check-memory
        return_code=$?
        if [ $return_code -eq 0 ]; then
            echo -e "${GREEN}POSITIVE TEST: $((i+1)): PASSED MEMORY: PASSED ${RC}"
            i_pos=$((i_pos+1))
        elif [ $return_code -eq 1 ]; then
            echo -e "${RED}POSITIVE TEST: $((i+1)): FAILED MEMORY: PASSED ${RC}"
        elif [ $return_code -eq 2 ]; then
            echo -e "${RED}POSITIVE TEST: $((i+1)): PASSED MEMORY: FAILED ${RC}"
            i_pos=$((i_pos+1))
        elif [ $return_code -eq 3 ]; then
            echo -e "${RED}POSITIVE TEST: $((i+1)): FAILED MEMORY: FAILED ${RC}"
        fi
    else
        "$current_dir/./pos_case.sh" "${arr_pos_in[i]}" "${arr_pos_out[i]}" "${arr_pos_args[i]}"
        return_code=$?
        if [ $return_code -eq 0 ]; then
            i_pos=$((i_pos+1))
            echo -e "${GREEN}POSITIVE TEST $((i+1)): PASSED ${RC}"
        else
            echo -e "${RED}POSITIVE TEST $((i+1)): FAILED ${RC}"
        fi
    fi
done

len_neg=${#arr_neg_args[@]}

# Запуск негативных тестов
for ((i=0; i<len_neg; i++)); do
    if [ "$USE_VALGRIND" = true ]; then
        "$current_dir/./neg_case.sh" "${arr_neg_in[i]}" "${arr_neg_args[i]}" --check-memory
        return_code=$?
        if [ $return_code -eq 0 ]; then
            echo -e "${GREEN}NEGATIVE TEST: $((i+1)): PASSED MEMORY: PASSED ${NC}"
            i_neg=$((i_neg+1))
        elif [ $return_code -eq 1 ]; then
            echo -e "${RED}NEGATIVE TEST: $((i+1)): FAILED MEMORY: PASSED ${NC}"
        elif [ $return_code -eq 2 ]; then
            echo -e "${RED}NEGATIVE TEST: $((i+1)): PASSED MEMORY: FAILED ${NC}"
            i_neg=$((i_neg+1))
        elif [ $return_code -eq 3 ]; then
            echo -e "${RED}NEGATIVE TEST: $((i+1)): FAILED MEMORY: FAILED ${NC}"
        fi
    else
        "$current_dir/./neg_case.sh" "${arr_neg_in[i]}" "${arr_neg_args[i]}"
        return_code=$?
        if [ $return_code -eq 0 ]; then
            i_neg=$((i_neg+1))
            echo -e "${GREEN}NEGATIVE TEST $((i+1)): PASSED ${NC}"
        else
            echo -e "${RED}NEGATIVE TEST $((i+1)): FAILED ${NC}"
        fi
    fi
done


if [ $i_pos -eq $len_pos ]; then
    echo -e "${GREEN}Positive tests: correct $i_pos of $len_pos ${NC}"
else
    echo -e "${RED}Positive tests: correct $i_pos of $len_pos ${NC}"
fi

if [ $i_neg -eq $len_neg ]; then
    echo -e "${GREEN}Negative tests: correct $i_neg of $len_pos ${NC}"
else
    echo -e "${RED}Negative tests: correct $i_neg of $len_pos ${NC}"
fi

number_fail=$((len_neg + len_pos - i_pos - i_neg))

exit $number_fail
