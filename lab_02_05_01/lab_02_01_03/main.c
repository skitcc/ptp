#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 10
#define BOTTOM 0
#define POS_RETURN_CODE 0
#define NEG_RETURN_CODE 1
#define INPUT_NUMBER 1

// Функция для ввода элементов массива
int input_array(int a[], size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        if (scanf("%d", &a[i]) != INPUT_NUMBER)  
            return NEG_RETURN_CODE;  
    }
    return POS_RETURN_CODE;  
}

// Функция для подсчета количества положительных элементов в массиве
int count_power(int a[], size_t size)
{
    int power = 0;
    for (size_t i = 0; i < size; i++)
    {
        if (a[i] > 0)
            power++;  
    }
    return power;  
}

// Функция для вычисления произведения положительных элементов массива
int count_product(int a[], size_t size)
{
    int product = 1;
    for (size_t i = 0; i < size; i++)
    {
        if (a[i] > 0)
            product *= a[i];  
    }
    return product;  
}

// Функция для подсчета количества отрицательных элементов массива
int neg_case(int a[], size_t size)
{
    int neg_elements = 0;
    for (size_t i = 0; i < size; i++)
    {
        if (a[i] < 0)
            neg_elements++;  
    }
    return neg_elements;  
}

int main(void)
{
    int power, mult, neg_elem, user_n;
    int a[N];
    double res;
    
    printf("Введите длину массива до десяти: ");
    
    // Проверяем корректность ввода длины массива
    if (scanf("%d", &user_n) != INPUT_NUMBER || user_n <= BOTTOM || user_n > N)
    {
        printf("Ошибка при вводе размера массива\n");
        return EXIT_FAILURE;
    }

    if (input_array(a, user_n) == NEG_RETURN_CODE)
    {
        printf("Ошибка при вводе массива\n");
        return EXIT_FAILURE;
    }
    
    neg_elem = neg_case(a, user_n);
    // Проверяем наличие положительных чисел
    if (neg_elem == user_n)
    {
        printf("Нет положительных элементов\n");
        return EXIT_FAILURE;
    }


    mult = count_product(a, user_n);
    power = count_power(a, user_n);
    
    
    res = pow(mult, 1.0 / power); 

    printf("Среднее геометрическое положительных чисел: %f\n", res);
    
    return EXIT_SUCCESS;
}
