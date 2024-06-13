/* This file is part of gapbuffer.

gapbuffer is free software: you can redistribute it and/or modify it under the terms of the GNU
General Public License as published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

gapbuffer is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
Public License for more details.

You should have received a copy of the GNU General Public License along with gapbuffer. If not, see
<https://www.gnu.org/licenses/>. */

#include "../include/gap_buffer.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/s8.h"
#include "../include/utils.h"

static s8 getDataBeforeGap(GapBuffer *buffer);
static s8 getDataAfterGap(GapBuffer *buffer);
static bool expandGap(GapBuffer **buffer, size str_len);
static void shiftGapToPosition(GapBuffer *buffer, usize position);

bool GapBuffer_new(GapBuffer **buffer, size req_size) {
  *buffer = malloc(sizeof(GapBuffer) + req_size * sizeof(u8));

  return_value_if(*buffer == NULL, false, ERR_OUT_OF_MEMORY);

  (*buffer)->gap_start = 0;
  (*buffer)->buffer_size = req_size;
  (*buffer)->gap_len = req_size;
  (*buffer)->old_gap_len = req_size;

  return true;
}

void GapBuffer_free(GapBuffer *buffer) {
  if (buffer) free(buffer);
}

bool GapBuffer_insert(GapBuffer **buffer, const s8 string, usize position) {
  return_value_if(expandGap(buffer, string.len) == false, false, ERR_OUT_OF_MEMORY);

  shiftGapToPosition(*buffer, position);
  memcpy((*buffer)->data + (*buffer)->gap_start, string.data, string.len);

  (*buffer)->gap_start += string.len;
  (*buffer)->gap_len -= string.len;

  return true;
}

static bool expandGap(GapBuffer **buffer, size str_len) {
  const GapBuffer *orig_buffer = *buffer;

  if (str_len <= orig_buffer->gap_len) {
    (*buffer)->old_gap_len = (*buffer)->gap_len;
    return true;
  }

  const usize req_size = (orig_buffer->buffer_size - orig_buffer->gap_len) + (2 * str_len);
  GapBuffer *new_buffer = realloc(*buffer, sizeof(GapBuffer) + req_size * sizeof(u8));

  if (new_buffer) {
    new_buffer->buffer_size = req_size;
    new_buffer->old_gap_len = new_buffer->gap_len;
    new_buffer->gap_len = 2 * str_len;

    *buffer = new_buffer;
    return true;
  } else {
    return_value_if(new_buffer == NULL, false, ERR_OUT_OF_MEMORY);
    return false; // To suppress -Wreturn-type warning
  }
}

static void shiftGapToPosition(GapBuffer *buffer, usize position) {
  if (position == buffer->gap_start) {
    return;
  } else if (position < buffer->gap_start) {
    const size num = (buffer->gap_start - position) * sizeof(u8);

    memmove(buffer->data + buffer->gap_start + buffer->gap_len - num, buffer->data + position, num);
  } else {
    const size num = (position - buffer->gap_start) * sizeof(u8);

    memmove(buffer->data + buffer->gap_start,
            buffer->data + buffer->gap_start + buffer->old_gap_len, num);
  }

  buffer->gap_start = position;
}

bool GapBuffer_delete(GapBuffer *buffer, usize position, size bytes) {
  const size total_bytes = (buffer->buffer_size - buffer->gap_len) - position;
  return_value_if(total_bytes < bytes, false, ERR_INVALID_SIZE);

  shiftGapToPosition(buffer, position);
  buffer->gap_len += bytes;

  return true;
}

bool GapBuffer_replace(GapBuffer **buffer, const s8 string, usize position) {
  return_value_if(GapBuffer_delete(*buffer, position, string.len) == false, false,
                  ERR_INVALID_SIZE);
  return_value_if(GapBuffer_insert(buffer, string, position) == false, false, ERR_OUT_OF_MEMORY);
  return true;
}

s8 GapBuffer_getBufferData(GapBuffer *buffer) {
  const s8 before_data = getDataBeforeGap(buffer);
  const s8 after_data = getDataAfterGap(buffer);

  s8 concat_str = s8cat(before_data, after_data);
  return_value_if(concat_str.data == NULL, concat_str, ERR_OBJECT_INITIALIZATION_FAILED);

  return concat_str;
}

static s8 getDataBeforeGap(GapBuffer *buffer) {
  const s8 before_str = {.data = buffer->data, .len = buffer->gap_start};

  return before_str;
}

static s8 getDataAfterGap(GapBuffer *buffer) {
  const usize first_byte_after_gap = buffer->gap_start + buffer->gap_len;

  const s8 after_str = {.data = buffer->data + first_byte_after_gap,
                        .len = buffer->buffer_size - first_byte_after_gap};

  return after_str;
}
