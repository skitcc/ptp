#ifndef SOLVE_TASK
#define SOLVE_TASK

#include "constraints.h"
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

int fill_array(char array[MAX_LEN_STRING / 2][MAX_SIZE_WORD + 1], char str[MAX_LEN_STRING + 1], size_t *word_count);
bool is_uniq(char array[MAX_LEN_STRING / 2][MAX_SIZE_WORD + 1], int word_count, char word[MAX_SIZE_WORD + 1], int position);
bool is_uniq_in_other(char array[MAX_LEN_STRING / 2][MAX_SIZE_WORD + 1], int word_count, char word[MAX_SIZE_WORD + 1]);
void print_result(char array1[MAX_LEN_STRING / 2][MAX_SIZE_WORD + 1], char array2[MAX_LEN_STRING / 2][MAX_SIZE_WORD + 1], int word_count1, int word_count2, char result[MAX_LEN_STRING * 2 + 1]);


#endif
