#include "matrix_info.h"
#include "matrix_operations.h"
#include "solve_task.h"


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LINES 10
#define COLUMNS 10

void print_array(int array[], int lenght)
{
    for (int i = 0; i < lenght; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");

}
int main(void)
{
    int matrix[LINES][COLUMNS];
    size_t user_lines, user_columns;
    int array_to_shift[LINES * COLUMNS];
    if (process_matrix_size(&user_lines, &user_columns))
        return EXIT_FAILURE;

    if (process_matrix(matrix, user_lines, user_columns))
        return EXIT_FAILURE;

    int lenght = fill_array(matrix, user_lines, user_columns, array_to_shift);
    if (!lenght)
    {
        printf("В матрице нет элементов, сумма чисел которых больше десяти\n");
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < 3; i++)
        shift_array(array_to_shift, lenght);

    refill_matrix(matrix, user_lines, user_columns, array_to_shift);
    print_matrix(matrix, user_lines, user_columns);
    return EXIT_SUCCESS;
}