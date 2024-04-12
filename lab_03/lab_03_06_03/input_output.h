#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 10
#define LINES 10


void print_matrix(int (*matrix)[COLUMNS], int n);
int process_matrix_size(int *lines, int  *columns);


#endif