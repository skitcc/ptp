#include "solve_task.h"
#include <stdio.h>


int main(int argc, char const *argv[])
{
    
    if (argc > 2 || argc == 1)
    {
        printf("Неверное кол-во позиционных аргументов!\n");
        return ERROR_WRONG_AMOUNT_ARGUMENTS;
    }
    FILE *f = fopen(argv[1], "r");
    int result = 0;
    if (f == NULL)
        return ERROR_WRONG_FILE;
    if (process(f, &result) != 0)
        return ERROR_NOT_VALID_DIGIT;
    printf("Кол-во чисел, больших чем ср.арифм : %d\n", result);
}
