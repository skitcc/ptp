#ifndef DET_H
#define DET_H

#include "definitions.h"
#include "structs.h"

#include <stdio.h>
#include <stdlib.h>


int count_determinant(int **matrix, int n, int *error_code);
int **allocate_minor(int size);
#endif
