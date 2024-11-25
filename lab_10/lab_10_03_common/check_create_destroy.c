#include "check_create_destroy.h"

START_TEST(test_create_destroy_basic) 
{
    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_nonnull(arr);
    assoc_array_destroy(&arr);
    ck_assert_ptr_null(arr);
}
END_TEST

START_TEST(test_destroy_null) 
{
    assoc_array_t arr = NULL;
    assoc_array_destroy(&arr);
    ck_assert_ptr_null(arr);
}
END_TEST

Suite *create_destroy_suite(void) 
{
    Suite *s = suite_create("Create_Destroy");
    TCase *tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_create_destroy_basic);
    tcase_add_test(tc_core, test_destroy_null);
    suite_add_tcase(s, tc_core);

    return s;
}
