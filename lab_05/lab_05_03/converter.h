#ifndef CONVERTER_H
#define CONVERTER_H

#include "file_checker.h"
#include "constraints.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int txt_bin(const char *input_file, const char *output_file);
int bin_txt(const char *input_file, const char *output_file);

#endif