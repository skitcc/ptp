#ifndef READ_H
#define READ_H


#include "definitions.h"

#include <stdio.h>
#include <stdlib.h>

short read_quantity(char *filename, size_t *n);
void fill_array(char *filename, int *pb_src, int *pe_src);

#endif  
