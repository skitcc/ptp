#include "input_output.h"
#include "solve_task.h"


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LINES 10
#define COLUMNS 10




int main(void)
{
    int matrix[LINES][COLUMNS];
    int user_lines, user_columns;

    if (process_matrix_size(&user_lines, &user_columns))
        return EXIT_FAILURE;

    int n = user_lines;
    spiral_fill(matrix, n);
    print_matrix(matrix, n);
    return EXIT_SUCCESS;
}