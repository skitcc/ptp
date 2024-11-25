#include "check_min_max.h"

START_TEST(test_min_max_non_empty) 
{
    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_nonnull(arr);

    assoc_array_insert(arr, "key3", 30);
    assoc_array_insert(arr, "key1", 10);
    assoc_array_insert(arr, "key2", 20);

    int *num = NULL;

    assoc_array_error_t res = assoc_array_min(arr, &num);
    ck_assert_int_eq(res, ASSOC_ARRAY_OK);
    ck_assert_ptr_nonnull(num);
    ck_assert_int_eq(*num, 10);

    res = assoc_array_max(arr, &num);
    ck_assert_int_eq(res, ASSOC_ARRAY_OK);
    ck_assert_ptr_nonnull(num);
    ck_assert_int_eq(*num, 30);

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_min_max_empty) 
{
    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_nonnull(arr);

    int *num = NULL;

    assoc_array_error_t res = assoc_array_min(arr, &num);
    ck_assert_int_eq(res, ASSOC_ARRAY_NOT_FOUND);
    ck_assert_ptr_null(num);

    res = assoc_array_max(arr, &num);
    ck_assert_int_eq(res, ASSOC_ARRAY_NOT_FOUND);
    ck_assert_ptr_null(num);

    assoc_array_destroy(&arr);
}
END_TEST

Suite *min_max_suite(void) 
{
    Suite *s = suite_create("Min_Max");
    TCase *tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_min_max_non_empty);
    tcase_add_test(tc_core, test_min_max_empty);
    suite_add_tcase(s, tc_core);

    return s;
}