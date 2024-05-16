#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

#ifndef SIZE
#error "WTF Billy"
#endif

#ifndef SORT
#error "WTF Billy2"
#endif

#define REPEATS 1000
#define N 100
#define POS_RETURN_CODE 100

void selection_sort_with_ind(int a[], size_t n);
void selection_sort_with_replace(int a[], size_t n);
void selection_sort_with_pointers(int a[], size_t n);

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

void selection_sort_with_ind(int a[], size_t n)
{
    for (size_t i = 0; i < n - 1; i++)
    {
        for (size_t j = 0; j < n - i - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

void selection_sort_with_replace(int a[], size_t n)
{
    for (size_t i = 0; i < n - 1; i++)
    {
        for (size_t j = 0; j < n - i - 1; j++)
        {
            if (*(a + j) > *(a + j + 1))
            {
                int temp = *(a + j);
                *(a + j) = *(a + j + 1);
                *(a + j + 1) = temp;
            }
        }
    }
}

void selection_sort_with_pointers(int a[], size_t n)
{
    for (int *ptr = a; ptr < a + n - 1; ptr++)
    {
        int *current = ptr; 

        for (int *j = current + 1; j < a + n; j++)
        {
            if (*current > *j)
            {
                int temp = *current;
                *current = *j;
                *j = temp;
            }
        }
    }
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

    double mean = 0.0;
    double sum_squared = 0.0;
    double s = 0.0;
    double std_err = 0.0;
    size_t iterations = 0;
    for (size_t i = 0; i < REPEATS; i++)
    {
        mean += calculate_time(a, SIZE, sorting_function);
    }
    mean /= REPEATS;
    while (true) {
        double time = calculate_time(a, SIZE, sorting_function);
        printf("%lf\n", time);
        if (iterations > 15)
        {

            sum_squared += (time - mean) * (time - mean);
            s = sqrt(sum_squared / iterations);

            std_err = s / sqrt(iterations + 1);

            double rse = (std_err / mean) * 100;
            
            if (rse < 1.0) {
                return 1;
            }
        }
        iterations++;
        if (iterations >= REPEATS) {
            return 2;
        }
    }


    return EXIT_SUCCESS;
}
