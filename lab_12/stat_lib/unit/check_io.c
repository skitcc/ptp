#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read.h"  // Функции для чтения
#include "print.h" // Функции для записи

// Тест: корректное чтение количества элементов из файла
START_TEST(test_read_quantity_valid_input)
{
    FILE *f = fopen("test_input.txt", "w");
    fprintf(f, "10 20 30 40 50\n");
    fclose(f);

    size_t n = 0;
    short result = read_quantity("test_input.txt", &n);
    ck_assert_int_eq(result, EXIT_SUCCESS);
    ck_assert_int_eq(n, 5); 

    remove("test_input.txt");
}
END_TEST

// Тест: файл не существует
START_TEST(test_read_quantity_file_not_found)
{
    size_t n = 0;
    short result = read_quantity("non_existent_file.txt", &n);
    ck_assert_int_eq(result, ERR_OPEN_FILE);
    ck_assert_int_eq(n, 0);
}
END_TEST

// Тест: пустой файл
START_TEST(test_read_quantity_empty_file)
{
    FILE *f = fopen("empty_file.txt", "w");
    fclose(f);

    size_t n = 0;
    short result = read_quantity("empty_file.txt", &n);
    ck_assert_int_eq(result, ERR_EMPTY_FILE);
    ck_assert_int_eq(n, 0);

    remove("empty_file.txt");
}
END_TEST

// Тест: корректное заполнение массива из файла
START_TEST(test_fill_array_valid_input)
{
    FILE *f = fopen("test_input.txt", "w");
    fprintf(f, "10 20 30 40 50\n");
    fclose(f);

    int arr[5] = {0};
    fill_array("test_input.txt", arr, arr + 4);

    int expected[] = {10, 20, 30, 40, 50};
    for (int i = 0; i < 5; i++)
        ck_assert_int_eq(arr[i], expected[i]);

    remove("test_input.txt");
}
END_TEST

// Тест: корректная запись массива в файл
START_TEST(test_print_to_file_valid_output)
{
    int arr[] = {10, 20, 30, 40, 50};
    
    int result = print_to_file(arr, arr + 5, "test_output.txt");
    ck_assert_int_eq(result, EXIT_SUCCESS);

    FILE *f = fopen("test_output.txt", "r");
    char buffer[256];
    fgets(buffer, sizeof(buffer), f);
    fclose(f);

    ck_assert_str_eq(buffer, "10 20 30 40 50 \n");
    remove("test_output.txt");
}
END_TEST

// Тест: ошибка открытия файла для записи
START_TEST(test_print_to_file_open_error)
{
    int arr[] = {10, 20, 30, 40, 50};
    int result = print_to_file(arr, arr + 5, "/invalid_path/output.txt");
    ck_assert_int_eq(result, ERR_OPEN_FILE);
}
END_TEST

Suite* io_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("IO");

    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_read_quantity_valid_input);
    tcase_add_test(tc_core, test_read_quantity_file_not_found);
    tcase_add_test(tc_core, test_read_quantity_empty_file);

    tcase_add_test(tc_core, test_fill_array_valid_input);

    tcase_add_test(tc_core, test_print_to_file_valid_output);
    tcase_add_test(tc_core, test_print_to_file_open_error);

    suite_add_tcase(s, tc_core);

    return s;
}
