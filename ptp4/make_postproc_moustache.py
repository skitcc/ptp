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
    q_low = float(temp.split()[3])
    q_middle = float(temp.split()[4])
    q_high = float(temp.split()[5])
    
    if mode == 1:
        d1[size] = [avg_time, q_low, q_middle, q_high]
    elif mode == 2:
        d2[size] = [avg_time, q_low, q_middle, q_high]
    elif mode == 3:
        d3[size] = [avg_time, q_low, q_middle, q_high]
    f.close()

d1 = dict(sorted(d1.items()))
d2 = dict(sorted(d2.items()))
d3 = dict(sorted(d3.items()))

# Создаем новый график
plt.figure(figsize=(10, 6))

# Рисуем график для каждой группы данных
for data, label, color in [(d1, 'Indexes', 'blue'), (d2, 'Replace', 'black'), (d3, 'Pointers', 'green')]:
    sizes = []
    avg_times = []

    for size, values in data.items():
        avg_time, q_low, q_middle, q_high = values
        sizes.append(size)
        avg_times.append(avg_time)

        # Добавляем вертикальные линии
        plt.vlines(size, q_low, q_high, color=color, linestyle='dashed')

        # Отмечаем точки avg_time, q_low, q_high, q_middle
        plt.scatter(size, avg_time, color='red', marker='o')
        plt.scatter(size, q_low, color='green', marker='x')
        plt.scatter(size, q_high, color='green', marker='x')
        plt.scatter(size, q_middle, color='orange', marker='^')

    plt.plot(sizes, avg_times, label=label, color=color)

# Добавляем название графика и подписи осей
plt.title('График зависимости среднего времени от размера данных с отмеченными точками')
plt.xlabel('Размер данных')
plt.ylabel('Среднее время (мс)')

# Включаем сетку и легенду
plt.grid(True)
plt.legend()

# Показываем график
plt.show()
