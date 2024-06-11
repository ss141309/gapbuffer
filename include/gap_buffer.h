#pragma once

#include <stdbool.h>

#include "utils.h"

typedef struct {
  size buffer_size;
  size gap_start;
  size gap_len;
  size old_gap_len;

  u8 data[];
} GapBuffer;

bool GapBuffer_new(GapBuffer **buffer, size req_size);
void GapBuffer_free(GapBuffer *buffer);
bool GapBuffer_insert(GapBuffer **buffer, const s8 string, size position);

static void printChar(GapBuffer *buffer);
static bool expandGap(GapBuffer **buffer, size str_len);
static void shiftGapToPosition(GapBuffer *buffer, size position);
