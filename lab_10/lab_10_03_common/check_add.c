#include "check_add.h"


// Тест на успешное добавление элементов
START_TEST(test_add_elements) 
{
    assoc_array_t array = associative_array_create();

    ck_assert(associative_array_add(array, "key1", 42));
    ck_assert(associative_array_add(array, "key2", 100));

    associative_array_destroy(array);
}
END_TEST

// Тест на добавление элементов с одинаковыми ключами
START_TEST(test_add_duplicate_keys) 
{
    assoc_array_t array = associative_array_create();

    ck_assert(associative_array_add(array, "key1", 42));
    ck_assert(associative_array_add(array, "key1", 100));

    ck_assert_int_eq(associative_array_get(array, "key1"), 100);
    associative_array_destroy(array);
}
END_TEST


Suite* add_suite(void) 
{
    Suite* s;
    TCase* tc_core;

    s = suite_create("Add");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_add_elements);
    tcase_add_test(tc_core, test_add_duplicate_keys);

    suite_add_tcase(s, tc_core);
    return s;
}