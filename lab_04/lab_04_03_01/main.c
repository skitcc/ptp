#include "solve_task.h"
#include "constraints.h"
#include <stdio.h>
#include <string.h>


int main(void) 
{
    char str[MAX_LEN_STRING + 1];
    char words[MAX_LEN_STRING / 2][MAX_SIZE_WORD + 1];
    char result[MAX_LEN_STRING + 1] = "";
    size_t word_count;
    printf("Введите одну строку\n");

    char *input_check = fgets(str, MAX_LEN_STRING + 1, stdin);
    if (input_check == NULL)
        return ERROR_READ_STRING;
    size_t size = strlen(str);
    if (str[size - 1] != '\n')
    {
        printf("Длина строки превышает максимально допустимую длину\n");
        return ERROR_LEN_STRING;
    }
    str[size - 1] = '\0';
    int len = fill_array(words, str, &word_count);
    if (len == -1)
    {
        printf("Длина слова превышает максимально допустимую длину\n");
        return ERROR_SIZE_WORD;
    }

    compare_to_last(words, word_count, result);
    if (strlen(result) == 0)
    {
        printf("Все слова удалены\n");
        return ERROR_ALL_WORDS_DELETED;
    }
    printf("Result: %s\n", result);


    return 0;
}
