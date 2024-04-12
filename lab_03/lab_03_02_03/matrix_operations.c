#include "matrix_operations.h"

bool input_matrix(int (*matrix)[COLUMNS], size_t lines, size_t columns)
{
    for (size_t i = 0; i < lines; i++)
        for (size_t j = 0; j < columns; j++)
            if (scanf("%d", &matrix[i][j]) != 1)
                return false;
    return true;
}


// Функция для вывода матрицы
void print_matrix(int (*matrix)[COLUMNS], size_t lines, size_t columns) {
    printf("Результат:\n");
    for (size_t i = 0; i < lines; i++) 
    {
        for (size_t j = 0; j < columns; j++) 
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}