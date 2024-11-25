#include "check_get.h"

// Тест на успешное получение значений
START_TEST(test_get_existing) 
{
    assoc_array_t array = associative_array_create();

    associative_array_add(array, "key1", 42);
    associative_array_add(array, "key2", 100);

    ck_assert_int_eq(associative_array_get(array, "key1"), 42);
    ck_assert_int_eq(associative_array_get(array, "key2"), 100);

    associative_array_destroy(array);
}
END_TEST

// Тест на попытку получения значения по несуществующему ключу
START_TEST(test_get_nonexistent) 
{
    assoc_array_t array = associative_array_create();

    ck_assert_int_eq(associative_array_get(array, "key1"), -1);
    associative_array_destroy(array);
}
END_TEST

Suite* get_suite(void) 
{
    Suite* s;
    TCase* tc_core;

    s = suite_create("Get");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_get_existing);
    tcase_add_test(tc_core, test_get_nonexistent);

    suite_add_tcase(s, tc_core);
    return s;
}