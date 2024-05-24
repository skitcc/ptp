#include "check_option.h"
#include "io.h"
#include "sorting.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{   

    int option = check_and_form(argc, argv);
    int rc = 0;
    int ra = 0;
    char res[256] = { "" };
    switch (option)
    {
        case 1:
            rc = write_numbers(argv);
            if (rc != 0)
                return rc;
            break;
        case 2:
            ra = print_numbers(argv, res);
            if (ra != 0)
                return ra;
            printf("%s", res);
            break;
        case 3:
            sort_numbers(argv);
            break;
        case 4:
            return 10;
            break;
    }
    return 0;
}
