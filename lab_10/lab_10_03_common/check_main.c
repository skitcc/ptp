#include "check_create_destroy.h"
#include "check_add.h"
#include "check_get.h"
#include "check_remove.h"

#include <stdlib.h>

int main(void)
{
    int number_failed;
    SRunner* sr;

    // Создаем раннер с первым набором тестов
    sr = srunner_create(create_destroy_suite());

    // Добавляем остальные тестовые наборы
    srunner_add_suite(sr, add_suite());
    srunner_add_suite(sr, get_suite());
    srunner_add_suite(sr, remove_suite());

    // Запуск всех тестов
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
