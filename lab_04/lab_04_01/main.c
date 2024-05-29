#include "tests.h"
#include <stdio.h>
#include <string.h>


int main(void) 
{
    size_t total_errors = 0;

    total_errors += test_strpbrk();
    total_errors += test_strspn();
    total_errors += test_strcspn();
    total_errors += test_strchr();
    total_errors += test_strrchr();

    printf("Кол-во проваленных тестов : %zu\n", total_errors);
    return 0;
}
