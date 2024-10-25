#ifndef INPUT_H
#define INPUT_H


#include "definitions.h"
#include "input.h"
#include "structs.h"
#include "math.h"
#include <stdio.h>
#include <stdlib.h>

double **input_matrix(char *filename);
int print_matrix_to_file(double **matrix, int n, int m, const char *file); 
void print_matrix(double **matrix, int n, int m);

#endif
