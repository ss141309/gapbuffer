CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -fsanitize=address,undefined -g
SRC = GapBuffer.c
DEPS = GapBuffer.h
TARGET = GapBuffer

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LIBS)
