#ifndef FT_H
#define FT_H


#include "constraints.h"
#include "struct.h"
#include "read_data.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>

int is_suffix(const char *name, const char *substr);
int fill_name(const char *input_filename, const char *output_filename);


#endif