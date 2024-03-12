#include <stdio.h>
#include <stdlib.h>

void rec_print(int n) 
{
    if (n == 0) 
        return;
    
    rec_print(n / 10);

    printf("%d", n % 10);
}

int main(void) 
{
    int n, rc;

    printf("Введите натуральное число: ");
    rc = scanf("%d", &n);
    if (rc != 1 || n <= 0) 
    {
        printf("Ошибка ввода.\n");
        return EXIT_FAILURE;
    }

    if (n == 0) 
        printf("0\n"); 
    else 
    {
        rec_print(n);
        printf("\n");
    }

    return EXIT_SUCCESS;
}
