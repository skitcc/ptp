import os
import matplotlib.pyplot as plt

directory = './data/preproced_data'
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
    
    # Добавление данных в соответствующий словарь в зависимости от режима
    if mode == 1:
        d1[size] = avg_time
    elif mode == 2:
        d2[size] = avg_time
    elif mode == 3:
        d3[size] = avg_time

    f.close()

# Сортировка данных для построения графиков
d1 = dict(sorted(d1.items()))
d2 = dict(sorted(d2.items()))
d3 = dict(sorted(d3.items()))

# Построение графиков для каждого режима
plt.figure(figsize=(10, 6))

plt.plot(list(d1.keys()), list(d1.values()), marker='o', linestyle='-', linewidth=1, label='Indexes')
plt.plot(list(d2.keys()), list(d2.values()), marker='o', linestyle='-', linewidth=1, label='Replace pointers')
plt.plot(list(d3.keys()), list(d3.values()), marker='o', linestyle='-', linewidth=1, label='Pointers')

plt.title('График зависимости времени от размера данных')
plt.xlabel('Размер данных')
plt.ylabel('Среднее время (мс)')
plt.legend()
plt.grid(True)
plt.show()
