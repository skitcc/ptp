import os
import glob

def extract_size_method_timestamp(filename):
    """Извлекает size, method и timestamp из имени файла."""
    base_name = os.path.basename(filename)
    parts = base_name.split('_')
    size = parts[0].split('=')[1]
    method = parts[1].split('=')[1]
    timestamp = parts[2].split('.')[0]
    return size, method, timestamp

def read_first_number_from_file(filepath):
    """Считывает первое число из файла."""
    with open(filepath, 'r') as f:
        line = f.readline().strip()
        first_number = line.split()[0]
    return first_number

def read_rse_iterations_from_file(filepath):
    """Считывает rse и iterations из последних двух строк файла."""
    with open(filepath, 'r') as f:
        lines = f.readlines()
        rse = lines[-2].strip().split('=')[1].strip()
        iterations = lines[-1].strip().split(':')[1].strip()
    return rse, iterations

def process_files(raw_data_dir, preproced_data_dir, output_file, own_method):
    """Обрабатывает файлы и записывает таблицу в файл."""
    files = glob.glob(os.path.join(raw_data_dir, '*.txt'))
    table_data = []
    
    for raw_file in files:
        size, method, timestamp = extract_size_method_timestamp(raw_file)
        if own_method != method:
            continue
        preproced_file = os.path.join(preproced_data_dir, f'size={size}_method={method}_{timestamp}.txt')
        if not os.path.exists(preproced_file):
            print(f"Preproced file {preproced_file} not found, skipping.")
            continue

        first_number = read_first_number_from_file(preproced_file)
        rse, iterations = read_rse_iterations_from_file(raw_file)

        table_data.append([size, first_number, rse, iterations, method])

    with open(output_file, 'w') as f:
        f.write("Size\tFirstNumber\tRSE\tIterations\tMethod\n")
        for row in table_data:
            f.write("\t".join(row) + "\n")

if __name__ == "__main__":
    raw_data_dir = "./data/inside_ticks_data/raw_data"
    preproced_data_dir = "./data/inside_ticks_data/preproced_data"
    output_file = "./tables_data/inside_data_table.txt"

    os.makedirs("./tables_data", exist_ok=True)
    method = "{3}"
    process_files(raw_data_dir, preproced_data_dir, output_file, method)
    print(f"Processed files from {raw_data_dir} and {preproced_data_dir}, output saved to {output_file}")
