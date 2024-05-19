#include "sort_variations.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

#ifndef SIZE
#error "ENTER SIZE USING -DSIZE"
#endif

#ifndef SORT
#error "ENTER SORT USING -DSORT"
#endif


#define REPEATS 1000
#define N 100
#define POS_RETURN_CODE 100

typedef void (*SortFunction)(int[], size_t);

double calculate_time(int array[SIZE], size_t n, SortFunction sorting)
{
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);

    sorting(array, n);
    
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    
    double execution_time_ms = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_nsec - start.tv_nsec) / 1e6;
    return execution_time_ms;
}

int init(int arr[SIZE], size_t n)
{
    for(size_t i = 0; i < n; i++)
        arr[i] = (int)(i * 230923 / 52);
    return 0;
}

int main(void)
{
    int a[SIZE];
    init(a, SIZE);
    SortFunction sorting_function;

    #if SORT == 1
        sorting_function = selection_sort_with_ind;
    #elif SORT == 2
        sorting_function = selection_sort_with_replace;
    #elif SORT == 3
        sorting_function = selection_sort_with_pointers;
    #else
        #error "ERROR"
    #endif

    printf("%lf\n", calculate_time(a, SIZE, sorting_function));
    return EXIT_SUCCESS;
}