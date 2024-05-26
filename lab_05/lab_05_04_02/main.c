#include "constraints.h"
#include "ft.h"
#include "at.h"
#include "check_args.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
    int code_return_ft = 0, code_return_at = 0;
    int code_return = args_checker(argc, argv);
    
    if (code_return != 0)
        return code_return;

    if (strcmp(argv[1], "ft") == 0)
    {
        code_return_ft = fill_name(argv[2], argv[3]);
        if (code_return_ft != 0)
            return code_return_ft;
    }
    
    if (strcmp(argv[1], "at") == 0)
    {
        code_return_at = insert_field_in_pos(argv);
        if (code_return_at != 0)
            return code_return_at;
    }
}
