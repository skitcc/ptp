#include "read_data.h"

int check_fields(FILE *input, struct product products[], int *count) {
    char name[NAME_LEN + 2];
    while (fgets(name, sizeof(name), input) != NULL) 
    {
        
        char producer[PRODUCER_LEN + 2];
        uint32_t price;
        uint32_t quantity;

        if (name[strcspn(name, "\n")] != '\n' && !feof(input)) {
            printf("Длина имени превышает допустимую длину\n");
            return WRONG_NAME;
        }
        name[strcspn(name, "\n")] = '\0';

        if (fgets(producer, sizeof(producer), input) == NULL || (producer[strcspn(producer, "\n")] != '\n' && !feof(input))) {
            printf("Длина изготовителя превышает допустимую длину\n");
            return WRONG_PRODUCER;
        }

        producer[strcspn(producer, "\n")] = '\0';
        char buffer[100];
        if (fgets(buffer, sizeof(buffer), input) == NULL || sscanf(buffer, "%" SCNu32, &price) != 1) 
        {
            printf("Ошибка в цене!\n");
            return WRONG_PRICE;
        }

        if (fgets(buffer, sizeof(buffer), input) == NULL || sscanf(buffer, "%" SCNu32, &quantity) != 1)
        {
            printf("Ошибка в кол-ве товара!\n");
            return WRONG_QUANTITY;
        }

        if (*count >= MAX_PRODUCTS) {
            return WRONG_AMOUNT;
        }

        strcpy(products[*count].name, name);
        strcpy(products[*count].producer, producer);
        products[*count].price = price;
        products[*count].quantity = quantity;
        (*count)++;
    }
    if (*count == 0)
        return EMPTY_FILE;
    return EXIT_SUCCESS;
}

int check_field(FILE *input, struct product *product_in) 
{
    char name[NAME_LEN + 2]; 
    char producer[PRODUCER_LEN + 2]; 

    if (fgets(name, sizeof(name), input) == NULL || (name[strcspn(name, "\n")] != '\n' && !feof(input))) 
    {
        printf("Длина имени превышает допустимую длину\n"); 
        return WRONG_NAME;
    }

    name[strcspn(name, "\n")] = '\0';

    if (fgets(producer, sizeof(producer), input) == NULL || (producer[strcspn(producer, "\n")] != '\n' && !feof(input))) {
        printf("Длина изготовителя превышает допустимую длину\n");
        return WRONG_PRODUCER;
    }

    producer[strcspn(producer, "\n")] = '\0';

    if (fscanf(input, "%" SCNu32, &product_in->price) != 1) 
    {
        printf("Ошибка в цене!\n");
        return WRONG_PRICE;
    }

    if (fscanf(input, "%" SCNu32, &product_in->quantity) != 1) 
    {
        printf("Ошибка в кол-ве товара!\n");
        return WRONG_QUANTITY;
    }

    strcpy(product_in->name, name);
    strcpy(product_in->producer, producer);

    return EXIT_SUCCESS;
}
