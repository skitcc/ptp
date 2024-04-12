#include "input_output.h"


// Вывод матрицы
void print_matrix(int (*matrix)[COLUMNS], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Обработка размеров матрицы
int process_matrix_size(int *lines, int *columns)
{
    printf("Введите кол-во строк и кол-во столбцов квадратной матрицы (до 10 каждый параметр)\n");
    if (scanf("%d", lines) != 1 || scanf("%d", columns) != 1)
    {
        printf("Неверный формат строк или столбцов\n");
        return EXIT_FAILURE;
    }
    if (*lines > LINES || *lines == 0 || *columns > COLUMNS || *columns == 0)
    {
        printf("Неверные значения для кол-ва строк или кол-ва столбцов\n");
        return EXIT_FAILURE;
    }
    if (*lines != *columns)
    {
        printf("Матрица должна быть квадратной\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}


