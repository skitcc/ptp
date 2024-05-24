#include "check_option.h"

int check_and_form(int argc, char const *argv[])
{
    if (argc == 4 && strcmp(argv[1], "c") == 0)
        return 1;
    else if (argc == 3 && strcmp(argv[1], "p") == 0)
        return 2;
    else if (argc == 3 && strcmp(argv[1], "s") == 0)
        return 3;
    return 4;
}