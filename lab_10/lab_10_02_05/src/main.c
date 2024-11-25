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
            free(input_str1);
            return 1;
        }

        if (getline(&input_str2, &n, stdin) == -1)
        {
            free(input_str1);
            free(input_str2);
            return 2;
        }

        size_t len1 = 0, len2 = 0;
        len1 = strlen(input_str1);
        len2 = strlen(input_str2);

        if (input_str1[len1 - 1] == '\n')
            input_str1[len1 - 1] = '\0';
        if (input_str2[len2 - 1] == '\n')
            input_str2[len2 - 1] = '\0';


        if (strlen(input_str1) == 0 || strlen(input_str2) == 0)
        {
            free(input_str1);
            free(input_str2);
            return 1;
        }
        list_t *head1 = NULL;
        list_t *head2 = NULL;

        if (read_str_to_list(input_str1, &head1) != 0)
        {
            free(input_str1);
            free(input_str2);
            return 1;
        }
        if (read_str_to_list(input_str2, &head2) != 0)
        {
            free(input_str1);
            free(input_str2);
            free_list(head1);
            head1 = NULL;
            return 2;
        }

        list_t *head = concatenate(head1, head2);
        if (!head)
        {
            free(input_str1);
            free(input_str2);
            return 3;
        }
        print_list(head);
        free(input_str1);
        free(input_str2);
        free_list(head);
        head = NULL;
        return 0;
    }
    else if (strcmp(option, "sps") == 0)
    {
        char *input_str = NULL;
        size_t n = 0;

        if (getline(&input_str, &n, stdin) == -1)
        {
            free(input_str);
            return 1;
        }

        size_t len = strlen(input_str);

        if (len > 0 && input_str[len - 1] == '\n')
        {
            input_str[len - 1] = '\0';
        }

        if (strlen(input_str) == 0)
        {
            free(input_str);
            return 2;
        }
        if (read_str_to_list(input_str, &head) != 0)
        {
            free(input_str);
            return 3;
        }

        int rc = collapse_spaces(head);

        if (rc != 0)
        {
            free(input_str);
            free_list(head);
            head = NULL;
            return 4;
        }
        print_list(head);
        free_list(head);
        head = NULL;
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
            free(input_str);
            return 1;
        }

        size_t len1 = strlen(input_str);
        if (len1 > 0 && input_str[len1 - 1] == '\n')
        {
            input_str[len1 - 1] = '\0';
        }

        char *substring = NULL;
        if (getline(&substring, &n, stdin) == -1)
        {
            free(substring);
            free(input_str);
            return 2;
        }
        size_t len = strlen(substring);
        if (len > 0 && substring[len - 1] == '\n')
        {
            substring[len - 1] = '\0';
        }

        if (strlen(input_str) == 0 || strlen(substring) == 0)
        {
            free(input_str);
            free(substring);
            return 2;
        }
        if (read_str_to_list(input_str, &head) != 0)
        {
            free(input_str);
            free(substring);
            return 3;
        }

        if (read_str_to_list(substring, &head1) != 0)
        {
            free(input_str);
            free(substring);
            free_list(head);
            head = NULL;
            return 4;
        }


        int result = find_substring(head, head1);

        printf("%d\n", result);
        free_list(head);
        free_list(head1);
        free(substring);
        free(input_str);
        head = NULL;
        head1 = NULL;
        return 0;
    }
    else if (strcmp(option, "out") == 0)
    {
        char *input_str = NULL;
        size_t n = 0;
        if (getline(&input_str, &n, stdin) == -1)
        {
            free(input_str);
            return 1;
        }
        size_t len = strlen(input_str);

        if (len > 0 && input_str[len - 1] == '\n')
        {
            input_str[len - 1] = '\0';
        }

        if (read_str_to_list(input_str, &head) != 0)
        {
            free(input_str);
            return 1;
        }
        print_list(head);
        free(input_str);
        free_list(head);
        head = NULL;
    }
    else
    {
        free_list(head);
        head = NULL;
        return 2;
    }
}
