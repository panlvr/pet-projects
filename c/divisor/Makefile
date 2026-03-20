CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
TARGET = divisor
SRC = divisor.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

rebuild: clean all

debug: CFLAGS += -g
debug: clean all

.PHONY: all run clean rebuild debug