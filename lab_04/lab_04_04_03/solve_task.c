#include "solve_task.h"

// Пропуск пробелов перед номером
void skip_whitespaces(char str[MAX_LEN_STRING + 1], int *counter)
{
    while (isspace(str[*counter]))
        (*counter)++;
}
// Пропуск кода строны
int skip_code_country(char str[MAX_LEN_STRING + 1], int *counter)
{
    int flag = 1;
    if (str[*counter] == '+')
    {
        (*counter)++;
        while (str[*counter] != '(')
        {
            if (!isdigit(str[*counter]))
                return 1;
            (*counter)++;
        }
    }
    else if (isdigit(str[*counter]))
    {
        flag = 0;
        (*counter)++;
        while (str[*counter] != '(')
        {
            if (!isdigit(str[*counter]))
                return 2;
            (*counter)++;
        }  
    }
    else if (str[*counter] == '(')
    {
        return 0;
    }
    else
    {
        return 3;
    }
    if (*counter == 1 && flag)
    {
        return 4;
    }
    return 0;
}
// Проверка кода оператора
int check_code_operator(char str[MAX_LEN_STRING + 1], int *counter)
{
    int count = 0;
    (*counter)++;
    while (str[*counter] != ')')
    {
        if (!isdigit(str[*counter]))
            return 1;
        count++;
        (*counter)++;
    }
    (*counter)++;
    if (count != 3)
        return 2;
    return 0;
}
// Проверка цифр (после кода страны и кода оператора)
int check_digits(char str[MAX_LEN_STRING + 1], int *counter, int len)
{
    int c = 0;
    if (str[*counter] == '-')
    {
        (*counter)++;
        while (isdigit(str[*counter]))
        {
            c++;
            (*counter)++;
        }
    }
    if (c != len)
        return 2;
    return 0;
}

// Основная функция проверки телефонного номиера 
int check_phone_number(char str[MAX_LEN_STRING + 1])
{
    int counter = 0;
    skip_whitespaces(str, &counter);
    // printf("%c", str[counter]);
    int code_skip = skip_code_country(str, &counter);
    if (code_skip != 0)
    {
        // printf("1\n");
        return 1;
    }
    int code_operator = check_code_operator(str, &counter);
    if (code_operator != 0)
    {
        // printf("2\n");
        return 2;
    }
    int code_digits1 = check_digits(str, &counter, 3);
    if (code_digits1 != 0)
    {
        // printf("3\n");
        return 3;
    }
    int code_digits2 = check_digits(str, &counter, 2);
    if (code_digits2 != 0)
    {
        // printf("4\n");
        return 4;
    }
    int code_digits3 = check_digits(str, &counter, 2);
    if (code_digits3 != 0)
    {
        // printf("5\n");
        return 5;
    }
    while ((size_t)counter < strlen(str))
    {
        if (!isspace(str[counter]) || !(str[counter] != '\0'))
            return 6;
        counter++;
    }
    return 0;
}
