import matplotlib.pyplot as plt
import matplotlib.ticker as ticker

# Функция для чтения данных из файла и преобразования их в соответствующие массивы
def read_data(filename):
    sizes = []
    mysort_ticks = []
    mysort_seconds = []
    qsort_ticks = []
    qsort_seconds = []

    with open(filename, 'r') as file:
        # Пропускаем первую строку с заголовками
        lines = file.readlines()[3:-1]  # Пропускаем заголовок и нижнюю границу таблицы
        for line in lines:
            parts = line.split('|')
            size = int(parts[1].strip())
            mysort_tick = int(parts[2].strip())
            mysort_sec = float(parts[3].strip())
            qsort_tick = int(parts[4].strip())
            qsort_sec = float(parts[5].strip())
            
            sizes.append(size)
            mysort_ticks.append(mysort_tick)
            mysort_seconds.append(mysort_sec)
            qsort_ticks.append(qsort_tick)
            qsort_seconds.append(qsort_sec)
    
    return sizes, mysort_ticks, mysort_seconds, qsort_ticks, qsort_seconds

# Построение графиков
def plot_graphs(sizes, mysort_ticks, mysort_seconds, qsort_ticks, qsort_seconds):
    plt.figure(figsize=(10, 5))

    # График для тиков
    plt.subplot(1, 2, 1)
    plt.plot(sizes, mysort_ticks, label='MySort (ticks)', marker='o')
    plt.plot(sizes, qsort_ticks, label='QSort (ticks)', marker='o')
    plt.xlabel('Размер массива')
    plt.ylabel('Количество тиков')
    plt.title('Сравнение по тикам')

    # Устанавливаем форматирование чисел оси Y для тиков
    plt.gca().yaxis.set_major_formatter(ticker.FuncFormatter(lambda x, _: f'{x:.0f}'))  # Без экспоненциального формата

    plt.legend()
    plt.grid(True)

    # График для секунд
    plt.subplot(1, 2, 2)
    plt.plot(sizes, mysort_seconds, label='MySort (seconds)', marker='o')
    plt.plot(sizes, qsort_seconds, label='QSort (seconds)', marker='o')
    plt.xlabel('Размер массива')
    plt.ylabel('Время (секунды)')
    plt.title('Сравнение по времени выполнения')
    plt.legend()
    plt.grid(True)

    plt.tight_layout()
    plt.show()

# Основная функция
if __name__ == "__main__":
    filename = 'random_sorting_results.txt'  # Имя файла с данными
    sizes, mysort_ticks, mysort_seconds, qsort_ticks, qsort_seconds = read_data(filename)
    plot_graphs(sizes, mysort_ticks, mysort_seconds, qsort_ticks, qsort_seconds)
