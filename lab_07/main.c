#include <stdio.h>
#include <string.h>

#include "definitions.h"
#include "read.h"
#include "operations.h"
#include "check_args.h"
#include "print.h"

int main(int argc, const char *argv[])
{
    bool need_filter = false;
    if (check(argc, argv, &need_filter))
        return 1;
    char filename_in[MAX_LEN_FILENAME + 1] = { 0 };
    char filename_out[MAX_LEN_FILENAME + 1] = { 0 };

    strncpy(filename_in, argv[1], MAX_LEN_FILENAME + 1);
    strncpy(filename_out, argv[2], MAX_LEN_FILENAME + 1);

    size_t quantity = 0;
    if (read_quantity(filename_in, &quantity))
        return 1;
    

    int *pb_src, *pe_src;
    if (allocate_memory(&pb_src, quantity))
        return 1;


    pe_src = pb_src + quantity - 1;
    fill_array(filename_in, pb_src, pe_src);
    int *dest_pe, *dest_pb;


    if (need_filter)
    {
        if (key(pb_src, pe_src, &dest_pb, &dest_pe))
            return 1;
    }
    else
    {
        if (cpy_arr(pb_src, pe_src, &dest_pb, &dest_pe))
            return 2;
    }

    // while (dest_pb <= dest_pe)
    // {
    //     printf("%d ", *dest_pb);
    //     dest_pb++;
    // }
    
    // printf("here\n");
    // size_t new_len = dest_pe - dest_pb + 1;
    // my_sort(dest_pb, new_len, sizeof(int), compare_ints);
    // printf("here\n");
    // if (print_to_file(dest_pb, dest_pe, filename_out))
    //     return 2;
    // printf("here\n");

    free(pb_src);
    free(dest_pb);
}
