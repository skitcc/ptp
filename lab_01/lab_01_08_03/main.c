#include <stdio.h>
#include <stdlib.h>

#define NUM_BIT 32
#define INPUT_NUMBER 1

void print_number(unsigned number)
{
    unsigned bit;
    printf("Result: ");

    for (int i = 0; i < NUM_BIT; i++)
    {
        if (i % 2 == 0)
            bit = (number >> (NUM_BIT - 2 - i)) & 1;
        else
            bit = (number >> (NUM_BIT - i)) & 1;

        printf("%u", bit);
    }
}

int main(void)
{	
    unsigned unsigned_number;

    if (scanf("%u", &unsigned_number) != INPUT_NUMBER)
    {
        printf("Error: input error");
        return EXIT_FAILURE;
    }

    print_number(unsigned_number);

    return EXIT_SUCCESS;		
}
