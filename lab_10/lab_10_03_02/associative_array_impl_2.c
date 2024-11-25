#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "associative_array.h"

typedef struct assoc_array_node 
{
    char *key;
    int value;
    struct assoc_array_node *left;
    struct assoc_array_node *right;
} assoc_array_node_t;

struct assoc_array_type 
{
    assoc_array_node_t *root;
};



assoc_array_t assoc_array_create(void) 
{
    assoc_array_t arr = malloc(sizeof(struct assoc_array_type));
    if (!arr) 
        return NULL;
    arr->root = NULL;
    return arr;
}

static void free_tree(assoc_array_node_t *node) 
{
    if (node) 
    {
        free_tree(node->left);
        free_tree(node->right);
        free(node->key);
        free(node);
    }
}

void assoc_array_destroy(assoc_array_t *arr) 
{
    if (!arr || !*arr) 
        return;
    free_tree((*arr)->root);
    free(*arr);
    *arr = NULL;
}



static assoc_array_node_t*insert_node(assoc_array_node_t *node, const char *key, int num, assoc_array_error_t *err) 
{
    if (!node) 
    {
        assoc_array_node_t *new_node = malloc(sizeof(assoc_array_node_t));
        if (!new_node) 
        {
            *err = ASSOC_ARRAY_MEM;
            return NULL;
        }
        new_node->key = malloc(strlen(key) + 1);
        if (!new_node->key) 
        {
            free(new_node);
            *err = ASSOC_ARRAY_MEM;
            return NULL;
        }
        strcpy(new_node->key, key);
        new_node->value = num;
        new_node->left = new_node->right = NULL;
        *err = ASSOC_ARRAY_OK;
        return new_node;
    }

    int cmp = strcmp(key, node->key);
    if (cmp < 0) 
        node->left = insert_node(node->left, key, num, err);
    else if (cmp > 0) 
        node->right = insert_node(node->right, key, num, err);
    else 
        *err = ASSOC_ARRAY_KEY_EXISTS;
    
    return node;
}


assoc_array_error_t assoc_array_insert(assoc_array_t arr, const char *key, int num) 
{
    if (!arr || !key || strlen(key) == 0) 
        return ASSOC_ARRAY_INVALID_PARAM;

    assoc_array_error_t err = ASSOC_ARRAY_OK;
    arr->root = insert_node(arr->root, key, num, &err);
    return err;
}


static assoc_array_node_t*find_node(assoc_array_node_t *node, const char *key) 
{
    if (!node) 
        return NULL;

    int cmp = strcmp(key, node->key);
    if (cmp < 0) 
        return find_node(node->left, key);
    if (cmp > 0) 
        return find_node(node->right, key);
    return node;
}


assoc_array_error_t assoc_array_find(const assoc_array_t arr, const char *key, int **num) 
{
    if (!arr || !key || strlen(key) == 0 || !num) 
        return ASSOC_ARRAY_INVALID_PARAM;

    assoc_array_node_t *node = find_node(arr->root, key);
    if (!node) 
        return ASSOC_ARRAY_NOT_FOUND;

    *num = &node->value;
    return ASSOC_ARRAY_OK;
}

static assoc_array_node_t*delete_node(assoc_array_node_t *node, const char *key, assoc_array_error_t *err) 
{
    if (!node) 
    {
        *err = ASSOC_ARRAY_NOT_FOUND;
        return NULL;
    }

    int cmp = strcmp(key, node->key);
    if (cmp < 0) 
    {
        node->left = delete_node(node->left, key, err);
    } 
    else if (cmp > 0) 
    {
        node->right = delete_node(node->right, key, err);
    } 
    else 
    {
        assoc_array_node_t *temp;
        if (!node->left) 
        {
            temp = node->right;
            free(node->key);
            free(node);
            *err = ASSOC_ARRAY_OK;
            return temp;
        } 
        else if (!node->right) 
        {
            temp = node->left;
            free(node->key);
            free(node);
            *err = ASSOC_ARRAY_OK;
            return temp;
        }

        assoc_array_node_t *min_right = node->right;
        while (min_right->left) 
            min_right = min_right->left;

        free(node->key);
        node->key = malloc(strlen(min_right->key) + 1);
        if (!node->key)
            return NULL;
        strcpy(node->key, min_right->key);
        node->value = min_right->value;
        node->right = delete_node(node->right, min_right->key, err);
    }

    return node;
}


assoc_array_error_t assoc_array_remove(assoc_array_t arr, const char *key) 
{
    if (!arr || !key || strlen(key) == 0) 
        return ASSOC_ARRAY_INVALID_PARAM;

    assoc_array_error_t err = ASSOC_ARRAY_OK;
    arr->root = delete_node(arr->root, key, &err);
    return err;
}

assoc_array_error_t assoc_array_clear(assoc_array_t arr) 
{
    if (!arr) 
        return ASSOC_ARRAY_INVALID_PARAM;

    free_tree(arr->root);
    arr->root = NULL;
    return ASSOC_ARRAY_OK;
}


static void traverse_tree(assoc_array_node_t *node, void (*action)(const char *key, int *num, void *param), void *param) 
{
    if (!node) 
        return;
    traverse_tree(node->left, action, param);
    action(node->key, &node->value, param);
    traverse_tree(node->right, action, param);
}

assoc_array_error_t assoc_array_each(const assoc_array_t arr, void (*action)(const char *key, int *num, void *param), void *param) 
{
    if (!arr || !action) 
        return ASSOC_ARRAY_INVALID_PARAM;

    traverse_tree(arr->root, action, param);
    return ASSOC_ARRAY_OK;
}


assoc_array_error_t assoc_array_min(const assoc_array_t arr, int **num) 
{
    if (!arr || !num) 
        return ASSOC_ARRAY_INVALID_PARAM;

    assoc_array_node_t *current = arr->root;
    if (!current) 
        return ASSOC_ARRAY_NOT_FOUND;

    while (current->left) 
        current = current->left;

    *num = &current->value;
    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_max(const assoc_array_t arr, int **num) 
{
    if (!arr || !num) 
        return ASSOC_ARRAY_INVALID_PARAM;

    assoc_array_node_t *current = arr->root;
    if (!current) 
        return ASSOC_ARRAY_NOT_FOUND;

    while (current->right) 
        current = current->right;

    *num = &current->value;
    return ASSOC_ARRAY_OK;
}






