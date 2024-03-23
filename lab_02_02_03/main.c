#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define N 10
#define BOTTOM 0
#define POS_RETURN_CODE 0
#define NEG_RETURN_CODE 1
#define NEG_RETURN_CODE_ARMSTRONG 200
#define INPUT_NUMBER 1


int input_array(int a[], size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        if (scanf("%d", &a[i]) != INPUT_NUMBER)
            return NEG_RETURN_CODE;
    }
    return POS_RETURN_CODE;
}

bool is_armstrong_digit(int n)
{   
    if (n < 0)
        return false;

    int k, summ, temp, to_comp;
    to_comp = n;
    temp = n;
    summ = 0;
    k = 0;
    while (temp > 0)
    {   
        k++;
        temp /= 10;
    }
    while (n > 0)
    {
        summ += (int)pow((n % 10), k);
        n /= 10;
    }
    if (to_comp == summ)
        return true;
    return false;    
}

int count_armstrong_digits(int a[], size_t size)
{
    int arm_counter = 0;
    for (size_t i = 0; i < size; i++)
    {
        if (is_armstrong_digit(a[i]))
            arm_counter++;
    }
    if (arm_counter == 0)
        return NEG_RETURN_CODE_ARMSTRONG;
    return arm_counter;
}


void print_array(int b[], size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        printf("%d ", b[i]);
    }
    printf("\n");
}

void fill_arr(int a[], int b[], size_t size)
{
    int ind = 0;
    for (size_t i = 0; i < size; i++)
    {
        if (is_armstrong_digit(a[i]))
        {
            b[ind] = a[i];
            ind++;
        }
    }
}

int main(void)
{
    int a[N], b[N];
    int user_n;
    printf("Введите длину массива до десяти\n");
    if (scanf("%d", &user_n) != INPUT_NUMBER || user_n < BOTTOM || user_n > N)
    {
        printf("Ошибка при вводе размера массива\n");
        return EXIT_FAILURE;
    }
    if (input_array(a, user_n) == NEG_RETURN_CODE)
    {
        printf("Ошибка при вводе массива\n");
        return EXIT_FAILURE;
    }
    if (count_armstrong_digits(a, user_n) == NEG_RETURN_CODE_ARMSTRONG)
    {
        printf("В исходном массиве отсутствуют числа армстронга\n");
        return EXIT_FAILURE;
    }
    int mass_armstrong_size = count_armstrong_digits(a, user_n);
    fill_arr(a, b, user_n);
    printf("Массив чисел армстронга\n");
    print_array(b, mass_armstrong_size);
    
    return EXIT_SUCCESS;
}