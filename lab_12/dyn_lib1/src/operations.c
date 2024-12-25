#include "operations.h"

int key(const int *pb_src, const int *pe_src, int *pb_dst)
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
    printf("sum : %d\n", sum);
    int temp_sum = sum;
    start_src = pb_src;

    while (start_src < pe_src - 1)
    {
        temp_sum -= *start_src;
        if (*start_src > temp_sum)
            counter++;
        
        start_src++;
    }

    printf("key counter : %d\n", counter);

    start_src = pb_src;
    temp_sum = sum;

    int *current_dst = pb_dst;
    while (pb_src < pe_src - 1)
    {
        temp_sum -= *pb_src;
        if (*pb_src > temp_sum)
        {
            printf("value : %d\n", *pb_src);
            *current_dst = *pb_src;  
            current_dst++; 
        }
        pb_src++;
    }
    return EXIT_SUCCESS;
}

int cpy_arr(const int *pb_src, const int *pe_src, int *pb_dst)
{
    int *current_dst = pb_dst;

    while (pb_src < pe_src)
    {
        *current_dst = *pb_src;
        current_dst++;
        pb_src++;
    }
    return EXIT_SUCCESS;
}

