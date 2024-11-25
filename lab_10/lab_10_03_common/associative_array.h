#ifndef ASSOCIATIVE_ARRAY_H
#define ASSOCIATIVE_ARRAY_H


#include <stdbool.h>

typedef char *key;
typedef int value;


typedef struct assoc_array* assoc_array_t;


// Создание ассоциативного массива
assoc_array_t associative_array_create();

// Удаление ассоциативного массива
void associative_array_destroy(assoc_array_t array);

// Добавление элемента (ключ-значение)
bool associative_array_add(assoc_array_t array, key key, value value);

// Получение значения по ключу
value associative_array_get(assoc_array_t array, key key);

// Удаление элемента по ключу
bool associative_array_remove(assoc_array_t array, key key);




#endif