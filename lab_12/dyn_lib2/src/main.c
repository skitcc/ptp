#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dlfcn.h>

#include "definitions.h"
#include "check_args.h"

int main(int argc, const char *argv[])
{
    bool need_filter = false;
    int rc = 0;

    // Проверка аргументов
    if ((rc = check(argc, argv, &need_filter)) != 0)
        return rc;

    char filename_in[MAX_LEN_FILENAME + 1] = {0};
    char filename_out[MAX_LEN_FILENAME + 1] = {0};
    strncpy(filename_in, argv[1], MAX_LEN_FILENAME + 1);
    strncpy(filename_out, argv[2], MAX_LEN_FILENAME + 1);

    size_t quantity = 0;
    int *pb_src = NULL, *pe_src = NULL;
    int *dest_pb = NULL, *dest_pe = NULL;

    // Загрузка динамической библиотеки
    void *handle = dlopen("./libdyn.so", RTLD_LAZY);
    if (!handle)
    {
        fprintf(stderr, "Ошибка загрузки библиотеки: %s\n", dlerror());
        return 1;
    }

    // Загрузка функций из библиотеки с явным приведением типов
    short (*read_quantity)(char *, size_t *) = (short (*)(char *, size_t *))dlsym(handle, "read_quantity");
    if (!read_quantity)
    {
        fprintf(stderr, "Ошибка загрузки функции read_quantity: %s\n", dlerror());
        dlclose(handle);
        return 2;
    }

    void (*fill_array)(char *, int *, int *) = (void (*)(char *, int *, int *))dlsym(handle, "fill_array");
    if (!fill_array)
    {
        fprintf(stderr, "Ошибка загрузки функции fill_array: %s\n", dlerror());
        dlclose(handle);
        return 2;
    }

    int (*key)(const int *, const int *, int **, int **) = (int (*)(const int *, const int *, int **, int **))dlsym(handle, "key");
    if (!key)
    {
        fprintf(stderr, "Ошибка загрузки функции key: %s\n", dlerror());
        dlclose(handle);
        return 2;
    }

    int (*cpy_arr)(const int *, const int *, int **, int **) = (int (*)(const int *, const int *, int **, int **))dlsym(handle, "cpy_arr");
    if (!cpy_arr)
    {
        fprintf(stderr, "Ошибка загрузки функции cpy_arr: %s\n", dlerror());
        dlclose(handle);
        return 2;
    }

    int (*print_to_file)(const int *, const int *, char *) = (int (*)(const int *, const int *, char *))dlsym(handle, "print_to_file");
    if (!print_to_file)
    {
        fprintf(stderr, "Ошибка загрузки функции print_to_file: %s\n", dlerror());
        dlclose(handle);
        return 2;
    }

    // Чтение количества элементов
    if ((rc = read_quantity(filename_in, &quantity)))
    {
        dlclose(handle);
        return rc;
    }

    pb_src = malloc(quantity * sizeof(int));
    if (!pb_src)
    {
        dlclose(handle);
        return ERR_ALLOC_MEM;
    }

    pe_src = pb_src + quantity;

    // Заполнение массива
    fill_array(filename_in, pb_src, pe_src);

    // Обработка массива
    if (need_filter)
    {
        rc = key(pb_src, pe_src, &dest_pb, &dest_pe);
        if (rc == ERR_EMPTY_FILE_AFTER_FILTER)
        {
            fprintf(stderr, "Ошибка: массив пуст после фильтрации.\n");
            free(pb_src);
            dlclose(handle);
            return rc;
        }
        else if (rc)
        {
            fprintf(stderr, "Ошибка при фильтрации массива.\n");
            free(pb_src);
            dlclose(handle);
            return rc;
        }
    }
    else
    {
        rc = cpy_arr(pb_src, pe_src, &dest_pb, &dest_pe);
        if (rc)
        {
            fprintf(stderr, "Ошибка копирования массива.\n");
            free(pb_src);
            dlclose(handle);
            return rc;
        }
    }

    // Запись результата в файл
    rc = print_to_file(dest_pb, dest_pe, filename_out);
    if (rc)
    {
        fprintf(stderr, "Ошибка записи массива в файл.\n");
        free(pb_src);
        free(dest_pb);
        dlclose(handle);
        return rc;
    }

    // Освобождение ресурсов
    free(pb_src);
    free(dest_pb);

    // Закрытие динамической библиотеки
    dlclose(handle);
    return 0;
}
