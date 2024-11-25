#include "check_utils.h"

node_t *node_create(void *data) 
{
    node_t *node = malloc(sizeof(node_t));
    node->data = data;
    node->next = NULL;
    return node;
}

student_info *create_student(int age, int course, const char *name) 
{
    student_info *student = malloc(sizeof(student_info));
    student->age = age;
    student->course = course;

    student->name = malloc(strlen(name) + 1);
    strcpy(student->name, name);
    return student;
}

void student_free(student_info *student) 
{
    free(student->name);
    free(student);
}

void free_list_with_data(node_t *head, void (*free_data)(void *)) 
{
    while (head) {
        node_t *temp = head;
        head = head->next;
        if (free_data)
            free_data(temp->data);
        free(temp);
    }
}
