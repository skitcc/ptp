#include "utils.h"



void print_list(node_t *head)
{
    node_t *current = head;

    while (current != NULL)
    {
        student_info *student = (student_info *)current->data;
        printf("age : %d, course : %d, name : %s\n", student->age, student->course, student->name);
        current = current->next;
    }
}


int print_list_to_file(node_t *head, char *filename)
{
    node_t *current = head;

    FILE *f = fopen(filename, "w");

    if (f == NULL)
    {
        return 1;
    }
    while (current != NULL)
    {
        student_info *student = (student_info *)current->data;
        fprintf(f, "age : %d, course : %d, name : %s\n", student->age, student->course, student->name);
        current = current->next;    
    }
    fclose(f);
    return 0;
}

void free_list(node_t *head)
{
    while (head) 
    {
        node_t *temp = head;
        head = (head)->next;
        free(((student_info *)temp->data)->name);
        free(temp->data);               
        free(temp);
    }
}