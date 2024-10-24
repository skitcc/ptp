#include "check_operations.h"

// Вспомогательная функция для создания матрицы с заданными размерами
static matrix_data_t *create_matrix(int rows, int cols) 
{
    matrix_data_t *matrix = malloc(sizeof(matrix_data_t));
    if (!matrix)
        return NULL;

    matrix->rows = rows;
    matrix->cols = cols;

    matrix->matrix = malloc(rows * sizeof(int *) + rows * cols * sizeof(int));
    if (!matrix->matrix) {
        free(matrix);
        return NULL;
    }

    int *data = (int *)(matrix->matrix + rows);
    for (int i = 0; i < rows; i++) {
        matrix->matrix[i] = data + i * cols;
    }

    return matrix;
}

START_TEST(test_add_matrices_success) 
{
    matrix_data_t *matrix_a = create_matrix(2, 2);
    matrix_data_t *matrix_b = create_matrix(2, 2);
    result_data_t result;

    // Инициализируем матрицы
    matrix_a->matrix[0][0] = 1; matrix_a->matrix[0][1] = 2;
    matrix_a->matrix[1][0] = 3; matrix_a->matrix[1][1] = 4;

    matrix_b->matrix[0][0] = 5; matrix_b->matrix[0][1] = 6;
    matrix_b->matrix[1][0] = 7; matrix_b->matrix[1][1] = 8;

    // Выполняем сложение
    int res = add(matrix_a, matrix_b, &result);

    // Проверяем результат
    ck_assert_int_eq(res, 0);
    ck_assert_int_eq(result.matrix[0][0], 6);
    ck_assert_int_eq(result.matrix[0][1], 8);
    ck_assert_int_eq(result.matrix[1][0], 10);
    ck_assert_int_eq(result.matrix[1][1], 12);

    // Освобождаем память
    free(matrix_a->matrix);
    free(matrix_b->matrix);
    free(result.matrix);
}
END_TEST

START_TEST(test_multiply_matrices_success) {
    matrix_data_t *matrix_a = create_matrix(2, 3);
    matrix_data_t *matrix_b = create_matrix(3, 2);
    result_data_t result;

    // Инициализируем матрицу A (2x3)
    matrix_a->matrix[0][0] = 1; matrix_a->matrix[0][1] = 2; matrix_a->matrix[0][2] = 3;
    matrix_a->matrix[1][0] = 4; matrix_a->matrix[1][1] = 5; matrix_a->matrix[1][2] = 6;

    // Инициализируем матрицу B (3x2)
    matrix_b->matrix[0][0] = 7; matrix_b->matrix[0][1] = 8;
    matrix_b->matrix[1][0] = 9; matrix_b->matrix[1][1] = 10;
    matrix_b->matrix[2][0] = 11; matrix_b->matrix[2][1] = 12;

    // Выполняем умножение
    int res = multiply(matrix_a, matrix_b, &result);

    // Проверяем результат
    ck_assert_int_eq(res, 0);
    ck_assert_int_eq(result.matrix[0][0], 58);  // 1*7 + 2*9 + 3*11 = 58
    ck_assert_int_eq(result.matrix[0][1], 64);  // 1*8 + 2*10 + 3*12 = 64
    ck_assert_int_eq(result.matrix[1][0], 139); // 4*7 + 5*9 + 6*11 = 139
    ck_assert_int_eq(result.matrix[1][1], 154); // 4*8 + 5*10 + 6*12 = 154

    // Освобождаем память
    free(matrix_a->matrix);
    free(matrix_b->matrix);
    free(result.matrix);
}
END_TEST

START_TEST(test_add_matrices_size_mismatch) 
{
    matrix_data_t *matrix_a = create_matrix(2, 2);
    matrix_data_t *matrix_b = create_matrix(3, 3);
    result_data_t result;

    matrix_a->matrix[0][0] = 1; matrix_a->matrix[0][1] = 2;
    matrix_a->matrix[1][0] = 4; matrix_a->matrix[1][1] = 5;

    // Инициализируем матрицу B (3x2)
    matrix_b->matrix[0][0] = 7; matrix_b->matrix[0][1] = 8, matrix_b->matrix[0][2] = 10;
    matrix_b->matrix[1][0] = 9; matrix_b->matrix[1][1] = 10, matrix_b->matrix[1][2] = 10;
    matrix_b->matrix[2][0] = 11; matrix_b->matrix[2][1] = 12, matrix_b->matrix[2][2] = 10;

    int res = add(matrix_a, matrix_b, &result);

    // Ожидаем ошибку из-за несоответствия размеров матриц
    ck_assert_int_eq(res, ERR_ADD_SIZES);

}
END_TEST

START_TEST(test_multiply_matrices_size_mismatch) {
    matrix_data_t *matrix_a = create_matrix(2, 3);
    matrix_data_t *matrix_b = create_matrix(2, 2);
    result_data_t result;

    int res = multiply(matrix_a, matrix_b, &result);

    // Ожидаем ошибку из-за несоответствия размеров матриц
    ck_assert_int_eq(res, ERR_MUL_SIZES);

    // Освобождаем память
    free(matrix_a->matrix);
    free(matrix_b->matrix);
}
END_TEST

Suite* matrix_operations_suite(void) 
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Matrix Operations");

    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_add_matrices_success);
    tcase_add_test(tc_core, test_multiply_matrices_success);
    tcase_add_test(tc_core, test_add_matrices_size_mismatch);
    tcase_add_test(tc_core, test_multiply_matrices_size_mismatch);

    suite_add_tcase(s, tc_core);

    return s;
}