#include "read.h"

int student_create(node_t **node, FILE *f)
{
    student_info *data = malloc(sizeof(student_info));
    if (!data)
    {
        return 1;
    }
    // printf("file2 : %p\n", (void *)f);
    char buffer[100];
    if (fgets(buffer, sizeof(buffer), f) == NULL)
    {
        printf("Error reading age: fgets failed\n");
        free(data);
        return 2;
    }

    buffer[strlen(buffer) - 1] = '\0';
    // printf("buffer : %s\n", buffer);
    if (sscanf(buffer, "%d", &data->age) != 1)
    {
        printf("Error reading age: sscanf failed\n");
        free(data);
        return 2;
    }

    if (data->age < 0)
        return 1;
    if (fgets(buffer, sizeof(buffer), f) == NULL || sscanf(buffer, "%d", &data->course) != 1)
    {
        free(data);
        return 2;
    }

    if (data->course < 0)
        return 2;
    // printf("age : %d, course : %d\n", data->age, data->course);
    size_t n = 0;
    

    char *name = NULL;
    if (getline(&name, &n, f) == -1)
    {
        printf("err here!\n");
        free(data);
        return 3;
    }
    // printf("name : %s\n", name);

    if ((name)[strcspn(name, "\n")] != '\n') 
    {
        free(name);
        free(data);
        return 2;
    }
    if (name[0] == '\n') 
    {
        printf("here!\n");
        free(name);
        free(data);
        return 1;
    }

    name[strcspn(name, "\n")] = '\0';

    data->name = malloc((sizeof(name)) * sizeof(char));
    strcpy(data->name, name);

    free(name);
    

    *node = malloc(sizeof(node_t));
    if (!(*node))
    {
        free(data->name);
        free(data);
        free(name);
        return 1;
    }

    // printf("age : %d, course : %d, name : %s\n", data->age, data->course, data->name);
    (*node)->data = data;
    (*node)->next = NULL;

    return 0; 
}

int read_whole_file(node_t **head, char *filename)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL)
        return 1;

    int n = 0;
    char buffer[100];
    if (fgets(buffer, sizeof(buffer), f) == NULL || sscanf(buffer, "%d", &n) != 1)
    {
        fclose(f);
        return 1;
    }
    printf("n = %d\n", n);
    node_t *tail = NULL;
    for (int i = 0; i < n; i++)
    {
        node_t *new_node = NULL;
        if (student_create(&new_node, f))
        {
            free_list(*head);
            fclose(f);
            return 1;
        }

        if (*head == NULL)
            *head = new_node;
        else
            tail->next = new_node;

        tail = new_node;
    }

    fclose(f);
    return 0;
}
