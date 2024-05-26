#include "file_checker.h"


int check_file_int(FILE *input_file)
{
    if (input_file == NULL)
    {
        fclose(input_file);
        printf("Ошибка чтения файла");
        return WRONG_FILE;
    }

    int number;
    char space;
    while (fscanf(input_file, "%d%c", &number, &space) == 2)
    {
        if (!isspace(space) && space != EOF)
        {
            fclose(input_file);
            return WRONG_CHAR; 
        }
    }
    if (!feof(input_file)) 
    {
        fclose(input_file);
        return WRONG_FORMAT;
    }


    return EXIT_SUCCESS;
}