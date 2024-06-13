/* This file is part of gapbuffer.

gapbuffer is free software: you can redistribute it and/or modify it under the terms of the GNU
General Public License as published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

gapbuffer is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
Public License for more details.

You should have received a copy of the GNU General Public License along with gapbuffer. If not, see
<https://www.gnu.org/licenses/>. */

#include <assert.h>
#include <stdio.h>

#include "../include/gap_buffer.h"

int main(void) {
  const s8 str1 = s8("hello");
  const s8 str2 = s8("world");
  const s8 str3 = s8(" my ");
  const s8 str4 = s8(", goodbye!");

  GapBuffer *buffer = {0};
  abort_if(GapBuffer_new(&buffer, 1) == false, ERR_OBJECT_INITIALIZATION_FAILED);

  GapBuffer_insert(&buffer, str1, 0);
  s8 buffer_data = GapBuffer_getBufferData(buffer);
  assert(s8cmp(buffer_data, s8("hello")));
  free(buffer_data.data);

  GapBuffer_insert(&buffer, str2, str1.len);
  buffer_data = GapBuffer_getBufferData(buffer);
  assert(s8cmp(buffer_data, s8("helloworld")));
  free(buffer_data.data);

  GapBuffer_insert(&buffer, str3, str1.len);
  buffer_data = GapBuffer_getBufferData(buffer);
  assert(s8cmp(buffer_data, s8("hello my world")));
  free(buffer_data.data);

  GapBuffer_insert(&buffer, str4, str1.len + str2.len + str3.len);
  buffer_data = GapBuffer_getBufferData(buffer);
  assert(s8cmp(buffer_data, s8("hello my world, goodbye!")));
  free(buffer_data.data);

  GapBuffer_delete(buffer, str1.len, 3);
  buffer_data = GapBuffer_getBufferData(buffer);
  assert(s8cmp(buffer_data, s8("hello world, goodbye!")));
  free(buffer_data.data);

  GapBuffer_replace(&buffer, s8("a"), 1);
  buffer_data = GapBuffer_getBufferData(buffer);
  assert(s8cmp(buffer_data, s8("hallo world, goodbye!")));
  free(buffer_data.data);

  GapBuffer_free(buffer);
  return 0;
}
