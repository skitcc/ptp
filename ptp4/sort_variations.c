#include "sort_variations.h"

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


