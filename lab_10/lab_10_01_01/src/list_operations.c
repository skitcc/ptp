#include "list_operations.h"

void *pop_front(node_t **head)
{
    if (head == NULL)
        return NULL;

    if (*head == NULL)
        return NULL;

    void *data = (*head)->data;
    
    node_t *del_head = *head;
    *head = (*head)->next;

    free(del_head);
    return data;
}

void insert(node_t **head, node_t *elem, node_t *before)
{
    if (head == NULL || *head == NULL || elem == NULL)
    {
        free_list(elem);
        free_list(*head);
        return;
    }
    if (before == NULL)
    {
        free_list(elem);
        free_list(*head);  
        return;
    }
    if (before == *head)
    {
        elem->next = *head;
        *head = elem;
        return;
    }
    node_t *current = *head;
    while (current != NULL && current->next != before)
    {
        current = current->next;
    }

    if (current == NULL)
        return;

    elem->next = before;
    current->next = elem;
}


node_t *reverse(node_t *head) 
{
    if (head == NULL || head->next == NULL) 
    {
        return head;
    }
    node_t *new_head = reverse(head->next);

    head->next->next = head;
    head->next = NULL;

    return new_head;
}


int get_len_list(node_t *head)
{
    node_t *current = head;
    int len = 0; 
    while (current != NULL)
    {
        current = current->next;
        len++;
    }
    return len;
}

void front_back_split(node_t *head, node_t **back)
{
    if (head == NULL)
        return;
    node_t *current = head;
    int len_list = get_len_list(head);
    int index = 0;
    if (len_list % 2)
        index = (len_list / 2) + 1;
    else
        index = (len_list / 2);

    int cur_index = 0;    
    while (cur_index != index)
    {
        current = current->next;
        cur_index++;
    }
    *back = current;
    cur_index = 0;
    current = head;
    while (cur_index < index - 1)
    {
        current = current->next;
        cur_index++;
    }

    current->next = NULL;
}

int compare_students_by_age(const void *a, const void *b) 
{
    const student_info *student_a = (const student_info *)a;
    const student_info *student_b = (const student_info *)b;
    return student_a->age - student_b->age;
}


node_t *sorted_merge(node_t **head_a, node_t **head_b, int (*comparator)(const void *, const void *)) 
{

    if (!head_a || !head_b || !comparator)
        return NULL;

    if (*head_a == NULL)
    {
        node_t *result = *head_b;
        *head_b = NULL;
        return result;
    }
    if (*head_b == NULL)
    {
        node_t *result = *head_a;
        *head_a = NULL;
        return result;
    }
    if (!comparator)
        return NULL;

    node_t *result = NULL;

    if (comparator((*head_a)->data, (*head_b)->data) <= 0) 
    {
        result = *head_a;
        *head_a = (*head_a)->next;
        result->next = sorted_merge(head_a, head_b, comparator);
    } 
    else
    {
        result = *head_b;
        *head_b = (*head_b)->next;
        result->next = sorted_merge(head_a, head_b, comparator);
    }

    *head_a = NULL;
    *head_b = NULL;
    return result;
}


void merge_sort(node_t **head, int (*comparator)(const void *, const void *)) 
{
    if (!head || !*head || !(*head)->next)
        return;

    node_t *back = NULL;

    front_back_split(*head, &back);

    merge_sort(head, comparator);
    merge_sort(&back, comparator);

    *head = sorted_merge(head, &back, comparator);
}