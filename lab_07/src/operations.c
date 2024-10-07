#include "operations.h"

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
    const int *start_src = pb_src;
    int sum = 0;
    int counter = 0;
    if (pb_src >= pe_src)
        return ERR_POINTERS;

    while (start_src < pe_src)
    {
        sum += *start_src;  
        start_src++;
    }
    int temp_sum = sum;
    start_src = pb_src;

    while (start_src < pe_src - 1)
    {
        temp_sum -= *start_src;
        if (*start_src > temp_sum)
            counter++;
        
        start_src++;
    }
    if (counter == 0)
        return ERR_EMPTY_FILE_AFTER_FILTER;

    *pb_dst = malloc(counter * sizeof(int));
    if (*pb_dst == NULL)
        return ERR_ALLOC_MEM;

    *pe_dst = *pb_dst + counter; 
    start_src = pb_src;
    temp_sum = sum;

    int *current_dst = *pb_dst;
    while (pb_src < pe_src - 1)
    {
        temp_sum -= *pb_src;
        if (*pb_src > temp_sum)
        {
            *current_dst = *pb_src;  
            current_dst++; 
        }
        pb_src++;
    }
    return EXIT_SUCCESS;
}

int cpy_arr(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
    size_t n = pe_src - pb_src;
    *pb_dst = malloc(n * sizeof(int));
    if (pb_dst == NULL)
        return ERR_ALLOC_MEM;
    *pe_dst = *pb_dst + n;

    int *current_dst = *pb_dst;

    while (pb_src < pe_src)
    {
        *current_dst = *pb_src;
        current_dst++;
        pb_src++;
    }
    return EXIT_SUCCESS;
}

