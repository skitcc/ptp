#include "matrix_operations.h"

// Ввод матрицы 
bool input_matrix(int (*matrix)[COLUMNS], size_t lines, size_t columns)
{
    for (size_t i = 0; i < lines; i++)
        for (size_t j = 0; j < columns; j++)
            if (scanf("%d", &matrix[i][j]) != 1)
                return false;
    return true;
}

// Ввод матрицы
void print_matrix(int (*matrix)[COLUMNS], size_t lines, size_t columns)
{
    printf("Рельтирующая матрица:\n");
    for (size_t i = 0; i < lines; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}