#include <check.h>
#include "check_args.h"

// Тест на случай, когда передано слишком мало аргументов
START_TEST(test_check_too_few_args) {
    bool need_filter = false;
    const char *argv[] = {"../app.exe", "./unit/data/input_args_check.txt"};
    int argc = 2;
    int result = check(argc, argv, &need_filter);
    ck_assert_int_eq(result, ERR_WRONG_ARGC); 
}
END_TEST

// Тест на случай, когда передано слишком много аргументов
START_TEST(test_check_too_many_args) {
    bool need_filter = false;
    const char *argv[] = {"../app.exe", "./unit/data/input_args_check.txt", "./unit/data/output.txt", "f", "extra_arg"};
    int argc = 5;
    
    int result = check(argc, argv, &need_filter);
    ck_assert_int_eq(result, ERR_WRONG_ARGC);  

}
END_TEST

// Тест на случай, когда передан неверный фильтр
START_TEST(test_check_wrong_filter) {
    bool need_filter = false;
    const char *argv[] = {"../app.exe", "./unit/data/input_args_check.txt", "./unit/data/output.txt", "wrong_filter"};
    int argc = 4;
    int result = check(argc, argv, &need_filter);
    ck_assert_int_eq(result, ERR_WRONG_FILTER);

}
END_TEST

// Тест на успешную проверку с правильным количеством аргументов и фильтром
START_TEST(test_check_success_with_filter) {
    bool need_filter = false;
    const char *argv[] = {"../app.exe", "./unit/data/input_args_check.txt", "./unit/data/output.txt", "f"};
    int argc = 4;

    int result = check(argc, argv, &need_filter);
    ck_assert_int_eq(result, EXIT_SUCCESS);     
    ck_assert(need_filter);                     

}
END_TEST

// Тест на успешную проверку без фильтра
START_TEST(test_check_success_no_filter) {
    bool need_filter = false;
    const char *argv[] = {"../app.exe", "./unit/data/input_args_check.txt", "./unit/data/output.txt"};
    int argc = 3;

    int result = check(argc, argv, &need_filter);
    ck_assert_int_eq(result, EXIT_SUCCESS);     
    ck_assert(!need_filter);                   

}
END_TEST

Suite *check_args_suite(void) 
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("CheckArgs"); 
    tc_core = tcase_create("Core"); 

    tcase_add_test(tc_core, test_check_too_few_args);
    tcase_add_test(tc_core, test_check_too_many_args);
    tcase_add_test(tc_core, test_check_wrong_filter);
    tcase_add_test(tc_core, test_check_success_with_filter);
    tcase_add_test(tc_core, test_check_success_no_filter);
    
    suite_add_tcase(s, tc_core); 

    return s;
}

