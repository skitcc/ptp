#include "check_each.h"


void sum_values(const char *key, int *num, void *param) 
{
    int *sum = (int *)param;
    *sum += *num;
}

START_TEST(test_each_action) 
{
    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_nonnull(arr);

    assoc_array_insert(arr, "key1", 10);
    assoc_array_insert(arr, "key2", 20);
    assoc_array_insert(arr, "key3", 30);

    int sum = 0;
    assoc_array_error_t res = assoc_array_each(arr, sum_values, &sum);
    ck_assert_int_eq(res, ASSOC_ARRAY_OK);
    ck_assert_int_eq(sum, 60);

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_each_null_callback) 
{
    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_nonnull(arr);

    assoc_array_insert(arr, "key1", 10);

    assoc_array_error_t res = assoc_array_each(arr, NULL, NULL);
    ck_assert_int_eq(res, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&arr);
}
END_TEST


Suite *each_suite(void) 
{
    Suite *s = suite_create("Each");
    TCase *tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_each_action);
    tcase_add_test(tc_core, test_each_null_callback);
    suite_add_tcase(s, tc_core);

    return s;
}