#include "sorting.h"

int get_number_by_pos(FILE *f, int pos)
{
    int number = 0;
    fseek(f, pos * sizeof(int), SEEK_SET);
    fread(&number, sizeof(int), 1, f);
    return number;
}

void put_number_by_pos(FILE *f, int pos, int number)
{
    fseek(f, pos * sizeof(int), SEEK_SET);
    fwrite(&number, sizeof(int), 1, f);
}

int sort_numbers(const char *argv[]) 
{
    FILE *f = fopen(argv[2], "r+b");
    if (f == NULL) 
    {
        printf("Не удалось открыть файл!\n");
        return WRONG_FILE;
    }

    fseek(f, 0, SEEK_END);
    long f_size = ftell(f);
    int count = f_size / sizeof(int);
    rewind(f);
    for (int i = 0; i < count - 1; ++i) 
    {
        for (int j = 0; j < count - i - 1; ++j) 
        {
            int num1 = get_number_by_pos(f, j);
            int num2 = get_number_by_pos(f, j + 1);
            if (num1 > num2) 
            {
                put_number_by_pos(f, j, num2);
                put_number_by_pos(f, j + 1, num1);
            }
        }
    }

    fclose(f);
    return EXIT_SUCCESS;
}