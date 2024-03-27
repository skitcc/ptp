#!/bin/bash

# Глобальная переменная, указывающая, были ли ошибки при тестировании
TEST_FAILED=false

execute_command() {
    if [ "$VERBOSE" = true ]; then
        echo "Исполнение файла func_tests.sh"
    fi
}

build_with_asan() {
    if [ "$VERBOSE" = true ]; then
        echo "Сборка санитайзером AddressSanitizer"
    fi
    
    ./build_debug_asan.sh
}

build_with_msan() {
    if [ "$VERBOSE" = true ]; then
        echo "Сборка санитайзером MemorySanitizer"
    fi
    ./build_debug_msan.sh
}

build_with_ubsan() {
    if [ "$VERBOSE" = true ]; then
        echo "Сборка санитайзером UndefinedBehaviorSanitizer"
    fi
    ./build_debug_ubsan.sh
}

run_tests() {
    if [ "$VERBOSE" = true ]; then
        echo "Запуск тестов"
    fi
    ./func_tests/scripts/func_tests.sh
    code_error="$?"
    if [ $code_error != 0 ]; then
        TEST_FAILED=true
        echo "ОШИБКА ТЕСТОВ"
    fi
}

if [ "$1" = "-v" ]; then
    VERBOSE=true
else
    VERBOSE=false
fi

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$SCRIPT_DIR" || exit

build_with_asan
run_tests

build_with_msan
run_tests

build_with_ubsan
run_tests

if [ "$TEST_FAILED" = true ]; then
    echo "Тестирование провалено."
else
    echo "Тестирование завершено успешно."
fi