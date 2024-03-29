#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 20
#define POS_RETURN_CODE 0
#define NEG_RETURN_CODE 1
#define INPUT_NUMBER 1
#define BOTTOM 0

// Функция для ввода массива
int input_array(int a[], size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        if (scanf("%d", &a[i]) != INPUT_NUMBER)
            return NEG_RETURN_CODE; 
    }
    return POS_RETURN_CODE; 
}

// Функция для обращения числа
int reversed(int n)
{
    int b = 0;
    while (n != 0)
    {
        b = b * 10 + n % 10; 
        n /= 10;
    }
    return b; 
}

// Функция для формирования массива с добавлением реверса положительных чисел
int form_array(int a[], size_t size)
{
    for (size_t i = 0; i < size; i++) 
    {
        if (a[i] > 0) 
        {
            int reversed_number = reversed(a[i]); 
            for (size_t j = size; j > i + 1; j--)
                a[j] = a[j - 1]; // Сдвигаем элементы вправо, чтобы вставить обращенное число
            a[i + 1] = reversed_number; // Вставляем обращенное число после текущего положительного числа
            size++; // Увеличиваем размер массива
            i++; // Пропускаем следующий элемент, чтобы избежать повторной обработки
        }
    }
    return size; // Возвращаем новый размер массива
}

// Функция для печати массив
void print_array(int a[], size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        printf("%d ", a[i]); 
    }
    printf("\n"); 
}

// Основная функция программы
int main(void)
{
    int a[N];
    int user_n, new_size;
    
    printf("Введите длину массива до десяти\n");
    
    // Проверяем корректность ввода длины массива и самого массива
    if (scanf("%d", &user_n) != INPUT_NUMBER || user_n < BOTTOM || user_n > N/2)
    {
        printf("Ошибка при вводе размера массива\n");
        return EXIT_FAILURE;
    }

    if (input_array(a, user_n) == NEG_RETURN_CODE)
    {
        printf("Ошибка при вводе массива\n");
        return EXIT_FAILURE;
    }

    // Формируем новый массив с добавлением реверсных чисел
    new_size = form_array(a, user_n);
    
    printf("Массив с добавленным реверсом\n");
    print_array(a, new_size);
    
    return EXIT_SUCCESS;
}
