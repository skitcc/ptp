# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -Werror -g
LDFLAGS = -lcheck -lm -lrt -lpthread

# Общие директории и цели
COMMON_DIR = ../lab_10_03_common
TARGET = app.exe

# Исходники
SRCS = associative_array_impl_2.c check_main.c check_create_destroy.c check_add.c check_get.c check_remove.c
OBJS = $(SRCS:.c=.o)

# Компиляция основного приложения
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Очистка временных файлов
clean:
	rm -f *.o $(TARGET)
