#include <stdio.h>
#include <stdlib.h>

#define N 10
#define BOTTOM 0
#define POS_RETURN_CODE 0
#define NEG_RETURN_CODE 1
#define INPUT_NUMBER 1

int input_array(int *start, size_t size)
{   
    for (size_t i = 0; i < size; i++)
    {
        if (scanf("%d", start + i) != 1)
            return NEG_RETURN_CODE;
    }
    return POS_RETURN_CODE;
}

int count_pos_elem(int *start, size_t size)
{   
    int pos = 0;
    for (size_t i = 0; i < size; i++)
    {
        if (*(start + i) > 0)
            pos++;
    }
    return pos;
}

int count_neg_elem(int *start, size_t size)
{
    int neg = 0;
    for (size_t i = 0; i < size; i++)
    {
        if (*(start + i) < 0)
            neg++;
    }
    return neg;
}

int solve(int *start, int *end)
{
    int *neg = start, *pos = end;
    int res = 0;
    while (neg <= end && pos >= start)
        if (*pos > 0 && *neg < 0)
            res += *pos-- * *neg++;
        else if (*pos <= 0)
            pos--;
        else if (*neg >= 0)
            neg++;
    return res;
}

int main(void)
{  
    int a[N];
    int *start = a;
    int user_size = 0, pos_elements = 0, neg_elements = 0;
    int res = 0;
    printf("Введите длину массива до десяти элементов\n");
    if (scanf("%d", &user_size) != INPUT_NUMBER || user_size <= BOTTOM || user_size > N)
    {
        printf("Ошибка при вводе размера массива\n");
        return EXIT_FAILURE;
    }
    if (input_array(start, user_size) == NEG_RETURN_CODE)
    {
        printf("Ошибка при вводе массива\n");
        return EXIT_FAILURE;
    }
    int *end = a + user_size - 1;
    pos_elements = count_pos_elem(start, user_size);
    neg_elements = count_neg_elem(start, user_size);
    if (pos_elements == 0)
    {
        printf("В массиве нет положительных элементов\n");
        return EXIT_FAILURE;
    }
    if (neg_elements == 0)
    {
        printf("В массиве нет отрицательных элементов\n");
        return EXIT_FAILURE;
    }
    res = solve(start, end);
    printf("Result : %d\n", res);
}