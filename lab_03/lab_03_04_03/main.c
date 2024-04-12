#include "matrix_info.h"
#include "matrix_operations.h"
#include "solve_task.h"


#include <stdio.h>
#include <stdlib.h>

#define LINES 10
#define COLUMNS 10


int main(void)
{
    int matrix[LINES][COLUMNS];
    size_t user_lines, user_columns;

    if (process_matrix_size(&user_lines, &user_columns))
        return EXIT_FAILURE;

    if (process_matrix(matrix, user_lines, user_columns))
        return EXIT_FAILURE;

    sorting_matrix(matrix, user_lines, user_columns);
    print_matrix(matrix, user_lines, user_columns);
    return EXIT_SUCCESS;
}