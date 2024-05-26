#ifndef SORTING_H
#define SORTING_H

#include "constraints.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int get_number_by_pos(FILE *f, int pos);
void put_number_by_pos(FILE *f, int pos, int number);
int sort_numbers(const char *argv[]);

#endif