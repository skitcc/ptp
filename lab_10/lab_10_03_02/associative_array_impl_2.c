#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "associative_array.h"

typedef struct tree_node 
{
    key key;
    value value;
    struct tree_node *left;
    struct tree_node *right;
} tree_node_t;

struct assoc_array 
{
    tree_node_t *root;
};

void destroy_tree(tree_node_t *node) 
{
    if (node) {
        destroy_tree(node->left);
        destroy_tree(node->right);
        free(node->key);
        free(node);
    }
}

assoc_array_t associative_array_create() 
{
    assoc_array_t array = malloc(sizeof(assoc_array_t));
    if (!array) 
        return NULL;
    array->root = NULL;
    return array;
}

void associative_array_destroy(assoc_array_t array) 
{
    if (!array) 
        return;
    destroy_tree(array->root);
    free(array);
}

tree_node_t* add_node(tree_node_t *node, key k, value v) 
{
    if (!node) 
    {
        tree_node_t *new_node = malloc(sizeof(tree_node_t));
        if (!new_node) 
            return NULL;
        new_node->key = malloc(strlen(k));
        if (!new_node->key) 
        {
            free(new_node);
            return NULL;
        }
        strcpy(new_node->key, k);
        new_node->value = v;
        new_node->left = new_node->right = NULL;
        return new_node;
    }

    int cmp = strcmp(k, node->key);
    if (cmp < 0) 
        node->left = add_node(node->left, k, v);
    else if (cmp > 0)
        node->right = add_node(node->right, k, v);
    else
        node->value = v;
    return node;
}

bool associative_array_add(assoc_array_t array, key k, value v) 
{
    if (!array || !k) 
        return false;
    array->root = add_node(array->root, k, v);
    return true;
}

tree_node_t* find_node(tree_node_t *node, key k) 
{
    if (!node) 
        return NULL;
    int cmp = strcmp(k, node->key);
    if (cmp == 0) return node;
    if (cmp < 0) return find_node(node->left, k);
    return find_node(node->right, k);
}

value associative_array_get(assoc_array_t array, key k) 
{
    if (!array || !k) return -1;
    tree_node_t *node = find_node(array->root, k);
    return node ? node->value : -1;
}

static tree_node_t *find_minimum(tree_node_t *node) 
{
    while (node->left != NULL) 
        node = node->left;
    return node;
}

// Вспомогательная функция для удаления узла из дерева
static tree_node_t *remove_node(tree_node_t *node, key k, bool *success) 
{
    if (node == NULL) 
    {
        *success = false;
        return NULL;
    }

    int cmp = strcmp(k, node->key);
    if (cmp < 0) 
    {
        node->left = remove_node(node->left, k, success);
    }
    else if (cmp > 0) 
    {
        node->right = remove_node(node->right, k, success);
    } 
    else 
    {
        *success = true;

        if (node->left == NULL && node->right == NULL) 
        {
            free(node->key);
            free(node);
            return NULL;
        }

        if (node->left == NULL) 
        {
            tree_node_t *right_child = node->right;
            free(node->key);
            free(node);
            return right_child;
        } 
        else if (node->right == NULL) 
        {
            tree_node_t *left_child = node->left;
            free(node->key);
            free(node);
            return left_child;
        }

        tree_node_t *min_node = find_minimum(node->right);
        free(node->key);
        node->key = malloc(strlen(min_node->key));
        if (!node->key)
            return NULL;
        strcpy(node->key, min_node->key);
        node->value = min_node->value;
        node->right = remove_node(node->right, min_node->key, success);
    }

    return node;
}

// Основная функция удаления
bool associative_array_remove(assoc_array_t array, key k) 
{
    if (array == NULL || k == NULL) {
        return false;
    }

    bool success = false;
    array->root = remove_node(array->root, k, &success);
    return success;
}