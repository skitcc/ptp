#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LINES 10
#define COLUMNS 10

bool input_matrix(int matrix[][COLUMNS], size_t lines, size_t columns)
{
    for (size_t i = 0; i < lines; i++)
        for (size_t j = 0; j < columns; j++)
            if (scanf("%d", &matrix[i][j]) != 1)
                return false;
    return true;
}

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


void form_result(int matrix[][COLUMNS], size_t lines, size_t columns, int res[])
{
    for (size_t i = 0; i < lines; i++)
    {
        if (is_monotone(matrix[i], columns))
            res[i] = 1;
        else
            res[i] = 0;
    }
}

void print_result(int array[], size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}


int main(void)
{
    int matrix[LINES][COLUMNS];
    size_t user_lines, user_columns;
    int res[LINES];
    printf("Введите кол-во строк и кол-во столбцов матрицы (до 10 каждый параметр)\n");
    if (scanf("%zu", &user_lines) !=  1 || scanf("%zu", &user_columns) != 1)
    {
        printf("Неверный формат строк или столбцов\n");
        return EXIT_FAILURE;
    }
    if (user_columns == 1)
    {
        printf("Последовательности из одного элемента не существует\n");
        return EXIT_FAILURE;
    }
    if (user_lines > LINES || user_lines == 0 || user_columns > COLUMNS || user_columns == 0)
    {
        printf("Неверные значения для кол-ва строк или кол-ва столбцов\n");
        return EXIT_FAILURE;
    }
    printf("Введите матрицу\n");
    if (!input_matrix(matrix, user_lines, user_columns))
    {
        printf("Ошибка ввода матрицы\n");
        return EXIT_FAILURE;
    }
    form_result(matrix, user_lines, user_columns, res);
    print_result(res, user_lines);

    return EXIT_SUCCESS;
}