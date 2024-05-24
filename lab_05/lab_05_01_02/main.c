#include "process.h"

#include <stdio.h>


int main(void)
{
    FILE *f = stdin;
    int code_return = process(f);
    if (code_return != 0)
        return ERROR_NO_NUMBERS;
    return 0;
}
