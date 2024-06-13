CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -fsanitize=address,undefined -g -std=c23
SRC = main.c gap_buffer.c s8.c
TARGET = gapbuffer

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LIBS)
