#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

#define COLUMNS 10

bool input_matrix(int (*matrix)[COLUMNS], size_t lines, size_t columns);
void print_matrix(int (*matrix)[COLUMNS], size_t lines, size_t columns);



#endif
