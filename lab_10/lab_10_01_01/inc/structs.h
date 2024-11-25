#ifndef STRUCTS_H
#define STRUCTS_H


typedef struct student_info
{
    int age;
    int course;
    char *name;
} student_info;



typedef struct node
{
    void *data;
    struct node *next;
} node_t;


#endif 