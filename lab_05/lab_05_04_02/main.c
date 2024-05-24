#include "constraints.h"
#include "ft.h"
#include "at.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
    int code_return_ft = 0, code_return_at = 0;

    if (strcmp(argv[1], "ft") != 0 && strcmp(argv[1], "at") != 0)
    {
        // printf("Аргумент должен быть ft или at!\n");
        return WRONG_COMPARE_ARGUMENT;
    }

    if (strcmp(argv[1], "ft") == 0 && argc != 4)
    {
        // printf("Неверное кол-во позиционных аргументов для запуска с ft");
        return WRONG_AMOUNT_ARGUMENTS;
    }

    else if (strcmp(argv[1], "at") == 0 && argc != 3)
    {
        // printf("Неверное кол-во позиционных аргументов для запуска с at");
        return WRONG_AMOUNT_ARGUMENTS;
    }

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
