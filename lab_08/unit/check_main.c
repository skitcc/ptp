#include <check.h>
#include "check_operations.h"
#include "check_det.h"

int main(void)
{
    int number_failed;
    SRunner *sr = srunner_create(matrix_operations_suite());

    srunner_add_suite(sr, matrix_suite());


    srunner_run_all(sr, CK_NORMAL); 
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;

}