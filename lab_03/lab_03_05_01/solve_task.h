#ifndef SOLVE_TASK_H
#define SOLVE_TASK_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define COLUMNS 10

bool summ_digits(int digit);
void shift_array(int array[], int lenght);
int fill_array(int (*matrix)[COLUMNS], size_t lines, size_t columns, int array[]);
void refill_matrix(int (*matrix)[COLUMNS], size_t lines, size_t columns, int array[]);


#endif
