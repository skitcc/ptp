#include "my_funcs.h"
#include <stdio.h>
#include <string.h>



int main(void)
{
    // Тестовые данные для strpbrk
    const char str1[5] = "hell";
    const char str2[5] = "wrld";

    // Тестовые данные для strspn
    char str [100] = "baaaba4";
    char sym [10] = "ab";

    // Тестовые данные для strcspn
    char str3 [100] = "12efab";
    char sym2 [10] = "ab";

    // Тестовые данные для strchr
    const char str_strchr[5] = "awda";
    int ch = 'a';

    // Тестовые данные для strrchr
    char str_strrchr[5] = "awdk";
    int ch1 = 'd';

    size_t acceptance = 0;

    if (my_strpbrk(str1, str2) != strpbrk(str1, str2))
        acceptance++;

    if (my_strspn(str, sym) != strspn(str, sym))
        acceptance++;

    if (my_strcspn(str3, sym2) != strcspn(str3, sym2))
        acceptance++;

    if (my_strchr(str_strchr, ch) != strchr(str_strchr, ch))
        acceptance++;

    if (my_strchr(str_strrchr, ch1) != strrchr(str_strrchr, ch1))
        acceptance++;

    printf("Кол-во проваленных тестов : %zu", acceptance);
}
