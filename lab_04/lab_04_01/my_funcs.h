#ifndef MY_FUNCS_H
#define MY_FUNCS_H

#include <stddef.h>
#include <string.h>

char *my_strpbrk(const char *s1, const char *s2);
size_t my_strspn(const char *s1, const char *s2);
size_t my_strcspn(const char *s1, const char *s2);
char *my_strchr(const char *s1, int ch);
char *my_strrchr(const char *s1, int ch);



#endif
