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

double calculate_time(int array[SIZE], size_t n)
{
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);

    #if SORT == 1
        selection_sort_with_ind(array, n);
    #elif SORT == 2
        selection_sort_with_replace(array, n);
    #elif SORT == 3
        selection_sort_with_pointers(array, n);
    #else
        #error "ERROR"
    #endif
    
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
    printf("%lf\n", calculate_time(a, SIZE));
    return EXIT_SUCCESS;
}
