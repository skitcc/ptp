#include "read_data.h"

int check_fields(FILE *input, struct product products[], int *count) {
    while (1) {
        char name[NAME_LEN + 1];
        char producer[PRODUCER_LEN + 1];
        uint32_t price;
        uint32_t quantity;

        if (fgets(name, NAME_LEN + 1, input) == NULL) {
            break;
        }
        name[strcspn(name, "\n")] = '\0';

        if (fgets(producer, PRODUCER_LEN + 1, input) == NULL) {
            printf("Error in producer\n");
            return WRONG_PRODUCER;
        }
        producer[strcspn(producer, "\n")] = '\0';

        char buffer[100];
        if (fgets(buffer, sizeof(buffer), input) == NULL || sscanf(buffer, "%" SCNu32, &price) != 1) {
            printf("Error in price\n");
            return WRONG_PRICE;
        }

        if (fgets(buffer, sizeof(buffer), input) == NULL || sscanf(buffer, "%" SCNu32, &quantity) != 1) {
            printf("Error in quantity\n");
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
    return EXIT_SUCCESS;
}

int check_field(FILE *input, struct product *product_in) {
    if (fgets(product_in->name, NAME_LEN + 1, input) == NULL) {
        return WRONG_NAME;
    }
    product_in->name[strcspn(product_in->name, "\n")] = '\0';

    if (fgets(product_in->producer, PRODUCER_LEN + 1, input) == NULL) {
        printf("Error in producer\n");
        return WRONG_PRODUCER;
    }
    product_in->producer[strcspn(product_in->producer, "\n")] = '\0';

    char buffer[100];
    if (fgets(buffer, sizeof(buffer), input) == NULL || sscanf(buffer, "%" SCNu32, &product_in->price) != 1) {
        printf("Error in price\n");
        return WRONG_PRICE;
    }

    if (fgets(buffer, sizeof(buffer), input) == NULL || sscanf(buffer, "%" SCNu32, &product_in->quantity) != 1) {
        printf("Error in quantity\n");
        return WRONG_QUANTITY;
    }
    return EXIT_SUCCESS;
}
