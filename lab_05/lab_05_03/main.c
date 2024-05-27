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
    int code_return_create = 0;
    int code_return_print = 0;
    int code_return_sort = 0;
    int code_return_import = 0, code_return_export = 0;
    char res[256] = { "" };
    switch (option)
    {
        case CREATE_OPTION:
            code_return_create = write_numbers(argv);
            if (code_return_create != 0)
                return code_return_create;
            break;
        case PRINT_OPTION:
            code_return_print = print_numbers(argv, res);
            if (code_return_print != 0)
                return code_return_print;
            printf("%s", res);
            break;
        case SORT_OPTION:
            code_return_sort = sort_numbers(argv);
            if (code_return_sort)
                return code_return_sort;
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
