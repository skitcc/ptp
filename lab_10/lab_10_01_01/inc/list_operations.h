#ifndef LIST_OPERATIONS_H
#define LIST_OPERATIONS_H



#include "structs.h"
#include "definitions.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

void *pop_front(node_t **head);
void insert(node_t **head, node_t *elem, node_t *before);
node_t *reverse(node_t *head);
void front_back_split(node_t *head, node_t **back);
int compare_students_by_age(const void *a, const void *b);
void merge_sort(node_t **head, int (*comparator)(const void *, const void *));
node_t *sorted_merge(node_t **head_a, node_t **head_b, int (*comparator)(const void *, const void *));

#endif