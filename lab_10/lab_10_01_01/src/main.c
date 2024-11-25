#include "structs.h"
#include "read.h"
#include "utils.h"
#include "definitions.h"
#include "list_operations.h"
#include "solve_task.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>

int main(int argc, char *argv[])
{
    if (argc != 4)
        return ERROR_LEN_ARG;

    char in_file[MAX_LEN_FILENAME + 1];
    strncpy(in_file, argv[1], MAX_LEN_FILENAME + 1);
    char out_file[MAX_LEN_FILENAME + 1];
    strncpy(out_file, argv[2], MAX_LEN_FILENAME + 1);

    char task = 0;
    task = argv[3][0];



    node_t *head = NULL;

    if (read_whole_file(&head, in_file))
    {
        return 1;
    }

    printf("Предварительно созданный список\n");
    print_list(head);

    if (task == '1')
    {
        int age = 0, course = 0;
        char name[100], buffer[100];
        printf("Введите возвраст\n");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL || sscanf(buffer, "%d", &age) != 1)
        {
            return 1;
        }

        if (age < 0)
            return 2;

        printf("Введите курс обучения\n");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL || sscanf(buffer, "%d", &course) != 1)
            return 2;

        if (course < 0)
            return 3;

        printf("Введите имя\n");
        if (fgets(name, sizeof(name), stdin) == NULL)
            return 3;

        if (strlen(name) == 0)
            return 4;

        name[strlen(name) - 1] = '\0';
        insert_student(&head, age, course, name);
        print_list_to_file(head, out_file);
    }
    else if (task == '2')
    {
        head = reverse(head);
        print_list_to_file(head, out_file);
    }
    else 
        return 4;

    free_list(head);
    return 0;
}