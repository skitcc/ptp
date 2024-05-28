#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    srand(time(NULL));
    printf("%d ", rand() % 1000);
    printf("%d ", rand() % 1000);
    printf("%d ", rand() % 1000);
    printf("%d ", rand() % 1000);
    printf("%d\n", rand() % 1000);
}