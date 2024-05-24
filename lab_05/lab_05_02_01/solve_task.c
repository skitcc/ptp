#include "solve_task.h"

int find_min_max(FILE *f, double *mn, double *mx)
{
    double digit = 0.0;
    if (fscanf(f, "%lf", &digit) != 1)
    {
        return ERROR_NOT_VALID_DIGIT;
    }
    double next_digit = 0;
    *mn = digit;
    *mx = digit;
    while (fscanf(f, "%lf", &next_digit) == 1)
    {
        if (next_digit > *mx)
            *mx = next_digit;
        if (next_digit < *mn)
            *mn = next_digit;
    }
    return SUCCESS;
}

int find_average(FILE *f, double *average)
{
    double mn = 0, mx = 0;
    if (find_min_max(f, &mn, &mx) != SUCCESS)
        return ERROR_NOT_VALID_DIGIT;

    *average = (mx + mn) / 2.0;
    return SUCCESS; 
}

int process(FILE *f, int *res)
{
    double average = 0.0;
    if (find_average(f, &average) != SUCCESS)
    {
        printf("Первый символ файла не валиден!\n");
        return ERROR_NOT_VALID_DIGIT;
    }
    rewind(f);
    double digit = 0.0;
    
    while (fscanf(f, "%lf", &digit) == 1)
    {
        if (digit > average)
            (*res)++;
    }
    return SUCCESS;
}