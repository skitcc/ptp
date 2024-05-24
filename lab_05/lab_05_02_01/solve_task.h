#ifndef SOLVE_TASK_H
#define SOLVE_TASK_H


#include "constraints.h"
#include <stdio.h>

int find_min_max(FILE *f, double *mn, double *mx);
int find_average(FILE *f, double *average);
int process(FILE *f, int *res);



#endif