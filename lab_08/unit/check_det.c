#include "check_det.h"

// Вспомогательная функция для создания квадратной матрицы
static int **create_matrix(int n)
{
    int **matrix = malloc(n * sizeof(int *) + n * n * sizeof(int));
    if (!matrix)
        return NULL;

    int *data = (int *)(matrix + n);
    for (int i = 0; i < n; i++)
    {
        matrix[i] = data + i * n;
    }

    return matrix;
}

// Тест на вычисление детерминанта матрицы 1x1
START_TEST(test_determinant_1x1)
{
    int error_code = 0; 
    int **matrix = create_matrix(1);
    ck_assert_ptr_nonnull(matrix);

    matrix[0][0] = 5;
    int det = count_determinant(matrix, 1, &error_code);

    ck_assert_int_eq(error_code, 0);

    ck_assert_int_eq(det, 5);

    free(matrix);

}
END_TEST

// Тест на вычисление детерминанта матрицы 2x2
START_TEST(test_determinant_2x2)
{
    int error_code = 0;
    int **matrix = create_matrix(2);
    ck_assert_ptr_nonnull(matrix);

    matrix[0][0] = 1;
    matrix[0][1] = 2;
    matrix[1][0] = 3;
    matrix[1][1] = 4;

    int det = count_determinant(matrix, 2, &error_code);
    ck_assert_int_eq(error_code, 0);
    ck_assert_int_eq(det, -2);

    free(matrix);
}
END_TEST

// Тест на вычисление детерминанта матрицы 3x3
START_TEST(test_determinant_3x3)
{
    int error_code = 0;
    int **matrix = create_matrix(3);
    ck_assert_ptr_nonnull(matrix);

    matrix[0][0] = 1;
    matrix[0][1] = 2;
    matrix[0][2] = 3;
    matrix[1][0] = 0;
    matrix[1][1] = 1;
    matrix[1][2] = 4;
    matrix[2][0] = 5;
    matrix[2][1] = 6;
    matrix[2][2] = 0;

    int det = count_determinant(matrix, 3, &error_code);
    ck_assert_int_eq(error_code, 0);
    ck_assert_int_eq(det, 1);

    free(matrix);
}
END_TEST

// Тест на выделение памяти для миноров
START_TEST(test_allocate_minor)
{
    int **minor = allocate_minor(2);
    ck_assert_ptr_nonnull(minor);

    minor[0][0] = 1;
    minor[1][1] = 2;

    ck_assert_int_eq(minor[0][0], 1);
    ck_assert_int_eq(minor[1][1], 2);

    free(minor);
}
END_TEST


// Основная функция тестирования
Suite *matrix_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Matrix");

    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_determinant_1x1);
    tcase_add_test(tc_core, test_determinant_2x2);
    tcase_add_test(tc_core, test_determinant_3x3);
    tcase_add_test(tc_core, test_allocate_minor);
    suite_add_tcase(s, tc_core);

    return s;
}