#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H

#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>

#define COLUMNS 10

bool input_matrix(int (*matrix)[COLUMNS], size_t lines, size_t columns);
void print_result(int array[], size_t size);



#endif
