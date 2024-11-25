#include "check_insert.h"

START_TEST(test_insert_valid) 
{
    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_nonnull(arr);

    assoc_array_error_t res = assoc_array_insert(arr, "key1", 42);
    ck_assert_int_eq(res, ASSOC_ARRAY_OK);

    res = assoc_array_insert(arr, "key2", 84);
    ck_assert_int_eq(res, ASSOC_ARRAY_OK);

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_insert_duplicate) 
{
    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_nonnull(arr);

    assoc_array_insert(arr, "key1", 42);
    assoc_array_error_t res = assoc_array_insert(arr, "key1", 99);
    ck_assert_int_eq(res, ASSOC_ARRAY_KEY_EXISTS);

    assoc_array_destroy(&arr);
}
END_TEST

Suite *insert_suite(void) 
{
    Suite *s = suite_create("Insert");
    TCase *tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_insert_valid);
    tcase_add_test(tc_core, test_insert_duplicate);
    suite_add_tcase(s, tc_core);

    return s;
}