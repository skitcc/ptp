#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "associative_array.h"




typedef struct node
{
    key key;
    value value;
    struct node *next;
} node_t;


struct assoc_array
{
    node_t *head;
};


assoc_array_t associative_array_create() 
{
    assoc_array_t array = malloc(sizeof(assoc_array_t));
    if (!array) 
        return NULL;
    array->head = NULL;
    return array;
}

void associative_array_destroy(assoc_array_t array) 
{
    if (!array) 
        return;
    node_t *current = array->head;
    while (current) 
    {
        node_t *temp = current;
        current = current->next;
        free(temp->key); 
        free(temp);
    }
    free(array);
}

bool associative_array_add(assoc_array_t array, key k, value v) 
{
    if (!array || !k) 
        return false;

    node_t *current = array->head;
    while (current) 
    {
        if (strcmp(current->key, k) == 0) 
        {
            current->value = v;
            return true;
        }
        current = current->next;
    }

    node_t *new_node = malloc(sizeof(node_t));
    if (!new_node) 
        return false;
    new_node->key = malloc(strlen(k));
    if (!new_node->key) 
    {
        free(new_node);
        return false;
    }
    strcpy(new_node->key, k);
    new_node->value = v;
    new_node->next = array->head;
    array->head = new_node;
    return true;
}

value associative_array_get(assoc_array_t array, key k) 
{
    if (!array || !k) return -1;

    node_t *current = array->head;
    while (current) {
        if (strcmp(current->key, k) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return -1;
}

bool associative_array_remove(assoc_array_t array, key k) 
{
    if (!array || !k) return false;

    node_t *current = array->head;
    node_t *prev = NULL;

    while (current) {
        if (strcmp(current->key, k) == 0) {
            if (prev) 
                prev->next = current->next;
            else 
                array->head = current->next;
            
            free(current->key);
            free(current);
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}
