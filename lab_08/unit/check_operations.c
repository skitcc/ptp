#include "check_operations.h"

static double **create_matrix(int rows, int cols) 
{

    double **a = malloc(rows * sizeof(double *) + rows * cols * sizeof(double));
    if (a == NULL)
    {
        return NULL;
    }

    double *data = (double *)(a + rows); 
    for (int i = 0; i < rows; i++)
    {
        a[i] = data + i * cols;    
    }

    for (int i = 0; i < rows * cols; i++)
    {
        data[i] = 0.0;
    }

    return a;
}

START_TEST(test_add_matrices_success) 
{
    matrix_data_t matrix_a;
    matrix_data_t matrix_b;
    result_data_t result;
    result.matrix = NULL; // Initialize result matrix to NULL

    matrix_a.matrix = create_matrix(2, 2);
    matrix_b.matrix = create_matrix(2, 2);

    matrix_a.rows = 2;
    matrix_a.cols = 2;
    matrix_b.rows = 2;
    matrix_b.cols = 2;

    if (!matrix_a.matrix || !matrix_b.matrix)
    {
        if (matrix_a.matrix) free(matrix_a.matrix);
        if (matrix_b.matrix) free(matrix_b.matrix);
        ck_abort_msg("Memory allocation failed for matrices.");
    }

    // Initialize matrix values
    matrix_a.matrix[0][0] = 1; matrix_a.matrix[0][1] = 2;
    matrix_a.matrix[1][0] = 3; matrix_a.matrix[1][1] = 4;
    matrix_b.matrix[0][0] = 5; matrix_b.matrix[0][1] = 6;
    matrix_b.matrix[1][0] = 7; matrix_b.matrix[1][1] = 8;

    int res = add(&matrix_a, &matrix_b, &result);

    ck_assert_int_eq(res, 0);
    ck_assert_double_eq(result.matrix[0][0], 6);
    ck_assert_double_eq(result.matrix[0][1], 8);
    ck_assert_double_eq(result.matrix[1][0], 10);
    ck_assert_double_eq(result.matrix[1][1], 12);

    free(matrix_a.matrix);
    free(matrix_b.matrix);
    if (result.matrix) // Only free if allocated
        free(result.matrix);
}
END_TEST

START_TEST(test_add_matrices_size_mismatch) 
{
    matrix_data_t matrix_a;
    matrix_data_t matrix_b;
    result_data_t result;
    result.matrix = NULL;

    matrix_a.matrix = create_matrix(2, 2);
    matrix_b.matrix = create_matrix(3, 3);

    matrix_a.rows = 2;
    matrix_a.cols = 2;
    matrix_b.rows = 3;
    matrix_b.cols = 3;

    if (!matrix_a.matrix || !matrix_b.matrix)
    {
        if (matrix_a.matrix) free(matrix_a.matrix);
        if (matrix_b.matrix) free(matrix_b.matrix);
        ck_abort_msg("Memory allocation failed for matrices.");
    }

    int res = add(&matrix_a, &matrix_b, &result);

    ck_assert_int_eq(res, ERR_ADD_SIZES);
}
END_TEST

START_TEST(test_multiply_matrices_success) 
{
    matrix_data_t matrix_a;
    matrix_data_t matrix_b;
    result_data_t result;
    result.matrix = NULL;

    matrix_a.matrix = create_matrix(2, 3);
    matrix_b.matrix = create_matrix(3, 2);

    matrix_a.rows = 2;
    matrix_a.cols = 3;
    matrix_b.rows = 3;
    matrix_b.cols = 2;

    if (!matrix_a.matrix || !matrix_b.matrix)
    {
        if (matrix_a.matrix) free(matrix_a.matrix);
        if (matrix_b.matrix) free(matrix_b.matrix);
        ck_abort_msg("Memory allocation failed for matrices.");
    }

    matrix_a.matrix[0][0] = 1; matrix_a.matrix[0][1] = 2; matrix_a.matrix[0][2] = 3;
    matrix_a.matrix[1][0] = 4; matrix_a.matrix[1][1] = 5; matrix_a.matrix[1][2] = 6;

    matrix_b.matrix[0][0] = 7; matrix_b.matrix[0][1] = 8;
    matrix_b.matrix[1][0] = 9; matrix_b.matrix[1][1] = 10;
    matrix_b.matrix[2][0] = 11; matrix_b.matrix[2][1] = 12;

    int res = multiply(&matrix_a, &matrix_b, &result);

    ck_assert_int_eq(res, 0);
    ck_assert_double_eq(result.matrix[0][0], 58); 
    ck_assert_double_eq(result.matrix[0][1], 64);  
    ck_assert_double_eq(result.matrix[1][0], 139); 
    ck_assert_double_eq(result.matrix[1][1], 154); 

    free(matrix_a.matrix);
    free(matrix_b.matrix);
    if (result.matrix) 
        free(result.matrix);
}
END_TEST

START_TEST(test_multiply_matrices_size_mismatch) 
{
    matrix_data_t matrix_a;
    matrix_data_t matrix_b;
    result_data_t result;
    result.matrix = NULL;

    matrix_a.matrix = create_matrix(2, 2);
    matrix_b.matrix = create_matrix(3, 3);

    matrix_a.rows = 2;
    matrix_a.cols = 2;
    matrix_b.rows = 3;
    matrix_b.cols = 3;

    if (!matrix_a.matrix || !matrix_b.matrix)
    {
        if (matrix_a.matrix) free(matrix_a.matrix);
        if (matrix_b.matrix) free(matrix_b.matrix);
        ck_abort_msg("Memory allocation failed for matrices.");
    }

    int res = multiply(&matrix_a, &matrix_b, &result);

    ck_assert_int_eq(res, ERR_MUL_SIZES);

    free(matrix_a.matrix);
    free(matrix_b.matrix);
    if (result.matrix) 
        free(result.matrix);
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