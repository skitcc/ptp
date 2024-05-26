#include "converter.h"

int txt_bin(const char *input_file, const char *output_file)
{
    FILE *input = fopen(input_file, "r");
    FILE *output = fopen(output_file, "wb");

    if (input == NULL || output == NULL)
    {
        if (input == NULL)
            printf("Ошибка чтения файла\n");
        if (output == NULL)
            printf("Ошибка создания файла\n");
        return WRONG_FILE;
    }

    int check_result = check_file_int(input);
    if (check_result != 0)
    {
        printf("Некорректный формат файла\n");
        fclose(output);
        return check_result;
    }
    rewind(input);

    int number;
    while (fscanf(input, "%d", &number) == 1)
    {
        fwrite(&number, sizeof(int), 1, output);
    }

    fclose(input);
    fclose(output);
    return EXIT_SUCCESS;
}

int bin_txt(const char *input_file, const char *output_file)
{
    FILE *input = fopen(input_file, "rb");
    FILE *output = fopen(output_file, "w");

    if (input == NULL || output == NULL)
    {
        if (input == NULL)
            printf("Ошибка чтения файла\n");
        if (output == NULL)
            printf("Ошибка создания файла\n");
        return WRONG_FILE;
    }

    int number;
    while (fread(&number, sizeof(int), 1, input) == 1)
    {
        fprintf(output, "%d ", number);
    }

    fclose(input);
    fclose(output);
    return EXIT_SUCCESS;
}
