#include "read.h"



int create_node(list_t **node)
{

    (*node) = malloc(sizeof(list_t));
    if (!(*node))
        return 1;
    
    (*node)->next = NULL;

    return 0;
}


int read_str_to_list(char *str, list_t **head)
{
    size_t len = strlen(str);
    printf("len : %zu\n", len);
    if (len == 0)
        return 1;

    size_t shift = 0;
    if (len % PART_SIZE)
        shift = PART_SIZE - len % PART_SIZE;
    size_t prev_len = len;
    len += shift;
    str = realloc(str, len);
    if (!str)
        return 2;

    printf("shifted_len : %zu\n", len);
    for (size_t i = prev_len; i < len; i++)
        str[i] = '\0';
    // printf("str : %s\n", str);

    list_t *tail = NULL;
    for (size_t i = PART_SIZE; i <= len; i += PART_SIZE)
    {
        list_t *new_node = NULL;
        if (create_node(&new_node))
            return 1;
        printf("i = %zu\n", i);
        for (size_t c = 0; c < PART_SIZE; c++)
        {
            new_node->part[c] = str[i - PART_SIZE + c];
            // printf("elem : %c\n", new_node->part[c]);
            // printf("new_node : %s\n", new_node->part);
        }
        // printf("new_node_part %s\n", new_node->part);
        if ((*head) == NULL)
        {
            *head = new_node;
        }
        else
            tail->next = new_node;

        tail = new_node;

    }
    return 0;
}