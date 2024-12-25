#include <check.h>
#include <stdlib.h>
#include <stdio.h>

extern Suite *check_args_suite(void);
extern Suite *io_suite(void);
extern Suite *key_suite(void);

int main(void)
{
    int number_failed;
    SRunner *sr = srunner_create(check_args_suite());

    srunner_add_suite(sr, io_suite());
    srunner_add_suite(sr, key_suite());

    srunner_run_all(sr, CK_NORMAL); 
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
