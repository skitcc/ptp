CC = gcc
CFLAGS = -Wall -Werror -g
LDFLAGS = -lcheck -lm

COMMON_DIR = ../lab_10_03_common
TARGET = unit_tests.exe

SRCS = associative_array_impl_2.c check_main.c check_create_destroy.c check_clear.c check_remove.c check_each.c check_insert.c check_min_max.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)
