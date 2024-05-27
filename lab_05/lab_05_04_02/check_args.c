#include "check_args.h"

int args_checker(int argc, const char *argv[])    
{
    if (argc == 1 || argc == 0 || argc > 4)
    {
        printf("Кол-во аргументов не может быть нулевое\n");
        return WRONG_AMOUNT_ARGUMENTS;
    }
    if (strcmp(argv[1], "ft") != 0 && strcmp(argv[1], "at") != 0)
    {
        printf("Аргумент должен быть ft или at!\n");
        return WRONG_COMPARE_ARGUMENT;
    }

    if (strcmp(argv[1], "ft") == 0 && argc != 4)
    {
        printf("Неверное кол-во позиционных аргументов для запуска с ft");
        return WRONG_AMOUNT_ARGUMENTS;
    }
    else if (strcmp(argv[1], "at") == 0 && argc != 3)
    {
        printf("Неверное кол-во позиционных аргументов для запуска с at");
        return WRONG_AMOUNT_ARGUMENTS;
    }
    return EXIT_SUCCESS;
}