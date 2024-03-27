#include <stdio.h>
#include <stdlib.h>

// v0 = 4, a = 5, t = 10 || s = 290.00
// v0 = 10, a = 20, t = 30 || s = 9300.00


int main(void)
{
    float v0, a, t, s;
    printf("Введите vo, a, t\n");
    scanf("%f %f %f", &v0, &a, &t);
    s = v0 * t + (a * t * t) / 2;
    printf("%.2f\n", s);


    return EXIT_SUCCESS;
}
