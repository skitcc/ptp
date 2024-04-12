#include "matrix_operations.h"
#include "solve_task.h"
#include "matrix_info.h"

#include <stdio.h>
#include <stdlib.h>

#define LINES 10
#define COLUMNS 10


int main(void)
{
    int matrix[LINES][COLUMNS];
    size_t user_lines, user_columns;
    int res[LINES];
    if (process_matrix_size(&user_lines, &user_columns))
        return EXIT_FAILURE;

    if (process_matrix(matrix, user_lines, user_columns))
        return EXIT_FAILURE;

    form_result(matrix, user_lines, user_columns, res);
    printf("Результат:\n");
    print_result(res, user_lines);

    return EXIT_SUCCESS;
}
