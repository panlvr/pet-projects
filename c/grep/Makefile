TARGET = s21_grep
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11

all: $(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) s21_grep.c -o $(TARGET)

clean:
	rm -f $(TARGET)

rebuild: clean all