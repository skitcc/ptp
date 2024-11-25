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
NC="\033[0m"

# Позитивные тесты
for pos_in in $(find "$current_dir/../data" -type f -name "pos_??_in.txt" | sort); do
    pos_out="${pos_in/_in.txt/_out.txt}"
    pos_args="${pos_in/_in.txt/_args.txt}"

    if [ -f "$pos_out" ] && [ -f "$pos_args" ]; then
        if [ "$USE_VALGRIND" = true ]; then
            "$current_dir/./pos_case.sh" "$pos_in" "$pos_out" "$pos_args" --check-memory
            return_code=$?
            if [ $return_code -eq 0 ]; then
                echo -e "${GREEN}POSITIVE TEST: $(basename "$pos_in"): PASSED MEMORY: PASSED ${NC}"
                i_pos=$((i_pos+1))
            elif [ $return_code -eq 1 ]; then
                echo -e "${RED}POSITIVE TEST: $(basename "$pos_in"): FAILED MEMORY: PASSED ${NC}"
            elif [ $return_code -eq 2 ]; then
                echo -e "${RED}POSITIVE TEST: $(basename "$pos_in"): PASSED MEMORY: FAILED ${NC}"
                i_pos=$((i_pos+1))
            elif [ $return_code -eq 3 ]; then
                echo -e "${RED}POSITIVE TEST: $(basename "$pos_in"): FAILED MEMORY: FAILED ${NC}"
            fi
        else
            "$current_dir/./pos_case.sh" "$pos_in" "$pos_out" "$pos_args"
            return_code=$?
            if [ $return_code -eq 0 ]; then
                echo -e "${GREEN}POSITIVE TEST $(basename "$pos_in"): PASSED ${NC}"
                i_pos=$((i_pos+1))
            else
                echo -e "${RED}POSITIVE TEST $(basename "$pos_in"): FAILED ${NC}"
            fi
        fi
    else
        echo -e "${YELLOW}Skipping incomplete positive test case: $(basename "$pos_in") ${NC}"
    fi
done

# Негативные тесты
for neg_in in $(find "$current_dir/../data" -type f -name "neg_??_in.txt" | sort); do
    neg_args="${neg_in/_in.txt/_args.txt}"

    if [ -f "$neg_args" ]; then
        if [ "$USE_VALGRIND" = true ]; then
            "$current_dir/./neg_case.sh" "$neg_in" "$neg_args" --check-memory
            return_code=$?
            if [ $return_code -eq 0 ]; then
                echo -e "${GREEN}NEGATIVE TEST: $(basename "$neg_in"): PASSED MEMORY: PASSED ${NC}"
                i_neg=$((i_neg+1))
            elif [ $return_code -eq 1 ]; then
                echo -e "${RED}NEGATIVE TEST: $(basename "$neg_in"): FAILED MEMORY: PASSED ${NC}"
            elif [ $return_code -eq 2 ]; then
                echo -e "${RED}NEGATIVE TEST: $(basename "$neg_in"): PASSED MEMORY: FAILED ${NC}"
                i_neg=$((i_neg+1))
            elif [ $return_code -eq 3 ]; then
                echo -e "${RED}NEGATIVE TEST: $(basename "$neg_in"): FAILED MEMORY: FAILED ${NC}"
            fi
        else
            "$current_dir/./neg_case.sh" "$neg_in" "$neg_args"
            return_code=$?
            if [ $return_code -eq 0 ]; then
                echo -e "${GREEN}NEGATIVE TEST $(basename "$neg_in"): PASSED ${NC}"
                i_neg=$((i_neg+1))
            else
                echo -e "${RED}NEGATIVE TEST $(basename "$neg_in"): FAILED ${NC}"
            fi
        fi
    else
        echo -e "${YELLOW}Skipping incomplete negative test case: $(basename "$neg_in") ${NC}"
    fi
done

# Итоговый вывод
len_pos=$(find "$current_dir/../data" -type f -name "pos_??_in.txt" | wc -l)
len_neg=$(find "$current_dir/../data" -type f -name "neg_??_in.txt" | wc -l)

if [ $i_pos -eq $len_pos ]; then
    echo -e "${GREEN}Positive tests: correct $i_pos of $len_pos ${NC}"
else
    echo -e "${RED}Positive tests: correct $i_pos of $len_pos ${NC}"
fi

if [ $i_neg -eq $len_neg ]; then
    echo -e "${GREEN}Negative tests: correct $i_neg of $len_neg ${NC}"
else
    echo -e "${RED}Negative tests: correct $i_neg of $len_neg ${NC}"
fi

number_fail=$((len_neg + len_pos - i_pos - i_neg))

exit $number_fail
