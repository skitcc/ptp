#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 100
#define MAX_SIZE 10
#define POS_RETURN_CODE 100

void selection_sort(int a[], size_t n)
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

int main(void) 
{
    int a[N];
    int n = 0; 
    for (int i = 0; i < N; i++) 
    {
        if (scanf("%d", &a[i]) != 1)
            break;
        if (n > MAX_SIZE)
            break;
        n++; 
    }
    if (n == 0)
    {
        printf("В массиве нет элемента");
        return EXIT_FAILURE;
    }
    selection_sort(a, n);




    for (int i = 0; i < n && i < MAX_SIZE; i++) 
        printf("%d ", a[i]);
    if (n > MAX_SIZE) 
        return POS_RETURN_CODE;

    return EXIT_SUCCESS;
}