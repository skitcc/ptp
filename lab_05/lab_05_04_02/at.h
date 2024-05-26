#ifndef AT_H
#define AT_H


#include "constraints.h"
#include "struct.h"
#include "read_data.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include <sys/stat.h>

int is_sorted(struct product products[], int count);
void insert_product(struct product products[], int *count, struct product product_in);
int write_products_to_file(const char *filename, struct product products[], int count);
int insert_field_in_pos(const char *argv[]);



#endif