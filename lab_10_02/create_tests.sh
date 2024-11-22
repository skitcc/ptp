#!/bin/bash

TEST_DIR="./func_tests/data"

GREEN="\e[32m"
RED="\e[31m"
YELLOW="\e[33m"
CYAN="\e[36m"
RESET="\e[0m"

get_last_test_number() {
    local prefix=$1
    last_num=$(find "$TEST_DIR" -type f -name "${prefix}_*_*" | grep -oP "${prefix}_\K\d{2}" | sort -n | tail -n 1)
    if [[ -z $last_num ]]; then
        echo 0
    else
        echo $last_num
    fi
}

create_files() {
    local neg_count=$1
    local pos_count=$2
    local append_mode=$3

    mkdir -p "$TEST_DIR"

    if [[ $append_mode == true ]]; then
        last_neg_num=$(get_last_test_number "neg")
        last_pos_num=$(get_last_test_number "pos")
    else
        last_neg_num=0
        last_pos_num=0
    fi

    echo -e "${CYAN}Создание негативных тестов:${RESET}"
    for ((i=1; i<=neg_count; i++)); do
        num=$(printf "%02d" $((last_neg_num + i)))  
        touch "$TEST_DIR/neg_${num}_args.txt"
        touch "$TEST_DIR/neg_${num}_in.txt"
        echo -e "${YELLOW}Создано:${RESET} neg_${num}_args.txt, neg_${num}_in.txt"
    done

    echo -e "${CYAN}Создание позитивных тестов:${RESET}"
    for ((i=1; i<=pos_count; i++)); do
        num=$(printf "%02d" $((last_pos_num + i)))  
        touch "$TEST_DIR/pos_${num}_args.txt"
        touch "$TEST_DIR/pos_${num}_in.txt"
        touch "$TEST_DIR/pos_${num}_out.txt"
        echo -e "${YELLOW}Создано:${RESET} pos_${num}_args.txt, pos_${num}_in.txt, pos_${num}_out.txt"
    done

    echo -e "${GREEN}Файлы для негативных ($neg_count) и позитивных ($pos_count) тестов успешно созданы в $TEST_DIR.${RESET}"
}

delete_empty_files() {
    echo -e "${CYAN}Удаление пустых файлов...${RESET}"
    find "$TEST_DIR" -type f -empty -print -delete
    echo -e "${GREEN}Все пустые файлы удалены.${RESET}"
}

append_mode=false

while [[ $# -gt 0 ]]; do
    case $1 in
        --clean-empty)
            delete_empty_files
            exit 0
            ;;
        --append)
            append_mode=true
            shift
            ;;
        *)
            echo -e "${RED}Неизвестный флаг: $1${RESET}"
            exit 1
            ;;
    esac
done

read -p "$(echo -e ${CYAN}Введите количество негативных тестов \(neg\): ${RESET})" neg_count
read -p "$(echo -e ${CYAN}Введите количество позитивных тестов \(pos\): ${RESET})" pos_count

create_files "$neg_count" "$pos_count" "$append_mode"
