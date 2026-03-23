CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = volume
SRC = volume.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)
    
rebuild: clean all

.PHONY: all run clean rebuild