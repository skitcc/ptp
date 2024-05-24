#include "io.h"

int gen_digit()
{
    int number = rand();
    return number;
}

int write_numbers(const char *argv[])
{
    FILE *f = fopen(argv[3], "wb");
    int amount = atoi(argv[2]);
    int element = 0;
    if (f != NULL)
    {
        if (amount > 0)
        {
            for (int i = 0; i < amount; i++)
            {
                element = gen_digit(i);
                fwrite(&element, 4, 1, f);
            }
            fclose(f);
        }
        else
            return WRONG_AMOUNT;
    }
    else
        return WRONG_FILE;

    return EXIT_SUCCESS;
}


int print_numbers(const char *argv[], char *res)
{
    FILE *f = fopen(argv[2], "rb");
    int number = 0;
    char number_str[20];
    if (f != NULL)
    {
        int c = 0;
        while (fread(&number, 4, 1, f) == 1)
        {
            c++;
            sprintf(number_str, "%d", number);
            strcat(res, number_str);
            strcat(res, " ");
        }
        if (c == 0)
            return EMPTY_FILE;
    }
    else
        return WRONG_FILE;

    return EXIT_SUCCESS;
}
