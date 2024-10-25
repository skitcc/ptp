#ifndef DET_H
#define DET_H

#include "definitions.h"
#include "structs.h"

#include <stdio.h>
#include <stdlib.h>


double count_determinant(double **matrix, int n, int *error_code);
double **allocate_minor(int size);
#endif
