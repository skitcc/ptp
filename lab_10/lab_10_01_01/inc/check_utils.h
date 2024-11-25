#ifndef CHECK_UTILS_H
#define CHECK_UTILS_H

#include <check.h>
#include <stdlib.h>
#include <string.h>
#include "list_operations.h"


node_t *node_create(void *data);
student_info *create_student(int age, int course, const char *name);
void student_free(student_info *student);
void free_list_with_data(node_t *head, void (*free_data)(void *));


#endif