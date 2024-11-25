#ifndef READ_H
#define READ_H

#define _GNU_SOURCE

#include "definitions.h"
#include "structs.h"
#include "utils.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int read_whole_file(node_t **head, char *filename);
int student_create(node_t **node, FILE *f);

#endif