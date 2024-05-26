#ifndef READ_DATA_H
#define READ_DATA_H

#include "constraints.h"
#include "struct.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>

int check_fields(FILE *input, struct product products[], int *count);
int check_field(FILE *input, struct product *product_in);


#endif