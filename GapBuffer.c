#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "GapBuffer.h"

GapBuffer *GapBuffer_new(size_t size) {
  GapBuffer *buffer = malloc(sizeof(GapBuffer) + size * sizeof(unsigned char));

  buffer->size = size;
  buffer->gap_start = 0;
  buffer->gap_len = size;

  return buffer;
}

void GapBuffer_free(GapBuffer *buffer) { free(buffer); }

void GapBuffer_insert(GapBuffer **buffer, const char *string, size_t len,
                      size_t position) {
  expandGap(buffer, len);
  shiftGapToPosition(*buffer, position);
  memcpy((*buffer)->data + (*buffer)->gap_start, string, len);
  
  (*buffer)->gap_start += len;
  (*buffer)->gap_len -= len;
}

static void expandGap(GapBuffer **buffer, size_t size) {
  const GapBuffer *orig_buffer = *buffer;
  
  if (size <= (orig_buffer)->gap_len) {
    return;
  }

  const size_t req_size =
      (orig_buffer->size - orig_buffer->gap_len) + (2 * size);
  GapBuffer *new_buffer =
      realloc(*buffer, sizeof(GapBuffer) + req_size * sizeof(unsigned char));

  if (new_buffer == NULL) {
    return;
  }

  new_buffer->size = req_size;
  new_buffer->gap_len = 2*size;

  //printf("new_gap_len: %lu\tnew_buff_size: %lu\n", new_buffer->gap_len, new_buffer->size);

  *buffer = new_buffer;
}

static void printChar(GapBuffer *buffer) {
  for (unsigned long i = 0; i < buffer->gap_start; i++) {
    printf("%c", buffer->data[i]);
  }
  for (unsigned long i = buffer->gap_start + buffer->gap_len; i < buffer->size; i++) {
    printf("%c", buffer->data[i]);
  }
  printf("\n");
}

static void shiftGapToPosition(GapBuffer *buffer, size_t position) {
  if (position == buffer->gap_start) {
    return;
  } else if (position < buffer->gap_start) {
    memmove(buffer->data + buffer->gap_start + buffer->gap_len - position,
            buffer->data + buffer->gap_start - position, buffer->gap_start - position);
    buffer->gap_start = position;
  } else {
    memmove(buffer->data + buffer->gap_start,
            buffer->data + buffer->gap_start + buffer->gap_len,
            position - buffer->gap_start);

    buffer->gap_start = position;
  }
}

int main(void) {
  const char *str = "hello";
  const size_t len = strlen(str);

  const char *str2 = "world";
  const size_t len2 = strlen(str2);

  const char *str3 = " my ";
  const size_t len3 = strlen(str3);

  const char *str4 = " sign";
  const size_t len4 = strlen(str4);

  const char *str5 = " testttt";
  const size_t len5 = strlen(str5);

  GapBuffer *buff = GapBuffer_new(1);

  GapBuffer_insert(&buff, str, len, 0);
  GapBuffer_insert(&buff, str2, len2, len);
  GapBuffer_insert(&buff, str3, len3, len);
  GapBuffer_insert(&buff, str4, len4, len + len2 + len3);
  GapBuffer_insert(&buff, str5, len5, len + len2 + len3 + len4);

  printChar(buff);

  GapBuffer_free(buff);
  return 0;
}
