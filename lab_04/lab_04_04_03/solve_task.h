#ifndef SOLVE_TASK_H
#define SOLVE_TASK_H

#include "constraints.h"
#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

int check_phone_number(char str[MAX_LEN_STRING + 1]);
int check_code_operator(char str[MAX_LEN_STRING + 1], int *counter);
int check_digits(char str[MAX_LEN_STRING + 1], int *counter, int len);



#endif
