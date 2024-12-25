#include "my_sort.h"

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


void mysort(void *base, size_t num, size_t size, int (*compare)(const void *, const void *))
{
    if (num == 0)
        return;
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
