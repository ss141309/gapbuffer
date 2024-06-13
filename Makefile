.POSIX:
.SUFFIXES:
CC = cc
CFLAGS = -std=c23 -Wall -Wextra -Wpedantic -fsanitize=address,undefined -g
LDFLAGS = -fsanitize=address,undefined

all: gapbuffer
gapbuffer: src/test.o src/gap_buffer.o src/s8.o
	$(CC) $(LDFLAGS) -o gapbuffer test.o gap_buffer.o s8.o
src/test.o: src/test.c
src/gap_buffer.o: src/gap_buffer.c include/gap_buffer.h
src/s8.o: src/s8.c include/s8.h
clean:
	rm -f gapbuffer test.o gap_buffer.o s8.o

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $<
