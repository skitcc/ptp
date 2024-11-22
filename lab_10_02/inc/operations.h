#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <stdbool.h>

#include "struct.h"
#include "read.h"
#include "utils.h"


list_t *concatenate(list_t *str1, list_t *str2);
void collapse_spaces(list_t *head);

#endif