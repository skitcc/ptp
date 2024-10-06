#include "check_args.h"

int check(int argc, const char *argv[], bool *need_filter)
{
    if (argc > 4 || argc < 2)
    {
        printf("Неверное кол-во аргументов!\n");
        return ERR_WRONG_ARGC;
    }
    if (argc == 4)
    {
        if (strcmp(argv[3], "f"))
            return 1;
        *need_filter = true;
    }
    return 0;
}