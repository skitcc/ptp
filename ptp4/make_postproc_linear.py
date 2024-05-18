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
    print(avg_time)
    
    if mode == 1:
        d1[size] = avg_time
    elif mode == 2:
        d2[size] = avg_time
    elif mode == 3:
        d3[size] = avg_time

    f.close()

d1 = dict(sorted(d1.items()))
d2 = dict(sorted(d2.items()))
d3 = dict(sorted(d3.items()))

plt.figure(figsize=(15, 10))
print(list(d1.values()))

plt.plot(list(d1.keys()), list(d1.values()), marker='3', linestyle='-', linewidth=1, label='Indexes')
plt.plot(list(d2.keys()), list(d2.values()), marker='3', linestyle='-', linewidth=1, label='Replace pointers')
plt.plot(list(d3.keys()), list(d3.values()), marker='3', linestyle='-', linewidth=1, label='Pointers')

plt.title('График зависимости времени от размера данных')
plt.xlabel('Размер данных')
plt.ylabel(f'{name}')
plt.legend()
plt.grid(True)


plt.savefig(f'linear_{s}.svg', format='svg')

plt.show()
