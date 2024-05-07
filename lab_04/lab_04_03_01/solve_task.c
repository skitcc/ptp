#include "solve_task.h"
void fill_first_occurrences(char *str) 
{
    int hash[MAX_LEN_STRING] = { 0 };
    int cur_ind = 0;

    for (size_t i = 0; i < strlen(str); i++) 
    {
        unsigned char cur_char = str[i];
        if (hash[cur_char] == 0) 
        {
            hash[cur_char] = 1;
            str[cur_ind++] = cur_char;
        }
    }
    str[cur_ind] = '\0'; 
}

void compare_to_last(char array[MAX_LEN_STRING / 2][MAX_SIZE_WORD + 1], size_t word_count, char result[MAX_LEN_STRING + 1]) 
{
    char cleaned_word[MAX_SIZE_WORD];
    strcpy(cleaned_word, array[word_count - 1]);
    cleaned_word[strcspn(cleaned_word, "\n")] = '\0';
    for (int i = word_count - 2; i >= 0; --i) 
    {
        if (strcmp(array[i], cleaned_word) == 0) 
            continue;
        fill_first_occurrences(array[i]);
        strcat(result, array[i]);
        strcat(result, " ");
    }
}

int fill_array(char array[MAX_LEN_STRING / 2][MAX_SIZE_WORD + 1], char str[MAX_LEN_STRING + 1], size_t *word_count)
{
    *word_count = 0;
    while (*str != '\0') 
    {
        str += strspn(str, SEPARATORS);
        if (*str == '\0')
            break;
        size_t word_len = strcspn(str, SEPARATORS);
        strncpy(array[*word_count], str, word_len);
        array[*word_count][word_len] = '\0';
        
        (*word_count)++;
        if (word_len > MAX_SIZE_WORD)
            return -1;
        str += word_len;
    }
    return 0;
}