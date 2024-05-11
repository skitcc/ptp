#ifndef SOLVE_TASK_H
#define SOLVE_TASK_H


#include "constraints.h"
#include <stdio.h>
#include <string.h>
#include <stddef.h>


void fill_first_occurrences(char *str);
void compare_to_last(char array[MAX_LEN_STRING / 2][MAX_SIZE_WORD + 1], size_t word_count, char result[MAX_LEN_STRING + 1]);
int fill_array(char array[MAX_LEN_STRING / 2][MAX_SIZE_WORD + 1], char str[MAX_LEN_STRING + 1], size_t *word_count);

#endif
