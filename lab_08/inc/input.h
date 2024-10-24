#ifndef INPUT_H
#define INPUT_H


#include "definitions.h"
#include "input.h"
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>

int **input_matrix(char *filename);
void print_matrix_to_file(int **matrix, int n, int m, char *file);
void print_matrix(int **matrix, int n, int m);

#endif
