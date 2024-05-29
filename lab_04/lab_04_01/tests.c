#include "tests.h"
size_t test_strpbrk(void) 
{
    const char strpbrk_check[][M][MAX_LEN] = 
    { 
        //Символов второй строки нету в первой строки
        { "abcdef", "xyz" }, 
        //Символ второй строки один раз в начале первой
        { "abcdef", "a" }, 
        // Размер первой строки 1 
        { "a", "abcdef" },
        // Строки полностью совпадают
        { "abcdef", "abcdef" },
        // Вторая строка пустая
        { "abc", "" },
        // Первая строка пустая
        { "", "abc" }
    };
    size_t errors = 0;

    for (size_t i = 0; i < sizeof(strpbrk_check) / sizeof(strpbrk_check[0]); i++) 
    {
        const char *result_my = my_strpbrk(strpbrk_check[i][0], strpbrk_check[i][1]);
        const char *result_std = strpbrk(strpbrk_check[i][0], strpbrk_check[i][1]);
        if (result_my != result_std) 
            errors++;
    }

    return errors;
}

size_t test_strspn(void) 
{
    const char strspn_check[][M][MAX_LEN] = 
    { 
        // Все символы вторки встречаются в первой
        { "abcdefghi", "cde" }, 
        // Не все символы второй строки встречаются в первой
        { "abcdefg", "fgh" }, 
        // Никакие символы второй строки не встречаются в первой
        { "abcdef", "xyz" }, 
        // Все символы второй строки встречаются в первой
        { "cccddee", "cde" }, 
        // Длина второй строки 1
        { "abcdef", "a" },
        // Вторая строка пустая
        { "abcdef", "" },
        // Первая строка пустая
        { "", "abcdef" }
    };
    size_t errors = 0;

    for (size_t i = 0; i < sizeof(strspn_check) / sizeof(strspn_check[0]); i++) 
    {
        size_t result_my = my_strspn(strspn_check[i][0], strspn_check[i][1]);
        size_t result_std = strspn(strspn_check[i][0], strspn_check[i][1]);
        if (result_my != result_std)
            errors++;
    }

    return errors;
}

size_t test_strcspn(void) 
{
    const char strcspn_check[][M][MAX_LEN] = 
    { 
        // Никакие символы из второй строки не встречаются в первой
        { "abcdef", "lmn" }, 
        // Длина второй строки 1, символ встречается в начале
        { "abcdef", "a" }, 
        // Длина второй строки 1, символ встречается в конце
        { "abcdef", "f" }, 
        // Длина первой строки 1, один символ встречается в начале
        { "a", "abcdef" },
        // Вторая строка пустая
        { "abcdef", "" },
        // Первая строка пустая
        { "", "abcdef" }
    };
    size_t errors = 0;

    for (size_t i = 0; i < sizeof(strcspn_check) / sizeof(strcspn_check[0]); i++) 
    {
        size_t result_my = my_strcspn(strcspn_check[i][0], strcspn_check[i][1]);
        size_t result_std = strcspn(strcspn_check[i][0], strcspn_check[i][1]);
        if (result_my != result_std)
            errors++;
    }

    return errors;
}

size_t test_strchr(void) 
{
    const char strchr_check[][MAX_LEN] = 
    { 
        
        "abcde", // символ встречается в середине строки
        "abcdef", // символ встречается в начале строки
        "abcdef", // символ не встречается в строке
        "ghijkl", // Нулевой байт
        "" // Первая строка пустая
    };
    const char strchr_check_chars[] = { 'c', 'a', 'z', '\0', 'k' };
    size_t errors = 0;

    for (size_t i = 0; i < sizeof(strchr_check) / sizeof(strchr_check[0]); i++) 
    {
        const char *result_my = my_strchr(strchr_check[i], strchr_check_chars[i]);
        const char *result_std = strchr(strchr_check[i], strchr_check_chars[i]);
        if (result_my != result_std)
            errors++;
    }

    return errors;
}

size_t test_strrchr(void) 
{
    const char strrchr_check[][MAX_LEN] = 
    { 
        "abcde", // символ встречается в середине строки
        "abcdef", // символ встречается в начале строки
        "abcdef", // символ не встречается в строке
        "ghijkl", // Нулевой байт
        "" //Первая строка пустая
    };
    const char strrchr_check_chars[] = { 'c', 'a', 'z', '\0', 'k' };
    size_t errors = 0;

    for (size_t i = 0; i < sizeof(strrchr_check) / sizeof(strrchr_check[0]); i++) 
    {
        const char *result_my = my_strrchr(strrchr_check[i], strrchr_check_chars[i]);
        const char *result_std = strrchr(strrchr_check[i], strrchr_check_chars[i]);
        if (result_my != result_std)
            errors++;
    }

    return errors;
}
