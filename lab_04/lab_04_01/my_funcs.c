#include "my_funcs.h"

// Функция ищет в строке s1 первое вхождение любого символа из строки s2.
char *my_strpbrk(const char *s1, const char *s2)
{
    for (int i = 0; s1[i] != '\0'; i++)
    {
        for (int j = 0; s2[j] != '\0'; j++)
        {
            if (s1[i] == s2[j])
                return (char *)&s1[i];
        }
    }
    return NULL;
}
// Функция возвращает длину начального сегмента строки s1, содержащего только символы из строки s2.
size_t my_strspn(const char *s1, const char *s2)
{
    const char *ptr1, *ptr2;
    size_t count = 0;
    for (ptr1 = s1; *ptr1 != '\0'; ptr1++)
    {
        for (ptr2 = s2; *ptr2 != '\0'; ptr2++)
        {
            if (*ptr1 == *ptr2)
            {
                count++;
                break;
            }
        }
        if (*ptr2 == '\0')
            break;
    }
    return count;
}

// Функция возвращает длину начального сегмента строки s1, не содержащего символы из строки s2.
size_t my_strcspn(const char *s1, const char *s2)
{
    const char *ptr1, *ptr2;
    size_t count = 0;
    for (ptr1 = s1; *ptr1 != '\0'; ptr1++)
    {
        for (ptr2 = s2; *ptr2 != '\0'; ptr2++)
        {
            if (*ptr1 == *ptr2)
            {
                return count;
            }
        }
        count++;
    }
    return count;
}

// Функция находит первое вхождение символа ch в строке s.
char *my_strchr(const char *s, int ch) 
{
    if (s == NULL)
        return NULL;

    if (ch == 0)
        return (char *)(s + strlen(s));

    if (ch > 255 || ch < 0)
        return NULL;

    while (*s != '\0') 
    {
        if (*s == ch) 
            return (char *)s;
        s++;
    }
    return NULL;
}

// Функция находит последнее вхождение символа ch в строке s.
char *my_strrchr(const char *s, int ch)
{
    if (s == NULL)
    return NULL;

    if (ch == 0)
        return (char *)(s + strlen(s));

    if (ch > 255 || ch < 0)
        return NULL;

    const char *ptr1;
    for (ptr1 = s + strlen(s) - 1; ptr1 >= s; ptr1--)
    {
        if (*ptr1 == ch)
            return (char *)ptr1;
    }
    return NULL;
}
