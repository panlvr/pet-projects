CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LIBS = -lcs50
TARGET = substitution
SRC = substitution.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LIBS)

run: $(TARGET)
	./$(TARGET) $(KEY)

clean:
	rm -f $(TARGET)

rebuild: clean all

.PHONY: all run clean rebuild