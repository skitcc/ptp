#ifndef MY_SORT_H
#define MY_SORT_H

#include "definitions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void my_sort(void *base, size_t num, size_t size, int (*compare)(const void *, const void *));
int compare_ints(const void *a, const void *b);



#endif