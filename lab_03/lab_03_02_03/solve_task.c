#include "solve_task.h"

// Функция для проверки, содержит ли число указанную цифру
int contains_digit(int num, int digit) 
{
    if (num == digit)
        return 1;
    
    while (num != 0) 
    {
        if (num % 10 == digit) 
            return 1;  
        num /= 10;
    }
    return 0;  
}


// Функция для удаления столбцов, содержащих заданную цифру
void remove_column(int (*matrix)[COLUMNS], size_t lines, size_t columns, size_t col) 
{
    for (size_t i = 0; i < lines; i++) 
    {
        for (size_t j = col; j < columns - 1; j++) 
        {
            matrix[i][j] = matrix[i][j + 1];
        }
    }
}

int remove_columns_with_digit(int (*matrix)[COLUMNS], size_t *lines, size_t *columns, int digit) 
{
    for (size_t j = 0; j < *columns; j++) 
    {
        int is_digit_in_column = 0;
        for (size_t i = 0; i < *lines; i++) 
        {
            if (contains_digit(abs(matrix[i][j]), digit)) 
            {
                is_digit_in_column = 1;
                break;
            }
        }

        if (is_digit_in_column) 
        {
            remove_column(matrix, *lines, *columns, j);
            (*columns)--;
            j--;
        }
    }
    if (*columns == 0)
        return 1;
    return 0;
}