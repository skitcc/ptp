#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H


#include "definitions.h"
#include "structs.h"
#include "input.h"

#include <stdio.h>
#include <stdlib.h>


int add(matrix_data_t *matrix_a, matrix_data_t *matrix_b, result_data_t *result);
int multiply(matrix_data_t *matrix_a, matrix_data_t *matrix_b, result_data_t *result);


#endif
