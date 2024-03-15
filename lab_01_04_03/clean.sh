#!/bin/bash
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$SCRIPT_DIR" || exit
rm -f ./func_tests/scripts/*.txt
rm -f ./func_tests/*.txt
rm -f ./*.txt
rm -f ./*.exe
rm -f ./*.o
rm -f ./*gcno
rm -f ./*gcda
rm -f ./*gcov