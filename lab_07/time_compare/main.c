#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <time.h>
#include "my_sort.h"  // Ваша реализация mysort

#define N 10000

#define GHZ 2.1  // Частота процессора в GHz

uint64_t tick_count(void)
{
    uint32_t high, low;
    __asm__ __volatile__ (
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r" (high), "=r" (low)
        :: "%rax", "%rbx", "%rcx", "%rdx"
    );

    return ((uint64_t)high << 32) | low;
}

void print_result(const char *sort_type, uint64_t start, uint64_t end)
{
    printf("%s: %" PRIu64 " тактов | %15.10lf секунд |\n", sort_type, end - start, (double)(end - start) / (GHZ * 1e9));
}

// Функции заполнения массивов
void fill_int_array(int *array, size_t size)
{
    for (size_t i = 0; i < size; i++) {
        array[i] = rand() % 1000;
    }
}

// Сортировка по возрастанию
void sort_ascending(void *array, size_t size, size_t element_size, int (*compare)(const void *, const void *))
{
    qsort(array, size, element_size, compare);
}

// Сортировка по убыванию
void sort_descending(void *array, size_t size, size_t element_size, int (*compare)(const void *, const void *))
{
    qsort(array, size, element_size, compare);
    for (size_t i = 0; i < size / 2; i++) {
        void *temp = malloc(element_size);
        memcpy(temp, (char *)array + i * element_size, element_size);
        memcpy((char *)array + i * element_size, (char *)array + (size - 1 - i) * element_size, element_size);
        memcpy((char *)array + (size - 1 - i) * element_size, temp, element_size);
        free(temp);
    }
}

int main(void)
{
    size_t sizes[N]; // Различные размеры массивов
    int c = 0;
    for (size_t i = 25; i < 1000; i+=25)
    {
        sizes[c++] = i;
    }
    size_t num_sizes = c;

    srand(time(NULL)); // Инициализация генератора случайных чисел

    // Открытие файлов для записи данных
    FILE *random_file = fopen("random_sorting_results.txt", "w");
    FILE *sorted_file = fopen("sorted_sorting_results.txt", "w");
    FILE *reversed_file = fopen("reversed_sorting_results.txt", "w");

    // Заголовки таблиц
    const char *header = "-------------------------------------------------------------------\n"
                         "|  Size  |   MySort ticks  |   MySort seconds  |   QSort ticks  |   QSort seconds  |\n"
                         "-------------------------------------------------------------------\n";
    
    // Записываем заголовки в файлы
    fprintf(random_file, "%s", header);
    fprintf(sorted_file, "%s", header);
    fprintf(reversed_file, "%s", header);

    // Целочисленные массивы
    for (size_t i = 0; i < num_sizes; i++) {
        int *array = malloc(sizes[i] * sizeof(int));
        int *original_array = malloc(sizes[i] * sizeof(int));

        printf("размер: %zu\n", sizes[i]);

        // 1. Случайный массив
        fill_int_array(original_array, sizes[i]);
        memcpy(array, original_array, sizes[i] * sizeof(int));

        printf("Случайный массив:\n");
        uint64_t start_ticks = tick_count();
        mysort(array, sizes[i], sizeof(int), compare_ints);
        uint64_t end_ticks = tick_count();
        print_result("MySort", start_ticks, end_ticks);
        uint64_t mysort_ticks = end_ticks - start_ticks;

        // Замеры для QSort
        memcpy(array, original_array, sizes[i] * sizeof(int));
        start_ticks = tick_count();
        qsort(array, sizes[i], sizeof(int), compare_ints);
        end_ticks = tick_count();
        print_result("QSort", start_ticks, end_ticks);
        uint64_t qsort_ticks = end_ticks - start_ticks;

        // Запись данных в файл для случайного массива
        fprintf(random_file, "| %5zu | %15lu | %17.10lf | %13lu | %15.10lf |\n", 
                sizes[i], mysort_ticks, (double)mysort_ticks / (GHZ * 1e9), qsort_ticks, (double)qsort_ticks / (GHZ * 1e9));

        // 2. Отсортированный массив
        sort_ascending(original_array, sizes[i], sizeof(int), compare_ints);
        memcpy(array, original_array, sizes[i] * sizeof(int));

        printf("Отсортированный массив:\n");
        start_ticks = tick_count();
        mysort(array, sizes[i], sizeof(int), compare_ints);
        end_ticks = tick_count();
        print_result("MySort", start_ticks, end_ticks);
        mysort_ticks = end_ticks - start_ticks;

        // Замеры для QSort
        memcpy(array, original_array, sizes[i] * sizeof(int));
        start_ticks = tick_count();
        qsort(array, sizes[i], sizeof(int), compare_ints);
        end_ticks = tick_count();
        print_result("QSort", start_ticks, end_ticks);
        qsort_ticks = end_ticks - start_ticks;

        // Запись данных в файл для отсортированного массива
        fprintf(sorted_file, "| %5zu | %15lu | %17.10lf | %13lu | %15.10lf |\n", 
                sizes[i], mysort_ticks, (double)mysort_ticks / (GHZ * 1e9), qsort_ticks, (double)qsort_ticks / (GHZ * 1e9));

        // 3. Массив, отсортированный в обратном порядке
        sort_descending(original_array, sizes[i], sizeof(int), compare_ints);
        memcpy(array, original_array, sizes[i] * sizeof(int));

        printf("Массив в обратном порядке:\n");
        start_ticks = tick_count();
        mysort(array, sizes[i], sizeof(int), compare_ints);
        end_ticks = tick_count();
        print_result("MySort", start_ticks, end_ticks);
        mysort_ticks = end_ticks - start_ticks;

        // Замеры для QSort
        memcpy(array, original_array, sizes[i] * sizeof(int));
        start_ticks = tick_count();
        qsort(array, sizes[i], sizeof(int), compare_ints);
        end_ticks = tick_count();
        print_result("QSort", start_ticks, end_ticks);
        qsort_ticks = end_ticks - start_ticks;

        // Запись данных в файл для массива, отсортированного в обратном порядке
        fprintf(reversed_file, "| %5zu | %15lu | %17.10lf | %13lu | %15.10lf |\n", 
                sizes[i], mysort_ticks, (double)mysort_ticks / (GHZ * 1e9), qsort_ticks, (double)qsort_ticks / (GHZ * 1e9));

        free(array);
        free(original_array);
    }

    // Записываем закрывающие линии таблицы в файлы
    const char *footer = "-------------------------------------------------------------------\n";
    fprintf(random_file, "%s", footer);
    fprintf(sorted_file, "%s", footer);
    fprintf(reversed_file, "%s", footer);

    // Закрытие файлов с данными
    fclose(random_file);
    fclose(sorted_file);
    fclose(reversed_file);

    return 0;
}
