#include "check_args.h"


int check(int argc, char *argv[])
{
    if (argc > 5 || argc < 3)
        return 1;
    
    char action = '-';
    if (strlen(argv[1]) == 1)
        action = argv[1][0];
    else
        return 4;

    if (action == 'o' && argc != 4)
        return 2;

    if (strchr("oam", action) == NULL)
        return 3;
    return 0;
    
}
