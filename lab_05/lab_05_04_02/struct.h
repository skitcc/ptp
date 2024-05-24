#ifndef STRUCT_H
#define STRUCT_H

#include "constraints.h"
#include <stdint.h>

struct product
{
    char name[NAME_LEN + 1];
    char producer[PRODUCER_LEN + 1];
    uint32_t price;
    uint32_t quantity;
};

#endif