CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = pong
SRC = pong.c

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)
