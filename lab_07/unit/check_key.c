#include <check.h>
#include "operations.h"


#include <check.h>
#include <stdlib.h>
#include "operations.h" 

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



Suite *key_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    s = suite_create("key_suite");
    tc_pos = tcase_create("core");
    tcase_add_test(tc_pos, test_key_valid_input);
    tcase_add_test(tc_pos, test_key_no_elements_to_filter);
    tcase_add_test(tc_pos, test_key_one_element);
    suite_add_tcase(s, tc_pos);

    return s;

}

