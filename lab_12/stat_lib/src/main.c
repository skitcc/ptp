#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "definitions.h"
#include "read.h"
#include "operations.h"
#include "check_args.h"
#include "print.h"
#include "my_sort.h"

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

    int *dest_pb, *dest_pe;

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
}
