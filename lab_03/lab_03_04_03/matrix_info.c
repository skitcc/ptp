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
    if (*lines != *columns)
    {
        printf("Матрица должна быть квадратной!\n");
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