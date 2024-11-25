#ifndef STRUCTS_H
#define STRUCTS_H

#include "definitions.h"

typedef struct list
{
    char part[PART_SIZE];
    struct list *next;
} list_t;



#endif