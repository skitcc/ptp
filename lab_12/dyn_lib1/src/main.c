#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <dlfcn.h>

#include "definitions.h"
#include "check_args.h"

int main(int argc, const char *argv[])
{
    bool need_filter = false;
    int rc = 0;
    if ((rc = check(argc, argv, &need_filter)) != 0)
        return rc;
    
    char filename_in[MAX_LEN_FILENAME + 1] = { 0 };
    char filename_out[MAX_LEN_FILENAME + 1] = { 0 };
    strncpy(filename_in, argv[1], MAX_LEN_FILENAME + 1);
    strncpy(filename_out, argv[2], MAX_LEN_FILENAME + 1);

    void *handle = dlopen("libdn1.so", RTLD_NOW);
    if (!handle)
    {
        dlclose(handle);
        return 1;
    }
    short (*read_quantity)(char *, size_t *) = (short (*)(char *, size_t *))dlsym(handle, "read_quantity");    
    if (!read_quantity)
    {
        dlclose(handle);
        return 2;
    }

    void (*fill_array)(char *, int *, int *) = dlsym(handle, "fill_array");
    if (!fill_array)
    {
        dlclose(handle);
        return 2;
    }

    int (*key)(const int *, const int *, int *) = dlsym(handle, "key");
    if (!key)
    {
        dlclose(handle);
        return 2;
    }

    int (*cpy_arr)(const int *, const int *, int *) = dlsym(handle, "cpy_arr");
    if (!cpy_arr)
    {
        dlclose(handle);
        return 2;
    }

    int (*print_to_file)(const int *, const int *, char *) = dlsym(handle, "print_to_file");
    if (!print_to_file)
    {
        dlclose(handle);
        return 2;
    }

    void (*mysort)(void *, size_t, size_t, int (*)(const void *, const void *)) = dlsym(handle, "mysort");
    
    if (!mysort)
    {
        printf("11111\n");
        dlclose(handle);
        return 2;
    }
    
    int (*compare_ints)(const void *, const void *) = dlsym(handle, "compare_ints");
    
    if (!compare_ints)
    {
        dlclose(handle);
        return 2;
    }
    size_t quantity = 0;
    if ((rc = read_quantity(filename_in, &quantity)))
    {
        return rc;
    }
    int *pb_src, *pe_src;

    pb_src = malloc(quantity * sizeof(int));
    if (pb_src == NULL)
        return ERR_ALLOC_MEM;

    pe_src = pb_src + quantity; 

    fill_array(filename_in, pb_src, pe_src);

    int *dest_pb = NULL, *dest_pe = NULL;

    if (need_filter)
    {
        const int *start_src = pb_src;
        int counter = 0;
        int sum = 0;
        while (start_src < pe_src)
        {
            sum += *start_src;  
            start_src++;
        }
        int temp_sum = sum;
        start_src = pb_src;
        while (start_src < pe_src - 1)
        {
            temp_sum -= *start_src;
            if (*start_src > temp_sum)
                counter++;
            
            start_src++;
        }
        dest_pb = malloc(counter * sizeof(int));
        if (!dest_pb)
        {
            free(pb_src);
            return 1;
        }

        if (counter == 0)
            return ERR_EMPTY_FILE_AFTER_FILTER;

        dest_pe = dest_pb + counter;
        printf("counter value : %d\n", counter);
        rc = key(pb_src, pe_src, dest_pb);
        if (rc != ERR_EMPTY_FILE_AFTER_FILTER && rc)
        {
            free(pb_src);
            free(dest_pb);
            return rc;
        }
        else if (rc == ERR_EMPTY_FILE_AFTER_FILTER)
        {
            free(pb_src);
            return rc;
        }
        print_to_file(dest_pb, dest_pe, filename_out);
    }
    else
    {
        // printf("here!\n");
        size_t n = pe_src - pb_src;
        dest_pb = malloc(n * sizeof(int));
        if (dest_pb == NULL)
            return ERR_ALLOC_MEM;
        dest_pe = dest_pb + n;

        if ((rc = cpy_arr(pb_src, pe_src, dest_pb)))
        {
            free(pb_src);
            free(dest_pb);
            return rc;
        }
        print_to_file(dest_pb, dest_pe, filename_out);

    }
    size_t new_len = dest_pe - dest_pb;
    mysort(dest_pb, new_len, sizeof(int), compare_ints);
    if ((rc = print_to_file(dest_pb, dest_pe, filename_out)))
    {
        free(pb_src);
        free(dest_pb);
        return rc;
    }
    free(pb_src);
    free(dest_pb); 
    dlclose(handle);
}
