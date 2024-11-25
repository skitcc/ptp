#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <stdbool.h>

#include "struct.h"
#include "read.h"
#include "utils.h"


list_t *concatenate(list_t *str1, list_t *str2);
int collapse_spaces(list_t *head);
int find_substring(list_t *head, list_t *sub_head);

#endif