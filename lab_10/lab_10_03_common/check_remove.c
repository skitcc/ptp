#include "check_remove.h"


START_TEST(test_remove_existing) 
{
    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_nonnull(arr);

    assoc_array_insert(arr, "key1", 42);
    assoc_array_error_t res = assoc_array_remove(arr, "key1");
    ck_assert_int_eq(res, ASSOC_ARRAY_OK);

    int *num = NULL;
    res = assoc_array_find(arr, "key1", &num);
    ck_assert_int_eq(res, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_remove_non_existing) {
    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_nonnull(arr);

    assoc_array_error_t res = assoc_array_remove(arr, "key2");
    ck_assert_int_eq(res, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
}
END_TEST

Suite *remove_suite(void) {
    Suite *s = suite_create("Remove");
    TCase *tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_remove_existing);
    tcase_add_test(tc_core, test_remove_non_existing);
    suite_add_tcase(s, tc_core);

    return s;
}

