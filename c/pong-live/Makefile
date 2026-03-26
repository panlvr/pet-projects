CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -lncurses
TARGET = pong-live
SRC = pong_live.c

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)