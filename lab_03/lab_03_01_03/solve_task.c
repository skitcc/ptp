#include "solve_task.h"

// Функция, проверяющая строку на монотонность элементов
bool is_monotone(int array[], size_t size)
{
    bool growing = true;
    bool decreasing = true;
    for (size_t i = 0; i < size - 1; i++)
        if (array[i] > array[i + 1])
            growing = false;
        else if (array[i] < array[i + 1])
            decreasing = false;

    return growing || decreasing;
}

// Функция, формирующая массив результатов
void form_result(int (*matrix)[COLUMNS], size_t lines, size_t columns, int res[])
{
    if (columns == 1)
    {
        for (size_t i = 0; i < lines; i++)
        {
            res[i] = 0;
        }
    }
    else
    {
        for (size_t i = 0; i < lines; i++)
        {
            if (is_monotone(matrix[i], columns))
                res[i] = 1;
            else
                res[i] = 0;
        }
    }
}