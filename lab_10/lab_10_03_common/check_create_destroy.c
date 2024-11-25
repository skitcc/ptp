#include "check_create_destroy.h"



// Тест на создание массива
START_TEST(test_create) 
{
    assoc_array_t array = associative_array_create();
    ck_assert_ptr_nonnull(array);
    associative_array_destroy(array);
}
END_TEST

// Тест на удаление пустого массива
START_TEST(test_destroy_empty) 
{
    assoc_array_t array = associative_array_create();
    associative_array_destroy(array);
}
END_TEST

Suite* create_destroy_suite(void) 
{
    Suite* s;
    TCase* tc_core;

    s = suite_create("CreateDestroy");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_create);
    tcase_add_test(tc_core, test_destroy_empty);

    suite_add_tcase(s, tc_core);
    return s;
}
