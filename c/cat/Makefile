TARGET = s21_cat
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11

all: $(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) s21_cat.c -o $(TARGET)

clean:
	rm -f $(TARGET)

rebuild: clean all