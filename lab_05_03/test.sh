#!/bin/bash

# Пути к файлам
file_tmp="1.tmp"
file_txt="1.txt"

# Выполнение grep команд и сохранение их вывода во временные файлы
grep -E "" "$file_tmp" > "output_tmp.txt"
grep -E "" "$file_txt" > "output_txt.txt"

# Сравнение вывода с помощью diff
diff "output_tmp.txt" "output_txt.txt"

# Очистка временных файлов
# rm "output_tmp.txt" "output_txt.txt"
