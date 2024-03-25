#include <stdio.h>
#include <stdlib.h>

#define N 10
#define BOTTOM 0
#define POS_RETURN_CODE 0
#define NEG_RETURN_CODE 1
#define INPUT_NUMBER 1

// Функция для ввода массива
int input_array(int *start, int *end)
{   
    for (int *i = start; i < end; i++)
    {
        if (scanf("%d", i) != 1) 
            return NEG_RETURN_CODE; 
    }
    return POS_RETURN_CODE; 
}

// Функция для подсчета положительных элементов в массиве
int count_pos_elem(int *start, int *end)
{   
    int pos = 0;
    for (int *i = start; i < end; i++)
    {
        if (*i > 0) 
            pos++; 
    }
    return pos; 
}

// Функция для подсчета отрицательных элементов в массиве
int count_neg_elem(int *start, int *end)
{
    int neg = 0;
    for (int *i = start; i < end; i++)
    {
        if (*i < 0) 
            neg++; 
    }
    return neg; 
}

// Функция для решения задачи по заданному алгоритму
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
    int a[N]; // Объявление массива
    int *start = a; // Указатель на начало массива
    int user_size = 0;
    int pos_elements = 0, neg_elements = 0;
    int res = 0; // Переменная для результата
    
    // Ввод размера массива
    printf("Введите длину массива до десяти элементов\n");
    
    // Проверка корректности ввода и ограничений на размер
    if (scanf("%d", &user_size) != INPUT_NUMBER || user_size <= BOTTOM || user_size > N)
    {
        printf("Ошибка при вводе размера массива\n");
        return EXIT_FAILURE;
    }
    int *end = a + user_size; // Указатель на конец массива
    
    // Ввод массива
    if (input_array(start, end) == NEG_RETURN_CODE)
    {
        printf("Ошибка при вводе массива\n");
        return EXIT_FAILURE;
    }
    
    pos_elements = count_pos_elem(start, end); // Подсчет положительных элементов
    neg_elements = count_neg_elem(start, end); // Подсчет отрицательных элементов
    
    // Проверка наличия положительных элементов
    if (pos_elements == 0)
    {
        printf("В массиве нет положительных элементов\n");
        return EXIT_FAILURE;
    }
    
    // Проверка наличия отрицательных элементов
    if (neg_elements == 0)
    {
        printf("В массиве нет отрицательных элементов\n");
        return EXIT_FAILURE;
    }
    end--;
    
    res = solve(start, end); // Решение задачи алгоритмом
    
    printf("Result : %d\n", res); // Вывод результата
    
    return EXIT_SUCCESS; // Успешное завершение программы
}
