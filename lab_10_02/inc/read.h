#ifndef READ_H
#define READ_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#include "struct.h"
#include "definitions.h"


int read_str_to_list(char *str, list_t **head);
int create_node(list_t **node);

#endif