#include "utils.h"


void print_list(list_t *head)
{
    list_t *current = head;
    while (current != NULL)
    {
        for (size_t i = 0; i < PART_SIZE; i++) 
        {
            if (current->part[i] == '\0') 
                break;
            putchar(current->part[i]);
        }
        current = current->next;
    }
    putchar('\n');
}



void free_list(list_t *head)
{
    while (head) 
    {
        list_t *temp = head;
        head = (head)->next;
        free(temp);
    }
}