#include "check_clear.h"

START_TEST(test_clear_non_empty) 
{
    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_nonnull(arr);

    assoc_array_insert(arr, "key1", 42);
    assoc_array_insert(arr, "key2", 84);

    assoc_array_error_t res = assoc_array_clear(arr);
    ck_assert_int_eq(res, ASSOC_ARRAY_OK);

    int *num = NULL;
    res = assoc_array_find(arr, "key1", &num);
    ck_assert_int_eq(res, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_clear_empty) 
{
    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_nonnull(arr);

    assoc_array_error_t res = assoc_array_clear(arr);
    ck_assert_int_eq(res, ASSOC_ARRAY_OK);

    assoc_array_destroy(&arr);
}
END_TEST

Suite *clear_suite(void) 
{
    Suite *s = suite_create("Clear");
    TCase *tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_clear_non_empty);
    tcase_add_test(tc_core, test_clear_empty);
    suite_add_tcase(s, tc_core);

    return s;
}