#define _GNU_SOURCE

#include <stdio.h> 
#include <string.h>



#include "struct.h"
#include "utils.h"
#include "read.h"
#include "operations.h"

int main(void)
{

    char option[10];
    if (fgets(option, sizeof(option), stdin) == NULL)
        return 1;

    option[strlen(option) - 1] = '\0';

    list_t *head = NULL;


    if (strcmp(option, "cat") == 0)
    {
        char *input_str1 = NULL;
        char *input_str2 = NULL;
        size_t n = 0;

        if (getline(&input_str1, &n, stdin) == -1)
        {
            return 1;
        }

        if (getline(&input_str2, &n, stdin) == -1)
        {
            free(input_str1);
            return 2;
        }

        // if (input_str1[strlen(input_str1) - 1] == '\n')
        input_str1[strlen(input_str1) - 1] = '\0';
        // if (input_str2[strlen(input_str2) - 1] == '\n')
        input_str2[strlen(input_str2) - 1] = '\0';
        // printf("%s\n", input_str1);
        // printf("%s\n", input_str2);

        list_t *head1 = NULL;
        list_t *head2 = NULL;

        if (read_str_to_list(input_str1, &head1) != 0)
        {
            free(input_str1);
            free(input_str2);
            free_list(head1); 
            return 1;
        }

        if (read_str_to_list(input_str2, &head2) != 0)
        {
            free(input_str1);
            free(input_str2);
            free_list(head1);
            free_list(head2);
            return 2;
        }

        list_t *head = concatenate(head1, head2);
        if (!head)
        {
            free(input_str1);
            free(input_str2);
            free_list(head1);
            free_list(head2);
            return 3;
        }

        print_list(head);

        free(input_str1);
        free(input_str2);
        free_list(head);
        return 0;
    }

    else if (strcmp(option, "sps") == 0)
    {
        char *input_str = NULL;
        size_t n = 0;

        if (getline(&input_str, &n, stdin) == -1)
        {
            return 1;
        }

        if (strlen(input_str) == 0)
        {
            free(input_str);
            return 2;
        }

        input_str[strlen(input_str) - 1] = '\0';
        if (read_str_to_list(input_str, &head) != 0)
        {
            free(input_str);
            return 3;
        }

        int rc = collapse_spaces(head);

        if (rc != 0)
            return 4;

        print_list(head);
        free_list(head);
        free(input_str);
        return 0;


    }
    else if (strcmp(option, "pos") == 0)
    {
        char *input_str = NULL;
        list_t *head1 = NULL;
        size_t n = 0;

        if (getline(&input_str, &n, stdin) == -1)
        {
            return 1;
        }  
        input_str[strlen(input_str) - 1] = '\0';

        char *substring = NULL;
        if (getline(&substring, &n, stdin) == -1)
        {
            free(input_str);
            return 1;
        }  
        substring[strlen(substring) - 1] = '\0';
        if (strlen(substring) == 0)
            return 2;

        if (read_str_to_list(input_str, &head) != 0)
        {
            free(input_str);
            free(substring);
            return 1;
        }

        if (read_str_to_list(substring, &head1) != 0)
        {
            free(input_str);
            free(substring);
            return 1;
        }


        int result = find_substring(head, head1);
        if (result == -1)
        {
            free(input_str);
            free(substring);
            free_list(head1);
            free_list(head);
            return 1;
        }

        printf("%d\n", result);
        free_list(head);
        free_list(head1);
        free(substring);
        free(input_str);
        return 0;


    }
    else
    {
        free_list(head);
        return 2;
    }
}