#include "matrix_operations.h"
#include "solve_task.h"
#include "matrix_info.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define LINES 10
#define COLUMNS 10


int main() 
{
    int matrix[LINES][COLUMNS];
    size_t user_lines, user_columns;
    int digit;

    if (process_matrix_size(&user_lines, &user_columns))
        return EXIT_FAILURE;

    if (process_matrix(matrix, user_lines, user_columns))
        return EXIT_FAILURE;


    if (process_digit(&digit))
        return EXIT_FAILURE;

    if (remove_columns_with_digit(matrix, &user_lines, &user_columns, digit))
        return EXIT_FAILURE;


    print_matrix(matrix, user_lines, user_columns);

    return 0;
}
