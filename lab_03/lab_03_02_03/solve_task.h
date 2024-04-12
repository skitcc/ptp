#ifndef SOLVE_TASK_H
#define SOLVE_TASK_H

#include <stdlib.h>
#include <stdio.h>

#define COLUMNS 10

int contains_digit(int num, int digit);
int remove_columns_with_digit(int (*matrix)[COLUMNS], size_t *lines, size_t *columns, int digit);


#endif
