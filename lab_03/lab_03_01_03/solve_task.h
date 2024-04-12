#ifndef SOLVE_TASK_H

#define SOLVE_TASK_H

#include <stddef.h>
#include <stdbool.h>
#define COLUMNS 10

bool is_monotone(int array[], size_t size);
void form_result(int (*matrix)[COLUMNS], size_t lines, size_t columns, int res[]);
#endif
