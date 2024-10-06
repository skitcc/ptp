#include "operations.h"

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
    const int *start_src = pb_src;
    int sum = 0;
    int counter = 0;

    while (start_src <= pe_src)
    {
        sum += *start_src;  
        start_src++;
    }
    
    int temp_sum = sum;
    start_src = pb_src;

    while (start_src < pe_src)
    {
        temp_sum -= *start_src;
        if (*start_src > temp_sum)
            counter++;
        
        start_src++;
    }

    *pb_dst = malloc(counter * sizeof(int));
    if (*pb_dst == NULL)
        return 1;

    *pe_dst = *pb_dst + counter - 1; 
    start_src = pb_src;
    temp_sum = sum;

    int *current_dst = *pb_dst;
    while (pb_src < pe_src)
    {
        temp_sum -= *pb_src;
        if (*pb_src > temp_sum)
        {
            *current_dst = *pb_src;  
            current_dst++; 
        }
        pb_src++;
    }

    return 0;
}
int cpy_arr(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
    size_t n = pe_src - pb_src;
    *pb_dst = malloc(n * sizeof(int));
    if (pb_dst == NULL)
        return 1;
    *pe_dst = *pb_dst + n;

    int *current_dst = *pb_dst;
    printf("here\n");

    while (current_dst <= pe_src)
    {
        *current_dst = *pb_src;
        printf("current : %d\n", *current_dst);
        current_dst++;
        pb_src++;
    }
    return 0;
}

void swap(void *a, void *b, size_t size)
{
    void *temp = malloc(size);
    if (temp == NULL)
        return;
    
    memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);

    free(temp);
}

int compare_ints(const void *a, const void *b)
{
    int int_a = *(const int *)a;
    int int_b = *(const int *)b;
    return (int_a > int_b) - (int_a < int_b);
}

void my_sort(void *base, size_t num, size_t size, int (*compare)(const void *, const void *))
{

    for (size_t i = 0; i < num - 1; i++)
    {
        for (size_t j = 0; j < num - i - 1; j++)
        {
            void *elem1 = (char *)base + j * size;
            void *elem2 = (char *)base + (j + 1) * size;
            if (compare(elem1, elem2) > 0)
                swap(elem1, elem2, size);

        }
    }
}