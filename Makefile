CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -fsanitize=address,undefined -g
SRC = gap_buffer.c
DEPS = include/gap_buffer.h
TARGET = gapbuffer

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LIBS)
