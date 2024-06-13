#include "../include/gap_buffer.h"

#include <stdio.h>
#include <assert.h>

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
  buffer_data = GapBuffer_getBufferData(buffer);  assert(s8cmp(buffer_data, s8("hello my world")));
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
