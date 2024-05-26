#include "ft.h"

int is_suffix(const char *name, const char *substr)
{
    int name_len = strlen(name);
    int suffix_len = strlen(substr);

    if (suffix_len > name_len) {
        return 0;
    }

    const char *name_end = name + name_len - suffix_len;
    return strcmp(name_end, substr) == 0;
}

int fill_name(const char *input_filename, const char *substr) 
{
    struct product products[MAX_PRODUCTS];
    FILE *input = fopen(input_filename, "r");
    if (input == NULL) 
    {
        printf("Файл неверно указан или не существует\n");
        return WRONG_FILE;
    }
    int count = 0;
    int rc = check_fields(input, products, &count);
    if (rc != 0)
    {
        fclose(input);
        return rc;
    }
    for (int i = 0; i < count; i++)
    {
        if (is_suffix(products[i].name, substr)) {
            printf("%s\n%s\n%u\n%u\n", products[i].name, products[i].producer, products[i].price, products[i].quantity);
        }
    }

    fclose(input);
    return 0;
}