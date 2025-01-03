# Директории
SRC_DIR := ./src/
OUT_DIR := ./out/
INC_DIR := ./inc/
LIB_DIR := ./lib/

# Создание директорий для объектных файлов
$(shell mkdir -p $(OUT_DIR))
$(shell mkdir -p $(LIB_DIR))

# Компилятор и флаги
CC := gcc
CFLAGS := -std=c99 -Wall -Werror -Wextra -Wfloat-equal -Wfloat-conversion -I$(INC_DIR)
LDFLAGS := -L$(LIB_DIR) -Wl,-rpath,$(PWD)/$(LIB_DIR)
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
SHARED_LIB := $(LIB_DIR)libdn1.so

# Цели
all: app.exe

# Сборка основного приложения с динамической библиотекой
app.exe: $(APP_OBJ) $(MAIN_OBJ) $(SHARED_LIB)
	$(CC) $(APP_OBJ) $(MAIN_OBJ) -o $@ $(LDFLAGS) -ldn1

# Сборка динамической библиотеки
$(SHARED_LIB): $(LIB_OBJ)
	$(CC) $(SHARED_FLAG) -o $@ $^

# Компиляция объектных файлов для библиотеки
$(OUT_DIR)%.o: $(SRC_DIR)%.c | $(OUT_DIR)
	$(CC) $(CFLAGS) -fPIC -c -o $@ $<

# Компиляция объектных файлов основного приложения
$(APP_OBJ): $(OUT_DIR)%.o: $(SRC_DIR)%.c | $(OUT_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(MAIN_OBJ): $(MAIN_SRC_FULL) | $(OUT_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Чистка
.PHONY: clean
clean:
	rm -rf $(OUT_DIR)/*.o $(LIB_DIR)/*.so app.exe
