#include "check_operations.h"


START_TEST(test_pop_front) 
{
    student_info *s1 = create_student(20, 1, "Alice");
    student_info *s2 = create_student(22, 2, "Bob");
    node_t *n1 = node_create(s1);
    node_t *n2 = node_create(s2);
    n1->next = n2;

    node_t *head = n1;

    student_info *data = pop_front(&head);
    ck_assert_ptr_eq(data, s1);
    ck_assert_ptr_eq(head, n2);

    student_free(data);
    free_list_with_data(head, (void (*)(void *))student_free);
}
END_TEST



START_TEST(test_insert) 
{
    student_info *s1 = create_student(20, 1, "Alice");
    student_info *s2 = create_student(22, 2, "Bob");
    student_info *s3 = create_student(25, 3, "Charlie");
    node_t *n1 = node_create(s1);
    node_t *n2 = node_create(s2);
    n1->next = n2;

    node_t *head = n1;
    node_t *n3 = node_create(s3);

    insert(&head, n3, n2);
    ck_assert_ptr_eq(head, n1);
    ck_assert_ptr_eq(n1->next, n3);
    ck_assert_ptr_eq(n3->next, n2);

    free_list_with_data(head, (void (*)(void *))student_free);
}
END_TEST


START_TEST(test_reverse) 
{
    student_info *s1 = create_student(20, 1, "Alice");
    student_info *s2 = create_student(22, 2, "Bob");
    student_info *s3 = create_student(25, 3, "Charlie");
    node_t *n1 = node_create(s1);
    node_t *n2 = node_create(s2);
    node_t *n3 = node_create(s3);
    n1->next = n2;
    n2->next = n3;

    node_t *head = n1;

    head = reverse(head);
    ck_assert_ptr_eq(head, n3);
    ck_assert_ptr_eq(head->next, n2);
    ck_assert_ptr_eq(n2->next, n1);
    ck_assert_ptr_eq(n1->next, NULL);

    free_list_with_data(head, (void (*)(void *))student_free);
}
END_TEST


START_TEST(test_front_back_split) 
{
    student_info *s1 = create_student(20, 1, "Alice");
    student_info *s2 = create_student(22, 2, "Bob");
    student_info *s3 = create_student(25, 3, "Charlie");
    node_t *n1 = node_create(s1);
    node_t *n2 = node_create(s2);
    node_t *n3 = node_create(s3);
    n1->next = n2;
    n2->next = n3;

    node_t *head = n1;
    node_t *back = NULL;

    front_back_split(head, &back);

    ck_assert_ptr_eq(head, n1);
    ck_assert_ptr_eq(head->next, n2);
    ck_assert_ptr_eq(n2->next, NULL);
    ck_assert_ptr_eq(back, n3);
    ck_assert_ptr_eq(back->next, NULL);

    free_list_with_data(head, (void (*)(void *))student_free);
    free_list_with_data(back, (void (*)(void *))student_free);
}
END_TEST


START_TEST(test_merge_sort) 
{
    student_info *s1 = create_student(25, 3, "Charlie");
    student_info *s2 = create_student(22, 2, "Bob");
    student_info *s3 = create_student(20, 1, "Alice");

    node_t *n1 = node_create(s1);
    node_t *n2 = node_create(s2);
    node_t *n3 = node_create(s3);
    n1->next = n2;
    n2->next = n3;

    node_t *head = n1;

    merge_sort(&head, compare_students_by_age);

    ck_assert_ptr_eq(head->data, s3);
    ck_assert_ptr_eq(head->next->data, s2);
    ck_assert_ptr_eq(head->next->next->data, s1);
    ck_assert_ptr_eq(head->next->next->next, NULL);

    free_list_with_data(head, (void (*)(void *))student_free);
}
END_TEST


Suite *list_operations_suite(void) 
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("List Operations");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_pop_front);
    tcase_add_test(tc_core, test_insert);
    tcase_add_test(tc_core, test_reverse);
    tcase_add_test(tc_core, test_front_back_split);
    tcase_add_test(tc_core, test_merge_sort);

    suite_add_tcase(s, tc_core);
    return s;
}



