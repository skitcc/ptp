import os
import re
from math import inf

def process_files(directory, directory_preproc):
    if not os.path.exists(directory_preproc):
        os.makedirs(directory_preproc)

    files = os.listdir(directory)

    for filename in files:
        filepath = os.path.join(directory, filename)
        with open(filepath, 'r') as f:
            average_time, low_q, middle_q, high_q = 0, 0, 0, 0
            mn, mx = inf, -inf
            temp = []
            
            for line in f:
                if re.search(r'rse\s*=\s*\d+', line) or re.search(r'iterations\s*=\s*\d+', line) or re.search(r'iterations_reached\s*:\s*\d+', line):
                    break
                temp.append(float(line.strip()))
        
        temp.sort()
        l = len(temp)
        for ind, time in enumerate(temp):
            average_time += time
            mn = min(mn, time)
            mx = max(mx, time)
            if ind == int(l / 4):
                low_q = time
            if ind == int(l / 2):
                middle_q = time
            if ind == int(l * 3 / 4):
                high_q = time
        average_time /= l
        mode = re.search(r'method={(\d+)}', filename).group(1)
        
        preproc_filepath = os.path.join(directory_preproc, filename)
        with open(preproc_filepath, 'w') as f1:
            f1.write(f"{average_time} {mn} {mx} {low_q} {middle_q} {high_q} {mode}")

data_directories = {
    'in': ('./data/inside_data/raw_data', './data/inside_data/preproced_data'),
    'out': ('./data/outside_data/raw_data', './data/outside_data/preproced_data'),
    'ticks': ('./data/inside_ticks_data/raw_data', './data/inside_ticks_data/preproced_data')
}

def main():
    print("Preparing data for graph...")
    for key, (raw_dir, preproc_dir) in data_directories.items():
        process_files(raw_dir, preproc_dir)
    print("Done!")

if __name__ == '__main__':
    main()
