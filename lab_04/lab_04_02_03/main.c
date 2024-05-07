#include "solve_task.h"

#include <stdio.h>


int main(void)
{
    char str1[MAX_LEN_STRING + 1];
    char str2[MAX_LEN_STRING + 1];
    char words1[MAX_LEN_STRING / 2][MAX_SIZE_WORD + 1];
    char words2[MAX_LEN_STRING / 2][MAX_SIZE_WORD + 1];
    char result[MAX_LEN_STRING * 2 + 1] = "";
    size_t word_count1, word_count2;

    // printf("Введите две строки подряд:\n");
    char *input_check1 = fgets(str1, MAX_LEN_STRING + 1, stdin);
    if (input_check1 == NULL)
        return ERROR_READ_STRING;
    size_t size = strlen(str1);
    if (str1[size - 1] != '\n')
    {
        // printf("Длина строки превышает максимально допустимую длину\n");
        return ERROR_LEN_STRING;
    }

    str1[size - 1] = '\0';
    int len1 = fill_array(words1, str1, &word_count1);
    if (len1 == -1)
    {
        // printf("Длина слова превышает максимально допустимую длину\n");
        return ERROR_SIZE_WORD;
    }


    char *input_check2 = fgets(str2, MAX_LEN_STRING + 1, stdin);
    if (input_check2 == NULL)
        return ERROR_READ_STRING;

    size_t size1 = strlen(str2);
    if (str2[size1 - 1] != '\n')
    {
        // printf("Длина строки превышает максимально допустимую длину\n");
        return ERROR_LEN_STRING;
    }

    str2[size1 - 1] = '\0';
    int len2 = fill_array(words2, str2, &word_count2);
    if (len2 == -1)
    {
        // printf("Длина слова превышает максимально допустимую длину\n");
        return ERROR_SIZE_WORD;
    }



    print_result(words1, words2, word_count1, word_count2, result);
    if (strlen(result) == 0)
    {
        // printf("Все слова удалены");
        return ERROR_ALL_DELETED;
    }
    printf("Result: %s\n", result);
    return 0;
}
