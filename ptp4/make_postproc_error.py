import os
import matplotlib.pyplot as plt

s = input("Введите какие данные использовать in/out/ticks: ")
name = 'Среднее время (мс)'
if (s == "in"):
    directory = './data/inside_data/preproced_data'
elif (s == "out"):
    directory = './data/outside_data/preproced_data'
elif (s == "ticks"):
    directory = './data/inside_ticks_data/preproced_data'
    name = 'Средние тики (TSC)'

files = os.listdir(directory)

d1 = {}
d2 = {}
d3 = {}

for filename in files:
    f = open(os.path.join(directory, filename), 'r')
    temp = f.readline().strip()
    size = int(filename[filename.find('{') + 1 : filename.find('}')])
    avg_time = float(temp.split()[0])
    mode = int(temp.split()[-1])
    mn = float(temp.split()[1])
    mx = float(temp.split()[2])
    
    if mode == 1:
        d1[size] = [avg_time, mn, mx]
    elif mode == 2:
        d2[size] = [avg_time, mn, mx]
    elif mode == 3:
        d3[size] = [avg_time, mn, mx]
    f.close()

d1 = dict(sorted(d1.items()))
d2 = dict(sorted(d2.items()))
d3 = dict(sorted(d3.items()))

plt.figure(figsize=(15, 10))

sizes = []
avg_times = []

for size, data in d1.items():
    plt.plot(size, data[0], marker='o', color='blue')
    plt.vlines(size, data[1], data[2], colors='black', linestyles='dashed')
    plt.scatter([size, size], [data[1], data[2]], marker='x', color='black')
    sizes.append(size)
    avg_times.append(data[0])

plt.plot(sizes, avg_times, color='black', linestyle='-', label='Indexes')

sizes = []
avg_times = []
for size, data in d2.items():
    plt.plot(size, data[0], marker='o', color='black')
    plt.vlines(size, data[1], data[2], colors='gray', linestyles='dashed')
    plt.scatter([size, size], [data[1], data[2]], marker='x', color='gray')
    sizes.append(size)
    avg_times.append(data[0])

plt.plot(sizes, avg_times, color='gray', linestyle='-', label='Replace')

sizes = []
avg_times = []
for size, data in d3.items():
    plt.plot(size, data[0], color='green',marker='o')
    plt.vlines(size, data[1], data[2], colors='red', linestyles='dashed')
    plt.scatter([size, size], [data[1], data[2]], marker='x', color='red')
    sizes.append(size)
    avg_times.append(data[0])

plt.plot(sizes, avg_times, color='red', linestyle='-', label='Pointers')

plt.title('График зависимости времени от размера данных')
plt.xlabel('Размер данных')
plt.ylabel(f'{name}')
plt.grid(True)
plt.legend()

plt.savefig(f'error_{s}.svg', format='svg')

plt.show()
