#include "at.h"

int is_sorted(struct product products[], int count) 
{
    for (int i = 0; i < count - 1; i++) 
    {
        if ((products[i].price < products[i + 1].price) || 
            ((products[i].price == products[i + 1].price) && 
             (products[i].quantity < products[i + 1].quantity))) 
            return 0;
    }
    return 1;
}

void insert_product(struct product products[], int *count, struct product product_in) 
{
    int position = *count;
    for (int i = 0; i < *count; i++) 
    {
        if ((product_in.price > products[i].price) || 
            ((product_in.price == products[i].price) && 
             (product_in.quantity > products[i].quantity))) 
        {
            position = i;
            break;
        }
    }

    for (int i = *count; i > position; i--) 
        products[i] = products[i - 1];

    products[position] = product_in;
    (*count)++;
}

int write_products_to_file(const char *filename, struct product products[], int count) 
{
    FILE *f = fopen(filename, "w");
    if (f == NULL) 
    {
        printf("Не удалось открыть файл для записи\n");
        return WRONG_FILE;
    }

    for (int i = 0; i < count; i++) 
    {
        if (i == count - 1) 
            fprintf(f, "%s\n%s\n%u\n%u", products[i].name, products[i].producer, products[i].price, products[i].quantity);
        else 
            fprintf(f, "%s\n%s\n%u\n%u\n", products[i].name, products[i].producer, products[i].price, products[i].quantity);
        
    }
    fclose(f);
    return 0;
}
int insert_field_in_pos(const char *argv[]) 
{
    struct product products[MAX_PRODUCTS];
    int count = 0;
    FILE *f = fopen(argv[2], "r");
    if (f == NULL) 
    {
        return WRONG_FILE;
    }
    struct stat st;
    stat(argv[2], &st);
    long size = st.st_size;
    if (size == 0)
        return EMPTY_FILE;


    int rc = check_fields(f, products, &count);
    if (rc != 0) 
    {
        fclose(f);
        return rc;
    }
    fclose(f);

    if (count >= MAX_PRODUCTS) 
    {
        return WRONG_AMOUNT;
    }

    struct product product_in;
    int rb = check_field(stdin, &product_in);
    if (rb != 0) 
    {
        return rb;
    }

    if (!is_sorted(products, count)) 
    {
        return NOT_SORTED;
    }

    insert_product(products, &count, product_in);
    return write_products_to_file(argv[2], products, count);
}
