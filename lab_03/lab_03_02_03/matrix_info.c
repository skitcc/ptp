#include "matrix_info.h"
// Обработка размеров матрицы
int process_matrix_size(size_t *lines, size_t *columns)
{
    printf("Введите кол-во строк и кол-во столбцов матрицы (до десяти каждый параметр)\n");
    if (scanf("%zu", lines) != 1 || scanf("%zu", columns) != 1)
    {
        printf("Неверный формат строк или столбцов\n");
        return EXIT_FAILURE;
    }
    
    if (*lines > LINES || *lines == 0 || *columns > COLUMNS || *columns == 0)
    {
        printf("Неверные значения для кол-ва строк или кол-ва столбцов\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
// Обработка ввода матрицы
int process_matrix(int (*matrix)[COLUMNS], size_t lines, size_t columns)
{
    printf("Введите матрицу\n");
    if (!input_matrix(matrix, lines, columns))
    {
        printf("Ошибка ввода матрицы\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int process_digit(int *digit)
{
    printf("Введите цифру для поиска\n");
    if (scanf("%d", digit) != 1)
    {
        printf("Введена не цифра\n");
        return EXIT_FAILURE;
    }

    if (*digit < 0 || *digit > 9)
    {
        printf("Цифра должна быть от нуля до девяти\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}