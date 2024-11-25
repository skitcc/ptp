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
            if (create_node(&new_node))
            {
                free_list(current);
                free_list(current_2);
                free_list(str1);
                free_list(str2);
                return NULL;
            }
            current->next = new_node;
            current = new_node;
        }
    }
    free_list(str2);
    return str1;
}

int collapse_spaces(list_t *head)
{
    if (!head)
        return 1;

    list_t *current = head;
    bool is_all_spaces = true;
    while (current != NULL)
    {
        for (int i = 0; i < PART_SIZE; i++)
        {
            if (current->part[i] != ' ' && current->part[i] != '\0')
            {
                is_all_spaces = false;
                break;
            }
        }
        current = current->next;
    }
    if (is_all_spaces)
        return 2;
    current = head;
    bool space_found = false;
    while (current != NULL)
    {
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

        }
        for (int i = true_index; i < PART_SIZE; i++)
        {
            current->part[i] = '\0';
        }
        current = current->next;
    }
    return 0;
}

int find_substring(list_t *head, list_t *sub_head)
{
    if (!head || !sub_head)
    {
        return -1; 
    }

    list_t *h_cur = head;     
    list_t *n_cur = sub_head; 
    int h_index = 0;          
    int match_index = -1;     
    int h_pos = 0;            
    int n_pos = 0;            

    while (h_cur)
    {
        
        if (h_cur->part[h_pos] == n_cur->part[n_pos])
        {
            
            if (match_index == -1) 
                match_index = h_index;

            
            n_pos++;
            if (n_cur->part[n_pos] == '\0' || n_pos == PART_SIZE) 
            {
                n_cur = n_cur->next;
                n_pos = 0;
            }

            if (!n_cur)
                return match_index;
        }
        else
        {
            
            if (match_index != -1)
            {
               
                h_pos = (match_index + 1) % PART_SIZE;
                h_index = match_index + 1;
                h_cur = head;
                for (int i = 0; i < h_index / PART_SIZE; i++)
                    h_cur = h_cur->next;

                match_index = -1;
                n_cur = sub_head;
                n_pos = 0;
                continue; 
            }
        }
        h_pos++;
        h_index++;

        if (h_pos == PART_SIZE || h_cur->part[h_pos] == '\0')
        {
            h_cur = h_cur->next;
            h_pos = 0;
        }
    }

    return -1;
}


