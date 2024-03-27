#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int number, composition = 1;

    scanf("%d", &number);
    number = abs(number);

    while (number > 0)
    {
        composition *= number % 10;
        number /= 10;
    }

    printf("%d", composition);

    return EXIT_SUCCESS;
}