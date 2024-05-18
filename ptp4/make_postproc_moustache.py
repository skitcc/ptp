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

for filename in files:
    f = open(os.path.join(directory, filename), 'r')
    temp = f.readline().strip()
    size = int(filename[filename.find('{') + 1 : filename.find('}')])
    avg_time = float(temp.split()[0])
    mode = int(temp.split()[-1])
    q_low = float(temp.split()[3])
    q_middle = float(temp.split()[4])
    q_high = float(temp.split()[5])
    
    if mode == 1:
        d1[size] = [avg_time, q_low, q_middle, q_high]
    f.close()

d1 = dict(sorted(d1.items()))

plt.figure(figsize=(15, 10))

sizes = []
avg_times = []

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
plt.savefig(f'moustache_{s}.svg', format='svg')

plt.show()
