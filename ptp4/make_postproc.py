import os
import matplotlib.pyplot as plt

# Предопределенные пути к данным
directories = {
    'in': './data/inside_data/preproced_data',
    'out': './data/outside_data/preproced_data',
    'ticks': './data/inside_ticks_data/preproced_data'
}

# Имя для графика
names = {
    'in': 'Среднее время (мс)',
    'out': 'Среднее время (мс)',
    'ticks': 'Средние тики (TSC)'
}

def load_data_linear(directory):
    d1, d2, d3 = {}, {}, {}
    files = os.listdir(directory)
    
    for filename in files:
        with open(os.path.join(directory, filename), 'r') as f:
            temp = f.readline().strip()
            size = int(filename[filename.find('{') + 1 : filename.find('}')])
            avg_time = float(temp.split()[0])
            mode = int(temp.split()[-1])
            
            if mode == 1:
                d1[size] = avg_time
            elif mode == 2:
                d2[size] = avg_time
            elif mode == 3:
                d3[size] = avg_time
    
    d1 = dict(sorted(d1.items()))
    d2 = dict(sorted(d2.items()))
    d3 = dict(sorted(d3.items()))
    
    return d1, d2, d3

def plot_linear(data, name, suffix):
    d1, d2, d3 = data
    
    plt.figure(figsize=(15, 10))
    
    plt.plot(list(d1.keys()), list(d1.values()), marker='3', linestyle='-', linewidth=1, label='Indexes')
    plt.plot(list(d2.keys()), list(d2.values()), marker='3', linestyle='-', linewidth=1, label='Replace pointers')
    plt.plot(list(d3.keys()), list(d3.values()), marker='3', linestyle='-', linewidth=1, label='Pointers')
    
    plt.title('График зависимости времени от размера данных')
    plt.xlabel('Размер данных')
    plt.ylabel(f'{name}')
    plt.legend()
    plt.grid(True)
    
    plt.savefig(f'./graphs/linear_{suffix}.svg', format='svg')
    plt.close()

def load_data_error(directory):
    d1, d2, d3 = {}, {}, {}
    files = os.listdir(directory)
    
    for filename in files:
        with open(os.path.join(directory, filename), 'r') as f:
            temp = f.readline().strip()
            size = int(filename[filename.find('{') + 1 : filename.find('}')])
            avg_time = float(temp.split()[0])
            mn = float(temp.split()[1])
            mx = float(temp.split()[2])
            mode = int(temp.split()[-1])
            
            if mode == 1:
                d1[size] = [avg_time, mn, mx]
            elif mode == 2:
                d2[size] = [avg_time, mn, mx]
            elif mode == 3:
                d3[size] = [avg_time, mn, mx]
    
    d1 = dict(sorted(d1.items()))
    d2 = dict(sorted(d2.items()))
    d3 = dict(sorted(d3.items()))
    
    return d1, d2, d3

def plot_error(data, name, suffix):
    d1, d2, d3 = data
    
    plt.figure(figsize=(15, 10))
    
    sizes, avg_times = [], []
    for size, values in d1.items():
        avg_time, mn, mx = values
        sizes.append(size)
        avg_times.append(avg_time)
        plt.plot(size, avg_time, marker='o', color='blue')
        plt.vlines(size, mn, mx, colors='black', linestyles='dashed')
        plt.scatter([size, size], [mn, mx], marker='x', color='black')
    
    plt.plot(sizes, avg_times, color='black', linestyle='-', label='Indexes')
    
    sizes, avg_times = [], []
    for size, values in d2.items():
        avg_time, mn, mx = values
        sizes.append(size)
        avg_times.append(avg_time)
        plt.plot(size, avg_time, marker='o', color='black')
        plt.vlines(size, mn, mx, colors='gray', linestyles='dashed')
        plt.scatter([size, size], [mn, mx], marker='x', color='gray')
    
    plt.plot(sizes, avg_times, color='gray', linestyle='-', label='Replace')
    
    sizes, avg_times = [], []
    for size, values in d3.items():
        avg_time, mn, mx = values
        sizes.append(size)
        avg_times.append(avg_time)
        plt.plot(size, avg_time, color='green', marker='o')
        plt.vlines(size, mn, mx, colors='red', linestyles='dashed')
        plt.scatter([size, size], [mn, mx], marker='x', color='red')
    
    plt.plot(sizes, avg_times, color='red', linestyle='-', label='Pointers')
    
    plt.title('График зависимости времени от размера данных')
    plt.xlabel('Размер данных')
    plt.ylabel(f'{name}')
    plt.grid(True)
    plt.legend()
    
    plt.savefig(f'./graphs/error_{suffix}.svg', format='svg')
    plt.close()

def load_data_moustache(directory):
    d1 = {}
    files = os.listdir(directory)
    
    for filename in files:
        with open(os.path.join(directory, filename), 'r') as f:
            temp = f.readline().strip()
            size = int(filename[filename.find('{') + 1 : filename.find('}')])
            avg_time = float(temp.split()[0])
            q_low = float(temp.split()[3])
            q_middle = float(temp.split()[4])
            q_high = float(temp.split()[5])
            mode = int(temp.split()[-1])
            
            if mode == 1:
                d1[size] = [avg_time, q_low, q_middle, q_high]
    
    d1 = dict(sorted(d1.items()))
    
    return d1

def plot_moustache(data, name, suffix):
    d1 = data
    
    plt.figure(figsize=(15, 10))
    
    sizes, avg_times = [], []
    for size, values in d1.items():
        avg_time, q_low, q_middle, q_high = values
        sizes.append(size)
        avg_times.append(avg_time)
        
        plt.vlines(size, q_low, q_high, color='blue', linestyle='dashed')
        plt.scatter(size, avg_time, color='red', marker='o')
        plt.scatter(size, q_low, color='green', marker='x')
        plt.scatter(size, q_high, color='green', marker='x')
        plt.scatter(size, q_middle, color='orange', marker='^')
    
    plt.plot(sizes, avg_times, label='Indexes', color='blue')
    
    plt.title('График зависимости среднего времени от размера данных с отмеченными точками')
    plt.xlabel('Размер данных')
    plt.ylabel(f'{name}')
    
    plt.grid(True)
    plt.legend()
    plt.savefig(f'./graphs/moustache_{suffix}.svg', format='svg')
    plt.close()

def main():
    for key, directory in directories.items():
        name = names[key]
        
        data_linear = load_data_linear(directory)
        plot_linear(data_linear, name, key)
        
        data_error = load_data_error(directory)
        plot_error(data_error, name, key)
        
        data_moustache = load_data_moustache(directory)
        plot_moustache(data_moustache, name, key)

if __name__ == '__main__':
    main()
