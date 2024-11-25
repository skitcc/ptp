#include "check_create_destroy.h"
#include "check_clear.h"
#include "check_each.h"
#include "check_insert.h"
#include "check_min_max.h"
#include "check_remove.h"

#include <stdlib.h>

int main(void)
{
    int number_failed;
    SRunner* sr;

    sr = srunner_create(create_destroy_suite());

    srunner_add_suite(sr, clear_suite());
    srunner_add_suite(sr, each_suite());
    srunner_add_suite(sr, insert_suite());
    srunner_add_suite(sr, min_max_suite());
    srunner_add_suite(sr, remove_suite());

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
