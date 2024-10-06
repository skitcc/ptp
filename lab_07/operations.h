#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "definitions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);
int cpy_arr(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);
void my_sort(void *base, size_t num, size_t size, int (*compare)(const void *, const void *));
int compare_ints(const void *a, const void *b);

#endif