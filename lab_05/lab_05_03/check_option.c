#include "check_option.h"

int check_and_form(int argc, char const *argv[])
{
    if (argc == 4 && strcmp(argv[1], "c") == 0)
        return CREATE_OPTION;
    else if (argc == 3 && strcmp(argv[1], "p") == 0)
        return PRINT_OPTION;
    else if (argc == 3 && strcmp(argv[1], "s") == 0)
        return SORT_OPTION;
    else if (argc == 4 && strcmp(argv[1], "import") == 0)
        return IMPORT_OPTION;
    else if (argc == 4 && strcmp(argv[1], "export") == 0)
        return EXPORT_OPTION;
    return WRONG_OPTION;
}