#include <stdio.h>


/*
include studio.h
   main{}
   (
   int s;
   s: = 56;
   print (Year has s weeks)
   )
нет знака # перед include и <>, перепутанры местами () и {} 
лишний знак : при присваивании переменной значения, printf вместо print, забы %d
и не там стоит s, return 0, не правильно stdio, не хватает ; в конце
*/


int main(void)
{
    int s;
    s = 56;
    printf("Year has %d weeks\n", s);
    return 0;
}
