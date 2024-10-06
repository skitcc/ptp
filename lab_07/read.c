#include "read.h"

short read_quantity(char *filename, size_t *n)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL)
    {
        printf("Ошибка открытия файла!\n");
        return 1;
    }
    int digit = 0;
    int rc = 0;
    while ((rc = fscanf(f, "%d", &digit)) == 1)
    {
        (*n)++;
    }
    fclose(f);
    return (rc == EOF) ? 0 : 1;
    
}

int allocate_memory(int **start, size_t n)
{
    *start = malloc(n * sizeof(int));
    if (*start == NULL)
        return 1;
    return 0;
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


