#include "solve_task.h"

// Функция для для проверки разделителя
int is_separator(const char symbol, const char *separators)
{
    for (size_t i = 0; i < strlen(separators); i++)
        if (symbol == separators[i])
            return 0;

    return 1;
}
// Заполнение массива по словам
int fill_array(char array[MAX_LEN_STRING / 2][MAX_SIZE_WORD + 1], char str[MAX_LEN_STRING + 1], size_t *word_count)
{
    *word_count = 0;
    int i = 0;
    while (*str != '\0') 
    {
        while (!is_separator(*str, SEPARATORS))
            str++;
        if (*str == '\0')
            break;
        while (is_separator(*str, SEPARATORS) && *str != '\0') 
        {
            array[*word_count][i++] = *str;
            str++;
        }
        array[*word_count][i] = '\0';
        (*word_count)++;
        if (i >= MAX_SIZE_WORD)
            return -1;
        i = 0;
    }
    return 0;
}

// Проверка на уникальность элемента в одной линии
bool is_uniq_in_line(char array[MAX_LEN_STRING / 2][MAX_SIZE_WORD + 1], int word_count, char word[MAX_SIZE_WORD + 1], int position)
{
    char cleaned_array_elem[MAX_SIZE_WORD];
    char cleaned_word[MAX_SIZE_WORD];
    strcpy(cleaned_word, word);
    cleaned_word[strcspn(cleaned_word, "\n")] = '\0';
    for (int i = 0; i < word_count; i++)
    {
        strcpy(cleaned_array_elem, array[i]);
        cleaned_array_elem[strcspn(cleaned_array_elem, "\n")] = '\0';
        if (i == position)
            continue;
        if (strcmp(cleaned_array_elem, cleaned_word) == 0)
            return false;
    }
    return true;
}
// Проверка на уникальность элемента в другоой линии
bool is_uniq_in_other(char array[MAX_LEN_STRING / 2][MAX_SIZE_WORD + 1], int word_count, char word[MAX_SIZE_WORD + 1])
{
    for (int i = 0; i < word_count; i++)
    {
        if (strcmp(array[i], word) == 0)
            return false;
    }
    return true;
}

// Печать результата
void print_result(char array1[MAX_LEN_STRING / 2][MAX_SIZE_WORD + 1], char array2[MAX_LEN_STRING / 2][MAX_SIZE_WORD + 1], int word_count1, int word_count2, char result[MAX_LEN_STRING * 2 + 1])
{
    char cleaned_word[MAX_SIZE_WORD];
    for (int i = 0; i < word_count1; i++)
    {
        if (is_uniq_in_line(array1, word_count1, array1[i], i) && is_uniq_in_other(array2, word_count2, array1[i]))
        {
            strcpy(cleaned_word, array1[i]);
            cleaned_word[strcspn(cleaned_word, "\n")] = '\0';
            strcat(result, cleaned_word);
            strcat(result, " ");
        }
    }
    for (int i = 0; i < word_count2; i++)
    {
        if (is_uniq_in_other(array1, word_count1, array2[i]) && is_uniq_in_line(array2, word_count2, array2[i], i))
        {
            strcpy(cleaned_word, array2[i]);
            cleaned_word[strcspn(cleaned_word, "\n")] = '\0';
            strcat(result, cleaned_word);
            strcat(result, " ");
        }
    }
}
