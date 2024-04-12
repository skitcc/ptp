#include "solve_task.h"

// Заполнить массив минимальными элементами строк
void fill_array_of_mins(int (*matrix)[COLUMNS], size_t lines, size_t columns, int array[])
{
    for (size_t i = 0; i < lines; i++)
    {
        int min = matrix[i][0];
        for (size_t j = 0; j < columns; j++)
        {
            if (matrix[i][j] < min)
                min = matrix[i][j];
        }
        array[i] = min;
    }
}

// Отсортировать матрицу
void sort_matrix(int (*matrix)[COLUMNS], size_t lines, size_t columns, int array[])
{
    for (size_t i = 0; i < lines - 1; i++)
    {
        for (size_t j = 0; j < lines - 1 - i; j++)
        {
            if (array[j] < array[j + 1])
            {
                int temp_min = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp_min;

                for (size_t k = 0; k < columns; k++)
                {
                    int temp = matrix[j][k];
                    matrix[j][k] = matrix[j + 1][k];
                    matrix[j + 1][k] = temp;
                }
            }
        }
    }
}