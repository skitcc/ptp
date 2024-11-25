#include "read.h"

int create_node(list_t **node)
{
    (*node) = malloc(sizeof(list_t));
    if (!(*node))
        return 1;
    
    (*node)->next = NULL;
    memset((*node)->part, '\0', PART_SIZE);

    return 0;
}


int read_str_to_list(const char *str, list_t **head) 
{
    size_t len = strlen(str);
    if (len == 0)
        return 1;

    list_t *tail = NULL;
    for (size_t i = 0; i < len; i += PART_SIZE) 
    {
        list_t *new_node = NULL;
        if (create_node(&new_node)) 
        {
            free_list(*head);
            return 1;
        }
        memset(new_node->part, '\0', PART_SIZE);
        for (size_t c = 0; c < PART_SIZE; c++) 
        {
            if (i + c < len) 
            {
                new_node->part[c] = str[i + c];
            }
            else
            {
                new_node->part[c] = '\0';
            }
        }

        if (*head == NULL) 
        {
            *head = new_node;
        } 
        else 
        {
            tail->next = new_node;
        }

        tail = new_node;
    }
    return 0;
}