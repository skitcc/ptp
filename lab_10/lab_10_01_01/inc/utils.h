#ifndef UTILS_H
#define UTILS_H

#include "definitions.h"
#include "structs.h"


#include <stdio.h>
#include <stdlib.h>

void print_list(node_t *head);
int print_list_to_file(node_t *head, char *filename);
void free_list(node_t *head);

#endif