# Директории
SRC_DIR := ./src/
OUT_DIR := ./out/
INC_DIR := ./inc/
UNIT_TEST_DIR := ./unit/

# Создание директории для объектных файлов
$(shell mkdir -p $(OUT_DIR))

# Компилятор и флаги
CC := gcc
CFLAGS := -std=c99 -Wall -Werror -pedantic -Wextra -Wfloat-equal -Wfloat-conversion -I$(INC_DIR)
LINKFLAGS := -lcheck -lm

# Исходные файлы и объектные файлы
SRC := $(wildcard $(SRC_DIR)*.c)
APP_OBJ := $(patsubst $(SRC_DIR)%.c, $(OUT_DIR)%.o, $(filter-out $(SRC_DIR)main.c, $(SRC)))

# Файлы с тестами и объектные файлы тестов
TEST_SRC := $(wildcard $(UNIT_TEST_DIR)*.c)
TEST_OBJ := $(patsubst $(UNIT_TEST_DIR)%.c, $(OUT_DIR)%.o, $(TEST_SRC))

# Файл с main() для тестов
CHECK_MAIN := $(OUT_DIR)check_main.o
SOURSE_MAIN := $(OUT_DIR)main.o

# Цели
all: app.exe unit_tests.exe 

# Сборка основного приложения
app.exe: $(APP_OBJ) $(SOURSE_MAIN)
	$(CC) $(APP_OBJ) $(SOURSE_MAIN) -o $@ 

# Сборка тестов
unit_tests.exe: $(TEST_OBJ) $(APP_OBJ) $(CHECK_MAIN)
	$(CC) $(TEST_OBJ) $(APP_OBJ) $(LINKFLAGS) $(COVERAGE_FLAGS) -o $@ 

# Компиляция основных файлов с флагами покрытия
$(OUT_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) -c -o $@ $<

# Компиляция тестов с флагами покрытия
$(OUT_DIR)%.o: $(UNIT_TEST_DIR)%.c
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) -c -o $@ $<

# Компиляция check_main.c (тестовый main) с покрытием
$(CHECK_MAIN): $(UNIT_TEST_DIR)check_main.c
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) -c -o $@ $<

# Компиляция main.c для основного приложения
$(SOURSE_MAIN): $(SRC_DIR)main.c
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) -c -o $@ $<
	
.PHONY: clean unit func coverage

unit : unit_tests.exe
	./unit_tests.exe

func : app.exe
	./func_tests/scripts/func_tests.sh -v

# Чистка
clean:
	rm -rf $(OUT_DIR)/*.o app.exe unit_tests.exe $(OUT_DIR)/*.gcda $(OUT_DIR)/*.gcno $(OUT_DIR)/*.gcov
