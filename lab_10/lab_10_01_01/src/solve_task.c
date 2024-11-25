#include "solve_task.h"



node_t *create_node(int age, int course, char *name)
{
    node_t *new_node = malloc(sizeof(node_t));

    if (!new_node)
        return NULL;
    student_info *data = malloc(sizeof(student_info));
    if (!data)
    {
        free(new_node);
        return NULL;
    }
    data->age = age;
    data->course = course;
    data->name = malloc(sizeof(strlen(name)));
    strcpy(data->name, name);

    new_node->data = data;
    new_node->next = NULL;

    return new_node;
}

void insert_student(node_t **head, int age, int course, char *name)
{
    node_t *new_node = create_node(age, course, name);
    if (new_node == NULL)
        return;

    if (*head == NULL)
    {
        *head = new_node;
        return;
    }

    student_info *head_data = (student_info *)(*head)->data;

    if (head_data->course > course)
    {
        new_node->next = *head;
        *head = new_node;
        return;
    }

    if (head_data->course == course)
    {
        student_info *removed_data = pop_front(head);
        free(removed_data->name);
        free(removed_data);

        new_node->next = *head;
        *head = new_node;
        return;
    }

    node_t *current = *head;
    while (current->next != NULL && ((student_info *)current->next->data)->course < course)
    {
        current = current->next;
    }

    if (current->next != NULL && 
        ((student_info *)current->next->data)->course == course)
    {
        node_t *to_replace = current->next;
        student_info *old_data = to_replace->data;

        free(old_data->name);
        old_data->age = age;
        old_data->course = course;
        old_data->name = malloc(strlen(name) + 1);
        strcpy(old_data->name, name);
        node_t *temp = new_node;
        free(((student_info *)temp->data)->name);
        free(temp->data);               
        free(temp);

        return;
    }

    insert(head, new_node, current->next);
}
