def sort_file(input_file, output_file):
    with open(input_file, 'r') as file:
        # Считываем строки файла
        lines = file.readlines()

    # Отделяем заголовок от данных
    header = lines[0]
    data_lines = lines[1:]

    # Парсим данные и сортируем по первому значению в каждой строке
    data_lines_sorted = sorted(data_lines, key=lambda x: int(x.split('\t')[0].strip('{}')))

    # Записываем отсортированные данные в выходной файл
    with open(output_file, 'w') as file:
        file.write(header)
        file.writelines(data_lines_sorted)

if __name__ == "__main__":
    input_file = './tables_data/inside_data_table.txt'  # Замените на имя вашего входного файла
    output_file = './tables_data/sorted_output_inside.txt'  # Замените на имя вашего выходного файла

    sort_file(input_file, output_file)
    print(f"Data sorted and written to {output_file}")
