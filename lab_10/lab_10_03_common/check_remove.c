#include "check_remove.h"


// Тест на успешное удаление существующего элемента
START_TEST(test_remove_existing) 
{
    assoc_array_t array = associative_array_create();

    associative_array_add(array, "key1", 42);
    associative_array_add(array, "key2", 100);

    ck_assert(associative_array_remove(array, "key1"));
    ck_assert_int_eq(associative_array_get(array, "key1"), -1);

    associative_array_destroy(array);
}
END_TEST

// Тест на удаление несуществующего элемента
START_TEST(test_remove_nonexistent) 
{
    assoc_array_t array = associative_array_create();

    ck_assert(!associative_array_remove(array, "key1"));

    associative_array_destroy(array);
}
END_TEST

Suite* remove_suite(void) 
{
    Suite* s;
    TCase* tc_core;

    s = suite_create("Remove");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_remove_existing);
    tcase_add_test(tc_core, test_remove_nonexistent);

    suite_add_tcase(s, tc_core);
    return s;
}

