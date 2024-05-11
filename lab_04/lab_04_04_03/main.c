#include "constraints.h"
#include "solve_task.h"

#include <stdio.h>
#include <string.h>


int main(void)
{
    char str[MAX_LEN_STRING + 1];
    char *input_check = fgets(str, MAX_LEN_STRING + 1, stdin);
    if (input_check == NULL)
        return 10;

    size_t size = strlen(str);
    if (str[size - 1] != '\n')
        return 11;
    str[size - 1] = '\0';
    int code_return = check_phone_number(str);
    if (code_return != 0)
        printf("NO");
    else
        printf("YES");
    return 0;
}
