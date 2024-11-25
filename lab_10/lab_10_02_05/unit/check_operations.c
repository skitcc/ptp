#include "check_operations.h"

#include <stdlib.h>
#include <check.h>
#include "operations.h"

static void list_to_string(const list_t *head, char *result, size_t max_len) 
{
    size_t index = 0;
    while (head != NULL && index < max_len - 1) {
        for (int i = 0; i < PART_SIZE && head->part[i] != '\0'; i++) 
        {
            result[index++] = head->part[i];
        }
        head = head->next;
    }
    result[index] = '\0';
}

START_TEST(test_concatenate_basic) 
{
    char *str1 = "abc";
    char *str2 = "def";
    list_t *head = NULL;
    list_t *head1 = NULL;
    list_t *head2 = NULL;
    read_str_to_list(str1, &head1);
    read_str_to_list(str2, &head2);

    head = concatenate(head1, head2);

    char result[16];
    list_to_string(head, result, sizeof(result));
    ck_assert_str_eq(result, "abcdef");

    free_list(head);
}
END_TEST

START_TEST(test_concatenate_empty) 
{
    char *str1 = "";
    char *str2 = "abc";
    list_t *head = NULL;
    list_t *head1 = NULL;
    list_t *head2 = NULL;
    read_str_to_list(str1, &head1);
    read_str_to_list(str2, &head2);

    head = concatenate(head1, head2);

    char result[16];
    list_to_string(head, result, sizeof(result));
    ck_assert_str_eq(result, "abc");

    free_list(head);
}
END_TEST

START_TEST(test_collapse_spaces_basic) 
{
    char *str = "a  b c";
    list_t *head = NULL;
    read_str_to_list(str, &head);

    int ret = collapse_spaces(head);
    ck_assert_int_eq(ret, 0);

    char result[16];
    list_to_string(head, result, sizeof(result));
    ck_assert_str_eq(result, "a b c");

    free_list(head);
}
END_TEST

START_TEST(test_collapse_spaces_no_spaces) 
{
    char *str = "abc";
    list_t *head = NULL;
    read_str_to_list(str, &head);

    int ret = collapse_spaces(head);
    ck_assert_int_eq(ret, 0);

    char result[16];
    list_to_string(head, result, sizeof(result));
    ck_assert_str_eq(result, "abc");

    free_list(head);
}
END_TEST

START_TEST(test_collapse_spaces_only_spaces) 
{
    char *str = "      ";
    list_t *head = NULL;
    read_str_to_list(str, &head);

    int ret = collapse_spaces(head);
    ck_assert_int_eq(ret, 0);

    free_list(head);
}
END_TEST

START_TEST(test_find_substring_basic) 
{
    char *str1 = "abcd";
    char *str2 = "cd";
    list_t *head1 = NULL;
    list_t *head2 = NULL;
    read_str_to_list(str1, &head1);
    read_str_to_list(str2, &head2);

    int index = find_substring(head1, head2);
    ck_assert_int_eq(index, 2);

    free_list(head1);
    free_list(head2);
}
END_TEST

START_TEST(test_find_substring_not_found) 
{
    char *str1 = "abcd";
    char *str2 = "fg";
    list_t *head1 = NULL;
    list_t *head2 = NULL;
    read_str_to_list(str1, &head1);
    read_str_to_list(str2, &head2);

    int index = find_substring(head1, head2);
    ck_assert_int_eq(index, -1);

    free_list(head1);
    free_list(head2);
}
END_TEST

START_TEST(test_find_substring_overlap_nodes) 
{
    char *str1 = "abcbcd";
    char *str2 = "bcd";
    list_t *head1 = NULL;
    list_t *head2 = NULL;
    read_str_to_list(str1, &head1);
    read_str_to_list(str2, &head2);

    int index = find_substring(head1, head2);
    ck_assert_int_eq(index, 3);

    free_list(head1);
    free_list(head2);
}
END_TEST

START_TEST(test_find_substring_partial_match_reset) 
{
    char *str1 = "abcabcabc";
    char *str2 = "cab";
    list_t *head1 = NULL;
    list_t *head2 = NULL;
    read_str_to_list(str1, &head1);
    read_str_to_list(str2, &head2);

    int index = find_substring(head1, head2);
    ck_assert_int_eq(index, 2);

    free_list(head1);
    free_list(head2);
}
END_TEST

Suite *operations_suite(void) 
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Operations");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_concatenate_basic);
    tcase_add_test(tc_core, test_concatenate_empty);

    tcase_add_test(tc_core, test_collapse_spaces_basic);
    tcase_add_test(tc_core, test_collapse_spaces_no_spaces);
    tcase_add_test(tc_core, test_collapse_spaces_only_spaces);

    tcase_add_test(tc_core, test_find_substring_basic);
    tcase_add_test(tc_core, test_find_substring_not_found);
    tcase_add_test(tc_core, test_find_substring_overlap_nodes);
    tcase_add_test(tc_core, test_find_substring_partial_match_reset);

    suite_add_tcase(s, tc_core);

    return s;
}


