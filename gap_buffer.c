#include "include/gap_buffer.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/utils.h"

bool GapBuffer_new(GapBuffer **buffer, size req_size) {
  *buffer = malloc(sizeof(GapBuffer) + req_size * sizeof(u8));

  GOTO_HANDLER_IF(*buffer == NULL, INIT_FAILED, ERR_OUT_OF_MEMORY);

  (*buffer)->gap_start = 0;
  (*buffer)->buffer_size = req_size;
  (*buffer)->gap_len = req_size;
  (*buffer)->old_gap_len = req_size;

  return true;

INIT_FAILED:
  free(*buffer);
  return false;
}

void GapBuffer_free(GapBuffer *buffer) { if (buffer) free(buffer); }

bool GapBuffer_insert(GapBuffer **buffer, const s8 string, size position) {
  RETURN_VALUE_IF(expandGap(buffer, string.len) == false, false,
                  ERR_OUT_OF_MEMORY);

  shiftGapToPosition(*buffer, position);
  memcpy((*buffer)->data + (*buffer)->gap_start, string.data, string.len);

  (*buffer)->gap_start += string.len;
  (*buffer)->gap_len -= string.len;

  printChar(*buffer);

  return true;
}

static bool expandGap(GapBuffer **buffer, size str_len) {
  const GapBuffer *orig_buffer = *buffer;

  if (str_len <= orig_buffer->gap_len) {
    (*buffer)->old_gap_len = (*buffer)->gap_len;
    return true;
  }

  const usize req_size =
      (orig_buffer->buffer_size - orig_buffer->gap_len) + (2 * str_len);
  GapBuffer *new_buffer =
      realloc(*buffer, sizeof(GapBuffer) + req_size * sizeof(u8));

  GOTO_HANDLER_IF(new_buffer == NULL, REALLOC_FAILED, ERR_OUT_OF_MEMORY);

  new_buffer->buffer_size = req_size;
  new_buffer->old_gap_len = new_buffer->gap_len;
  new_buffer->gap_len = 2 * str_len;

  *buffer = new_buffer;
  return true;

REALLOC_FAILED:
  free(*buffer);
  return false;
}

static void shiftGapToPosition(GapBuffer *buffer, size position) {
  if (position == buffer->gap_start) {
    return;
  } else if (position < buffer->gap_start) {
    const size num = (buffer->gap_start - position) * sizeof(u8);

    memmove(buffer->data + buffer->gap_start + buffer->gap_len - num,
            buffer->data + position, num);
  } else {
    const size num = (position - buffer->gap_start) * sizeof(u8);

    memmove(buffer->data + buffer->gap_start,
            buffer->data + buffer->gap_start + buffer->old_gap_len, num);
  }

  buffer->gap_start = position;
}

static void printChar(GapBuffer *buffer) {
  for (size i = 0; i < buffer->gap_start; i++) {
    printf("%c", buffer->data[i]);
  }

  for (size i = 0; i < buffer->gap_len; i++) {
    printf("_");
  }

  for (size i = buffer->gap_start + buffer->gap_len; i < buffer->buffer_size; i++) {
    printf("%c", buffer->data[i]);
  }

  printf("\n");
}

int main(void) {
  const s8 str = s8("hello");
  const s8 str2 = s8("world");
  const s8 str3 = s8(" my ");
  const s8 str4 = s8(" signing off");

  GapBuffer *buff = {0};

  ABORT_IF(GapBuffer_new(&buff, 1) == false, ERR_OUT_OF_MEMORY);

  ABORT_IF(GapBuffer_insert(&buff, str, 0) == false, ERR_OUT_OF_MEMORY);
  ABORT_IF(GapBuffer_insert(&buff, str2, str.len) == false, ERR_OUT_OF_MEMORY);
  ABORT_IF(GapBuffer_insert(&buff, str3, str.len) == false, ERR_OUT_OF_MEMORY);
  ABORT_IF(
      GapBuffer_insert(&buff, str4, str.len + str2.len + str3.len) == false,
      ERR_OUT_OF_MEMORY);

  GapBuffer_free(buff);
  return 0;
}
