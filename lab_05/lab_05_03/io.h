#ifndef IO_H
#define IO_H

#include "file_checker.h"
#include "constraints.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int gen_digit();
int write_numbers(const char *argv[]);
int print_numbers(const char *argv[], char *res);


#endif