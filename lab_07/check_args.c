#include "check_args.h"

int check(int argc, const char *argv[], bool *need_filter)
{
    if (argc < 3)
    {
        printf("Аргументов слишком мало!\n");
        return ERR_WRONG_ARGC;
    }
    if (argc > 4)
    {
        printf("Аргументов слишком много!\n");
        return ERR_WRONG_ARGC;
    }
    if (argc == 4)
    {
        if (strcmp(argv[3], "f"))
        {
            printf("Последний параметр должен иметь значение f!\n");
            return ERR_WRONG_FILTER;
        }
        *need_filter = true;
    }
    return EXIT_SUCCESS;
}