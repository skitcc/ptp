# Директории
SRC_DIR := ./src/
OUT_DIR := ./out/
INC_DIR := ./inc/
LIB_DIR := ./lib/
UNIT_TEST_DIR := ./unit/

# Создание директорий для объектных файлов
$(shell mkdir -p $(OUT_DIR))
$(shell mkdir -p $(LIB_DIR))

# Компилятор и флаги
CC := gcc
CFLAGS := -std=c99 -Wall -Werror -pedantic -Wextra -Wfloat-equal -Wfloat-conversion -I$(INC_DIR)
LINKFLAGS := -lcheck -lm

# Исходные файлы
LIB_SRC := read.c print.c operations.c
APP_SRC := $(filter-out $(LIB_SRC), $(filter-out main.c, $(notdir $(wildcard $(SRC_DIR)*.c))))
MAIN_SRC := main.c

# Полные пути к исходным файлам
LIB_SRC_FULL := $(addprefix $(SRC_DIR), $(LIB_SRC))
APP_SRC_FULL := $(addprefix $(SRC_DIR), $(APP_SRC))
MAIN_SRC_FULL := $(SRC_DIR)$(MAIN_SRC)

# Объектные файлы
LIB_OBJ := $(addprefix $(LIB_DIR), $(LIB_SRC:.c=.o))
APP_OBJ := $(addprefix $(OUT_DIR), $(APP_SRC:.c=.o))
MAIN_OBJ := $(OUT_DIR)$(MAIN_SRC:.c=.o)

# Цели
all: app.exe

# Сборка основного приложения со статической библиотекой
app.exe: $(APP_OBJ) $(MAIN_OBJ) libstat.a
	$(CC) $(APP_OBJ) $(MAIN_OBJ) libstat.a -o $@

# Сборка статической библиотеки
libstat.a: $(LIB_OBJ)
	ar cr $@ $^
	ranlib $@

# Компиляция объектных файлов для статической библиотеки
$(LIB_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Компиляция объектных файлов основного приложения
$(OUT_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Компиляция main.c для основного приложения
$(MAIN_OBJ): $(MAIN_SRC_FULL)
	$(CC) $(CFLAGS) -c -o $@ $<

# Чистка
.PHONY: clean
clean:
	rm -rf $(OUT_DIR)/*.o $(LIB_DIR)/*.o app.exe libstat.a
