#ifndef MATRIX_INFO_H
#define MATRIX_INFO_H

#include "matrix_operations.h"
#include <stdio.h>
#include <stdlib.h>


#define COLUMNS 10
#define LINES 10

int process_matrix_size(size_t *lines, size_t *columns);
int process_matrix(int (*matrix)[COLUMNS], size_t lines, size_t columns);



#endif
