#!/bin/bash

# Запуск всех скриптов поочередно

if [[ $# != 2 ]]; then
    echo "Enter SIZE and SORT"
    exit 1
fi

SIZES=$1
SORTS=$2

./build_apps.sh "${SIZES}" "${SORTS}"
./update_data.sh
python3 make_preproc.py
python3 make_postproc.py