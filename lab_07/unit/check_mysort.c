#include <check.h>
#include "my_sort.h"


int cmp_arr(const int *arr1, size_t size1, const int *arr2, size_t size2)
{
    if (size1 != size2)
        return 1;

    for (size_t i = 0; i < size1; i++)
    {
        if (arr1[i] != arr2[i])
            return 2;
    }
    return 0;
}


int compare_doubles(const void *a, const void *b)
{
    double double_a = *(const double *)a;
    double double_b = *(const double *)b;
    return (double_a > double_b) - (double_a < double_b);
}


START_TEST(sorted_arrs)
{
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int b[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    mysort(a, 10, sizeof(int), compare_ints);
    int rc = cmp_arr(a, 10, b, 10);
    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(rev_sorted)
{
    int a[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int b[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    mysort(a, 10, sizeof(int), compare_ints);
    int rc = cmp_arr(a, 10, b, 10);
    ck_assert_int_eq(rc, 0);
}
END_TEST


START_TEST(equal_arrs)
{
    int a[] = {5, 5, 5, 5, 5};
    int b[] = {5, 5, 5, 5, 5};

    mysort(a, 5, sizeof(int), compare_ints);
    int rc = cmp_arr(a, 5, b, 5);
    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(random_pos)
{
    int a[] = {5, 2, 3, 4, 1};
    int b[] = {1, 2, 3, 4, 5};
    mysort(a, 5, sizeof(int), compare_ints);
    int rc = cmp_arr(a, 5, b, 5);
    ck_assert_int_eq(rc, 0);
}

START_TEST(arr_len_1)
{
    int a[] = {5};
    int b[] = {5};

    mysort(a, 1, sizeof(int), compare_ints);
    int rc = cmp_arr(a, 1, b, 1);
    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(empty_array)
{
    int *a = NULL; 
    int *b = NULL;

    mysort(a, 0, sizeof(int), compare_ints);
    ck_assert_ptr_eq(a, b);
}
END_TEST




Suite *my_sort_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    s = suite_create("my_sort");
    tc_pos = tcase_create("core");
    tcase_add_test(tc_pos, sorted_arrs);
    tcase_add_test(tc_pos, rev_sorted);
    tcase_add_test(tc_pos, equal_arrs);
    tcase_add_test(tc_pos, random_pos);
    tcase_add_test(tc_pos, arr_len_1);
    tcase_add_test(tc_pos, empty_array);
    suite_add_tcase(s, tc_pos);

    return s;

}



