#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "definitions.h"
#include "read.h"
#include "operations.h"
#include "check_args.h"
#include "print.h"

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
        rc = key(pb_src, pe_src, &dest_pb, &dest_pe);
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
    }
    else
    {
        if ((rc = cpy_arr(pb_src, pe_src, &dest_pb, &dest_pe)))
        {
            free(pb_src);
            free(dest_pb);
            return rc;
        }
    }
    free(pb_src);
    free(dest_pb); 
}
