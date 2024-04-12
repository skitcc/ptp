#include "matrix_operations.h"

// Функция ввода матрицы
bool input_matrix(int (*matrix)[COLUMNS], size_t lines, size_t columns)
{
    for (size_t i = 0; i < lines; i++)
        for (size_t j = 0; j < columns; j++)
            if (scanf("%d", &matrix[i][j]) != 1)
                return false;
    return true;
}
// Функция вывода матрицы
void print_result(int array[], size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}
