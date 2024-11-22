#include "utils.h"


void print_list(list_t *head)
{
    list_t *current = head;
    printf("sentense :");
    while (current != NULL)
    {
        printf("%s", current->part);
        current = current->next;
    }
    printf("\n");
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