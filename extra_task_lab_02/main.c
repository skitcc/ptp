#include <stdio.h>
#include <stdlib.h>

#define INPUT_NUMBER 1

// Функция для ввода массива
int input_array(int a[], size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        if (scanf("%d", &a[i]) != INPUT_NUMBER)
            return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
// Проверка на существование хотя бы одного числа, подходящего под условие для суммы
int check_digits_for_sum(int a[], size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        if (abs(a[i]) % 2 != 0 && abs(a[i]) % 3 == 0)
            return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}
// Проверка на существование хотя бы одного числа, подходящего под условие для произведения 
int check_digits_for_prod(int a[], size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        if (abs(a[i]) % 2 == 0 && abs(a[i]) % 3 != 0)
            return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}
// Вычисление суммы чисел, подходящих под условие
int summ_digits(int a[], size_t size)
{
    int sum = 0;
    for (size_t i = 0; i < size; i++)
    {
        if (abs(a[i]) % 2 != 0 && abs(a[i]) % 3 == 0)
            sum += a[i];
    }
    return sum;
}
// Вычисление произведения чисел, подходящих под условие
int prod_digits(int a[], size_t size)
{
    int prod = 1;
    for (size_t i = 0; i < size; i++)
    {
        if (abs(a[i]) % 2 == 0 && abs(a[i]) % 3 != 0)
            prod *= a[i];
    }
    return prod;
}

int print_result(int is_sum, int is_prod, int sum, int prod)
{
    if (is_sum == 1 && is_prod != 1)
    {
        printf("Произведение чисел = %d\n", prod);
    }
    else if (is_sum != 1 && is_prod == 1)
    {
        printf("Сумма чисел = %d\n", sum);
    }
    else if (is_sum == 0 && is_prod == 0)
    {
        printf("Сумма чисел = %d\n", sum);
        printf("Произведение чисел = %d\n", prod);
    }
    else if (is_sum == 1 && is_prod == 1)
    {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}


int main(void)
{
    int un;
    if (scanf("%d", &un) != 1)
    {
        return EXIT_FAILURE;
    }
    int a[un];
    int summary, product;
    int is_sum = 0, is_prod = 0;
    printf("Введите %d элементов массива :\n", un);
    if (input_array(a, un) == EXIT_FAILURE)
    {
        printf("Ошибка при вводе массива!\n");
        return EXIT_FAILURE;
    }
    if (check_digits_for_sum(a, un) == EXIT_FAILURE)
    {
        printf("Нет чисел подходящих под условие для суммы\n");
        is_sum = 1;
    }


    if (check_digits_for_prod(a, un) == EXIT_FAILURE)
    {
        printf("Нет чисел подходящих под условие для произведения\n");
        is_prod = 1;
    }

    summary = summ_digits(a, un);
    product = prod_digits(a, un);

    if (print_result(is_sum, is_prod, summary, product) == EXIT_FAILURE){
        printf("Нет таких чисел которые подходят под условия");
        return 2;
    }

    return EXIT_SUCCESS;
}