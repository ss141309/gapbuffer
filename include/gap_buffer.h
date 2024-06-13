#pragma once

#include <stdbool.h>

#include "s8.h"
#include "utils.h"

typedef struct {
  size buffer_size;
  usize gap_start;
  size gap_len;
  size old_gap_len;

  u8 data[];
} GapBuffer;

bool GapBuffer_new(GapBuffer **buffer, size req_size);
void GapBuffer_free(GapBuffer *buffer);
bool GapBuffer_insert(GapBuffer **buffer, const s8 string, usize position);
bool GapBuffer_delete(GapBuffer *buffer, usize position, size bytes);
bool GapBuffer_replace(GapBuffer **buffer, const s8 string, usize position);
s8 GapBuffer_getBufferData(GapBuffer *buffer);
