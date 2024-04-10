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


void delete_column(int matrix[][COLUMNS], size_t lines, size_t columns, size_t column_to_delete)
{
    for (size_t i = 0; i < lines; i++)
        for (size_t j = column_to_delete; j < columns - 1; j++)
            matrix[i][j] = matrix[i][j + 1];
}


bool is_digit_in_elem(int element, int digit)
{
    while (element > 0)
    {
        if (digit == element % 10)
            return true;
        element /= 10;
    }
    return false;
}

int fill_col_to_del_array(int matrix[][COLUMNS], size_t lines, size_t columns, int digit, int columns_to_delete[], size_t count)
{
    for (size_t i = 0; i < lines; i++)
        for (size_t j = 0; j < columns; j++)
        {
            if (is_digit_in_elem(matrix[i][j], digit))
            {
                count--;
                columns_to_delete[j] = 1; 
            }
        }
    return count;
}

void reform_matrix(int matrix[][COLUMNS], int columns_to_delete[], size_t lines, size_t columns)
{
    for (size_t i = 0; i < columns; i++)
    {
        if (columns_to_delete[i])
            delete_column(matrix, lines, columns, i);
    }
}

void print_matrix(int matrix[][COLUMNS], size_t lines, size_t columns)
{
    for (size_t i = 0; i < lines; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
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
    int digit;
    
    int columns_to_delete[COLUMNS];
    printf("Введите кол-во строк и кол-во столбцов матрицы (до 10 каждый параметр)\n");
    if (scanf("%zu", &user_lines) !=  1 || scanf("%zu", &user_columns) != 1)
    {
        printf("Неверный формат строк или столбцов\n");
        return EXIT_FAILURE;
    }
    
    if (user_lines > LINES || user_lines == 0 || user_columns > COLUMNS || user_columns == 0)
    {
        printf("Неверные значения для кол-ва строк или кол-ва столбцов\n");
        return EXIT_FAILURE;
    }

    size_t count_delete_cols = user_columns;
    size_t counted_cols = 0;

    printf("Введите матрицу\n");
    if (!input_matrix(matrix, user_lines, user_columns))
    {
        printf("Ошибка ввода матрицы\n");
        return EXIT_FAILURE;
    }
    printf("Введите цифру\n");

    if (scanf("%d", &digit) != 1)
    {
        printf("Неверный формат ввода цифры");
        return EXIT_FAILURE;
    }
    if (digit < 0 || digit > 9)
    {
        printf("Не цифра");
        return EXIT_FAILURE;
    }
    counted_cols = fill_col_to_del_array(matrix, user_lines, user_columns, digit, columns_to_delete, count_delete_cols);
    print_result(columns_to_delete, user_columns);
    reform_matrix(matrix, columns_to_delete, user_lines, user_columns);
    printf("Рельтирующая матрица:\n");
    print_matrix(matrix, user_lines, counted_cols);

    return EXIT_SUCCESS;
}