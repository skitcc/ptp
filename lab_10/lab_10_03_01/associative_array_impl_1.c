#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "associative_array.h"

typedef struct assoc_array_node 
{
    char *key;
    int value;
    struct assoc_array_node *next;
} assoc_array_node_t;

struct assoc_array_type 
{
    assoc_array_node_t *head;
};



assoc_array_t assoc_array_create(void) 
{
    assoc_array_t arr = malloc(sizeof(struct assoc_array_type));
    if (!arr) 
        return NULL;
    arr->head = NULL;
    return arr;
}

void assoc_array_destroy(assoc_array_t *arr) 
{
    if (!arr || !*arr) 
        return;

    assoc_array_node_t *current = (*arr)->head;
    while (current) 
    {
        assoc_array_node_t *next = current->next;
        free(current->key);
        free(current);
        current = next;
    }
    free(*arr);
    *arr = NULL;
}

assoc_array_error_t assoc_array_insert(assoc_array_t arr, const char *key, int num) 
{
    if (!arr || !key || strlen(key) == 0) 
        return ASSOC_ARRAY_INVALID_PARAM;

    assoc_array_node_t *current = arr->head;
    while (current) 
    {
        if (strcmp(current->key, key) == 0) 
        {
            return ASSOC_ARRAY_KEY_EXISTS;
        }
        current = current->next;
    }

    assoc_array_node_t *new_node = malloc(sizeof(assoc_array_node_t));
    if (!new_node) 
        return ASSOC_ARRAY_MEM;

    new_node->key = malloc(strlen(key) + 1);
    if (!new_node->key) 
    {
        free(new_node);
        return ASSOC_ARRAY_MEM;
    }

    strcpy(new_node->key, key);

    new_node->value = num;
    new_node->next = arr->head;
    arr->head = new_node;

    return ASSOC_ARRAY_OK;
}


assoc_array_error_t assoc_array_find(const assoc_array_t arr, const char *key, int **num) 
{
    if (!arr || !key || strlen(key) == 0 || !num) 
        return ASSOC_ARRAY_INVALID_PARAM;

    assoc_array_node_t *current = arr->head;
    while (current) 
    {
        if (strcmp(current->key, key) == 0) 
        {
            *num = &current->value;
            return ASSOC_ARRAY_OK;
        }
        current = current->next;
    }

    return ASSOC_ARRAY_NOT_FOUND;
}


assoc_array_error_t assoc_array_remove(assoc_array_t arr, const char *key) 
{
    if (!arr || !key || strlen(key) == 0) 
        return ASSOC_ARRAY_INVALID_PARAM;

    assoc_array_node_t **current = &arr->head;
    while (*current) 
    {
        if (strcmp((*current)->key, key) == 0) 
        {
            assoc_array_node_t *to_remove = *current;
            *current = to_remove->next;

            free(to_remove->key);
            free(to_remove);
            return ASSOC_ARRAY_OK;
        }
        current = &(*current)->next;
    }

    return ASSOC_ARRAY_NOT_FOUND;
}


assoc_array_error_t assoc_array_clear(assoc_array_t arr) 
{
    if (!arr) 
        return ASSOC_ARRAY_INVALID_PARAM;

    assoc_array_node_t *current = arr->head;
    while (current) 
    {
        assoc_array_node_t *next = current->next;
        free(current->key);
        free(current);
        current = next;
    }

    arr->head = NULL;
    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_each(const assoc_array_t arr, void (*action)(const char *key, int *num, void *param), void *param) 
{
    if (!arr || !action)
        return ASSOC_ARRAY_INVALID_PARAM;

    assoc_array_node_t *current = arr->head;
    while (current) 
    {
        action(current->key, &current->value, param);
        current = current->next;
    }

    return ASSOC_ARRAY_OK;
}


assoc_array_error_t assoc_array_min(const assoc_array_t arr, int **num) 
{
    if (!arr || !num) 
        return ASSOC_ARRAY_INVALID_PARAM;

    if (!arr->head) 
        return ASSOC_ARRAY_NOT_FOUND;

    assoc_array_node_t *current = arr->head;
    assoc_array_node_t *min_node = current;

    while (current) 
    {
        if (strcmp(current->key, min_node->key) < 0) 
            min_node = current;
        
        current = current->next;
    }

    *num = &min_node->value;
    return ASSOC_ARRAY_OK;
}


assoc_array_error_t assoc_array_max(const assoc_array_t arr, int **num) 
{
    if (!arr || !num) 
        return ASSOC_ARRAY_INVALID_PARAM;

    if (!arr->head) 
        return ASSOC_ARRAY_NOT_FOUND;

    assoc_array_node_t *current = arr->head;
    assoc_array_node_t *max_node = current;

    while (current) 
    {
        if (strcmp(current->key, max_node->key) > 0) 
            max_node = current;
        current = current->next;
    }

    *num = &max_node->value;
    return ASSOC_ARRAY_OK;
}




