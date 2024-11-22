#include "operations.h"


list_t *concatenate(list_t *str1, list_t *str2) 
{
    if (str1 == NULL) 
        return str2;

    list_t *current = str1;
    while (current->next != NULL) 
        current = current->next;

    list_t *current_2 = str2;
    int i = 0;

    while (current_2 != NULL) 
    {
        for (int j = 0; j < PART_SIZE && current_2 != NULL; j++) 
        {
            if (current->part[j] == '\0') 
            {
                while (i < PART_SIZE && current_2->part[i] != '\0') 
                {
                    current->part[j] = current_2->part[i++];
                    j++;

                    if (j >= PART_SIZE || i >= PART_SIZE || current_2->part[i] == '\0') 
                        break;
                }

                if (i >= PART_SIZE || current_2->part[i] == '\0') 
                {
                    current_2 = current_2->next;
                    i = 0; 
                }
            }
        }

        if (current->part[PART_SIZE - 1] != '\0') 
        {
            list_t *new_node = NULL;
            create_node(&new_node);
            current->next = new_node;
            current = new_node;
        }
    }

    return str1;
}

void collapse_spaces(list_t *head) 
{
    if (!head)
        return;

    list_t *current = head;
    list_t *prev = NULL;

    while (current != NULL)
    {
        // printf("1\n");
        bool space_found = false;
        int true_index = 0;
        for (int i = 0; i < PART_SIZE; i++)
        {
            if (current->part[i] == ' ')
            {
                if (!space_found)
                {
                    current->part[true_index++] = ' '; 
                    space_found = true;
                }
            }
            else
            {
                current->part[true_index++] = current->part[i]; 
                space_found = false;
            }
            // printf("current part first :%s\n", current->part);

        }
        for (int i = true_index; i < PART_SIZE; i++)
            current->part[i] = ' ';





        int next_index = 0;
        if (current->next != NULL)
        {
            if (current->part[PART_SIZE - 1] == ' ')
            {                
                while (current->next->part[next_index] == ' ' && next_index < PART_SIZE)
                    next_index++;
                for (int i = 0; i < PART_SIZE - next_index; i++)
                {
                    current->next->part[i] = current->next->part[i + next_index];
                }

                for (int i = PART_SIZE - next_index; i < PART_SIZE; i++)
                {
                    current->next->part[i] = '\0';
                }
            }


            while (true_index < PART_SIZE && strlen(current->next->part) > 0)
            {
                current->part[true_index++] = current->next->part[0];

                for (int i = 0; i < PART_SIZE - 1; i++)
                {
                    current->next->part[i] = current->next->part[i + 1];
                }
                current->next->part[PART_SIZE - 1] = '\0';
            }


            if (strlen(current->next->part) == 0)
            {
                list_t *node_to_delete = current->next;
                current->next = current->next->next;
                free(node_to_delete);
            }
        }

        bool is_spaced = true;
        for (int k = 0; k < PART_SIZE; k++)
        {
            if (current->part[k] != ' ')
                is_spaced = false;
        }

        printf("is_spaced : %d\n", is_spaced);

        if (current->next != NULL &&(strlen(current->part) == 0 || is_spaced))
        {
            printf("on delete null\n");
            list_t *node_to_delete = current;

            if (prev != NULL)
                prev->next = current->next; 
            else
                head = current->next;

            current = current->next;
            free(node_to_delete);
        }
        else
        {
            printf("current :%s\n", current->part);
            prev = current;
            current = current->next;
        }
    }
}


