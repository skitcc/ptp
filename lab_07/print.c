#include "print.h"

int print_to_file(const int *pb, const int *pe, char *filename)
{
    FILE *f = fopen(filename, "w");

    if (f == NULL)
    {
        printf("Ошибка в открытии файла для записи!\n");
        return 1;
    }

    while (pb <= pe)
    {
        fprintf(f, "%d ", *pb);
        pb++;
    }
    fprintf(f, "\n");

    fclose(f);
    return 0;
}