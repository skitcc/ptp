#include "check_option.h"
#include "io.h"
#include "sorting.h"
#include "converter.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{   

    int option = check_and_form(argc, argv);
    int rc = 0;
    int ra = 0;
    int code_return_import = 0, code_return_export = 0;
    char res[256] = { "" };
    switch (option)
    {
        case CREATE_OPTION:
            rc = write_numbers(argv);
            if (rc != 0)
                return rc;
            break;
        case PRINT_OPTION:
            ra = print_numbers(argv, res);
            if (ra != 0)
                return ra;
            printf("%s", res);
            break;
        case SORT_OPTION:
            sort_numbers(argv);
            break;
        case IMPORT_OPTION:
            code_return_import = txt_bin(argv[2], argv[3]);
            if (code_return_import)
                return code_return_import;
            break;
        case EXPORT_OPTION:
            code_return_export = bin_txt(argv[2], argv[3]);
            if (code_return_export)
                return code_return_export;
            break;
        default:
            return WRONG_OPTION;
    }
    return 0;
}
