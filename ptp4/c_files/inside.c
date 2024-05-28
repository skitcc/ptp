#include "sort_variations.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

#define MAX_ITERATIONS_REACHED 1
#ifndef SIZE
#error "ENTER SIZE USING -DSIZE"
#endif

#ifndef SORT
#error "ENTER SORT USING -DSORT"
#endif

#define REPEATS 10000
#define POS_RETURN_CODE 100

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
        arr[i] = rand() % 1000;
    return 0;
}

// int print_array(int *array)
// {
//     for (int i = 0; i < SIZE; i++)
//     {
//         printf("%d ", array[i]);
//     }
//     printf("\n");
//     return 0;
// }

int main(void)
{
    srand(time(NULL));
    int a[SIZE];
    init(a, SIZE);

    double mean = 0.0;
    double sum_squared = 0.0;
    double s = 0.0;
    double std_err = 0.0;
    size_t iterations = 0;
    for (size_t i = 0; i < REPEATS; i++)
    {
        mean += calculate_time(a, SIZE);
    }
    mean /= REPEATS;
    while (true) {
        init(a, SIZE);
        double time = calculate_time(a, SIZE);
        printf("%lf\n",time);
        sum_squared += (time - mean) * (time - mean);
        s = sqrt(sum_squared / iterations);

        std_err = s / sqrt(iterations + 1);

        double rse = (std_err / mean) * 100;
        if (rse < 1.0) 
        {
            printf("rse = %lf\n", rse);
            printf("iterations : %zu\n", iterations + 1);
            return EXIT_SUCCESS;
        }
        iterations++;
        if (iterations >= REPEATS) {
            printf("iterations_reached : %zu", iterations);
            return MAX_ITERATIONS_REACHED;
        }
    }

    return 2;
}
