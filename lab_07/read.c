#include "read.h"

short read_quantity(char *filename, size_t *n)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL)
    {
        printf("Ошибка открытия входного файла!\n");
        return ERR_OPEN_FILE;
    }
    int digit = 0;
    int rc = 0;
    while ((rc = fscanf(f, "%d", &digit)) == 1)
    {
        (*n)++;
    }
    fclose(f);
    if (*n == 0)
        return ERR_EMPTY_FILE;
    return (rc == EOF) ? EXIT_SUCCESS : EXIT_FAILURE;
    
}

void fill_array(char *filename, int *pb_src, int *pe_src)
{
    FILE *f = fopen(filename, "r");
    while (pb_src <= pe_src)
    {
        fscanf(f, "%d", pb_src);
        pb_src++;
    }
    fclose(f);
}


