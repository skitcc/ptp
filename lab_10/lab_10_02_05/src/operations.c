#include "operations.h"


list_t *concatenate(list_t *str1, list_t *str2) 
{
    if (str1 == NULL)
        return str2;

    list_t *current = str1;

    while (current->next != NULL)
        current = current->next;

    int pos = 0;
    while (pos < PART_SIZE && current->part[pos] != '\0')
        pos++;

    list_t *current_2 = str2;

    while (current_2 != NULL) 
    {
        for (int i = 0; i < PART_SIZE && current_2->part[i] != '\0'; i++) 
        {
            if (pos == PART_SIZE)
            {
                list_t *new_node = NULL;
                if (create_node(&new_node)) 
                {
                    free_list(str1);
                    free_list(str2);
                    str1 = NULL;
                    str2 = NULL;
                    return NULL;
                }
                current->next = new_node;
                current = new_node;
                pos = 0;
            }

            current->part[pos++] = current_2->part[i];
        }
        current_2 = current_2->next;
    }

    if (pos < PART_SIZE)
        current->part[pos] = '\0';
    else if (current->next == NULL)
    {
        list_t *new_node = NULL;
        if (create_node(&new_node)) 
        {
            free_list(str1);
            free_list(str2);
            str1 = NULL;
            str2 = NULL;
            return NULL;
        }
        current->next = new_node;
        new_node->part[0] = '\0';
    }

    free_list(str2);
    str2 = NULL;
    return str1;
}


int collapse_spaces(list_t *head)
{
    if (!head)
        return 1;

    list_t *current = head;
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
        return -1; 

    int h_index = 0;             
    int match_index = -1;        
    size_t h_pos = 0, n_pos = 0;
    const list_t *h_cur = head;
    const list_t *n_cur = sub_head;

    while (h_cur) 
    {
        if (h_cur->part[h_pos] == n_cur->part[n_pos]) 
        {
            if (match_index == -1)
                match_index = h_index;

            n_pos++;
            h_pos++;

            if (n_pos == PART_SIZE || n_cur->part[n_pos] == '\0') 
            {
                n_cur = n_cur->next;
                n_pos = 0;
            }

            if (!n_cur)
                return match_index;

            if (h_pos == PART_SIZE || h_cur->part[h_pos] == '\0') 
            {
                h_cur = h_cur->next;
                h_pos = 0;
            }
        } 
        else 
        {
            if (match_index != -1) 
            {
                h_index = match_index + 1; 
                match_index = -1; 
                n_cur = sub_head;
                n_pos = 0;

                h_cur = head;
                h_pos = h_index % PART_SIZE;
                for (int i = 0; i < h_index / PART_SIZE; i++)
                    h_cur = h_cur->next;
            } 
            else 
            {
                h_pos++;
                h_index++;

                if (h_pos == PART_SIZE || h_cur->part[h_pos] == '\0') 
                {
                    h_cur = h_cur->next;
                    h_pos = 0;
                }
            }
        }
    }

    return -1;
}



