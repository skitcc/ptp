# Директории
SRC_DIR := ./src/
OUT_DIR := ./out/
INC_DIR := ./inc/
LIB_DIR := $(shell realpath ./lib/)

# Создание директорий для объектных файлов
$(shell mkdir -p $(OUT_DIR))
$(shell mkdir -p $(LIB_DIR))

# Компилятор и флаги
CC := gcc
CFLAGS := -std=c99 -Wall -Werror -Wextra -Wfloat-equal -Wfloat-conversion -g3 -I$(INC_DIR)
LDFLAGS := -L$(LIB_DIR) -Wl,-rpath,$(PWD)
SHARED_FLAG := -shared

# Исходные файлы
LIB_SRC := read.c print.c operations.c my_sort.c
APP_SRC := $(filter-out $(LIB_SRC), $(filter-out main.c, $(notdir $(wildcard $(SRC_DIR)*.c))))
MAIN_SRC := main.c

# Полные пути к исходным файлам
LIB_SRC_FULL := $(addprefix $(SRC_DIR), $(LIB_SRC))
APP_SRC_FULL := $(addprefix $(SRC_DIR), $(APP_SRC))
MAIN_SRC_FULL := $(SRC_DIR)$(MAIN_SRC)

# Объектные файлы
LIB_OBJ := $(addprefix $(OUT_DIR), $(LIB_SRC:.c=.o))
APP_OBJ := $(addprefix $(OUT_DIR), $(APP_SRC:.c=.o))
MAIN_OBJ := $(OUT_DIR)$(MAIN_SRC:.c=.o)

# Динамическая библиотека
SHARED_LIB := $(LIB_DIR)libdyn.so

# Цели
all: $(SHARED_LIB) app.exe

# Сборка основного приложения с динамической загрузкой
app.exe: $(APP_OBJ) $(MAIN_OBJ) $(SHARED_LIB)
	$(CC) $(APP_OBJ) $(MAIN_OBJ) -o $@ $(LDFLAGS)

# Сборка динамической библиотеки
$(SHARED_LIB): $(LIB_OBJ)
	$(CC) $(SHARED_FLAG) -o $@ $^

# Компиляция объектных файлов для библиотеки
$(OUT_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -fPIC -c -o $@ $<

# Компиляция объектных файлов основного приложения
$(OUT_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Чистка
.PHONY: clean
clean:
	rm -rf $(OUT_DIR)/*.o $(LIB_DIR)/*.so app.exe
