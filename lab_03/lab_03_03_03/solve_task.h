#ifndef SOLVE_TASK_H
#define SOLVE_TASK_H

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

#define COLUMNS 10

void fill_array_of_mins(int (*matrix)[COLUMNS], size_t lines, size_t columns, int array[]);
void sort_matrix(int (*matrix)[COLUMNS], size_t lines, size_t columns, int array[]);



#endif
