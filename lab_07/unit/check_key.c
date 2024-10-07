#include <check.h>
#include "operations.h"
#include <stdlib.h>

// Тест: Корректная фильтрация массива
START_TEST(test_key_valid_input)
{
    int src[] = {20, 10, 5, 2, 1};
    int *pb_dst = NULL;
    int *pe_dst = NULL;

    int result = key(src, src + 5, &pb_dst, &pe_dst);

    ck_assert_int_eq(result, EXIT_SUCCESS);
    ck_assert_int_eq(pe_dst - pb_dst, 4); 

    int expected[] = {20, 10, 5, 2};
    int *temp_pb = pb_dst;
    int i = 0;
    while (temp_pb < pe_dst)
    {
        ck_assert_int_eq(*temp_pb, expected[i++]);
        temp_pb++;
    }
    free(pb_dst);
}
END_TEST

// Тест: Нет элементов для фильтрации (вернуть ошибку ERR_EMPTY_FILE_AFTER_FILTER)
START_TEST(test_key_no_elements_to_filter)
{
    int src[] = {1, 2, 3, 4};  
    int *pb_dst = NULL;
    int *pe_dst = NULL;

    int result = key(src, src + 4, &pb_dst, &pe_dst);

    ck_assert_int_eq(result, ERR_EMPTY_FILE_AFTER_FILTER);
    ck_assert_ptr_null(pb_dst);
}
END_TEST

// Тест: Один элемент в массиве
START_TEST(test_key_one_element)
{
    int src[] = {5};
    int *dst = NULL;
    int *pe_dst = NULL;

    int result = key(src, src + 1, &dst, &pe_dst);

    ck_assert_int_eq(result, ERR_EMPTY_FILE_AFTER_FILTER);
    ck_assert_ptr_null(dst);
}
END_TEST

// Тест: Проверка, что указатель pb_dst не превышает pe_dst
START_TEST(test_key_pointer_check)
{
    int src[] = {20, 10, 5, 2, 1};
    int *pb_dst = NULL;
    int *pe_dst = NULL;

    int result = key(src, src + 5, &pb_dst, &pe_dst);

    ck_assert_int_eq(result, EXIT_SUCCESS);
    ck_assert(pb_dst <= pe_dst); // Проверка, что pb_dst не превышает pe_dst
    free(pb_dst);
}
END_TEST

// Тест: Проверка, что указатели pb_dst и pe_dst не равны NULL
START_TEST(test_key_pointers_not_null)
{
    int src[] = {20, 10, 5, 2, 1};
    int *pb_dst = NULL;
    int *pe_dst = NULL;

    int result = key(src, src + 5, &pb_dst, &pe_dst);

    ck_assert_int_eq(result, EXIT_SUCCESS);
    ck_assert_ptr_nonnull(pb_dst); // Проверка, что pb_dst не NULL
    ck_assert_ptr_nonnull(pe_dst); // Проверка, что pe_dst не NULL
    free(pb_dst);
}
END_TEST

// Тест: Проверка, что размер элементов и длина не равны 0
START_TEST(test_key_size_and_length)
{
    int src[] = {20, 10, 5, 2, 1};
    int *pb_dst = NULL;
    int *pe_dst = NULL;

    int result = key(src, src + 5, &pb_dst, &pe_dst);

    ck_assert_int_eq(result, EXIT_SUCCESS);
    ck_assert_int_gt(pe_dst - pb_dst, 0); // Проверка, что длина не 0
    free(pb_dst);
}
END_TEST

// Тест: Проверка, что конец больше начала
START_TEST(test_key_end_greater_than_start)
{
    int src[] = {20, 10, 5, 2, 1};
    int *pb_dst = NULL;
    int *pe_dst = NULL;

    int result = key(src, src + 5, &pb_dst, &pe_dst);

    ck_assert_int_eq(result, EXIT_SUCCESS);
    ck_assert(pb_dst < pe_dst);
    free(pb_dst);
}
END_TEST

// Тест: Фильтрация нулевого массива
START_TEST(test_filter_zero_mass)
{
    int *src = NULL;
    int *pb_dst = NULL;
    int *pe_dst = NULL;

    int result = key(src, src, &pb_dst, &pe_dst);

    ck_assert_int_eq(result, ERR_POINTERS);
    free(pb_dst);
}
END_TEST

Suite *key_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    s = suite_create("key_suite");
    tc_pos = tcase_create("core");
    tcase_add_test(tc_pos, test_key_valid_input);
    tcase_add_test(tc_pos, test_key_no_elements_to_filter);
    tcase_add_test(tc_pos, test_key_one_element);
    tcase_add_test(tc_pos, test_key_pointer_check);  
    tcase_add_test(tc_pos, test_key_pointers_not_null); 
    tcase_add_test(tc_pos, test_key_size_and_length); 
    tcase_add_test(tc_pos, test_key_end_greater_than_start); 
    tcase_add_test(tc_pos, test_filter_zero_mass);
    suite_add_tcase(s, tc_pos);

    return s;
}
