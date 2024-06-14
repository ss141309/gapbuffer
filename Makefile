# This file is part of gapbuffer.

# gapbuffer is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

# gapbuffer is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

# You should have received a copy of the GNU General Public License along with gapbuffer. If not, see <https://www.gnu.org/licenses/>.

.POSIX:
.SUFFIXES:
CC = cc
CFLAGS = -Wall -Wextra -Wpedantic -fsanitize=address,undefined -g
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
