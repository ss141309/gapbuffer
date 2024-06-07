#ifndef GAPBUFFER_H
#define GAPBUFFER_H

#include <stdlib.h>
#include <unistd.h>

typedef struct {
  size_t size;
  size_t gap_start;
  size_t gap_len;

  unsigned char data[];
} GapBuffer;

GapBuffer *GapBuffer_new(size_t size);
void GapBuffer_free(GapBuffer *buffer);
void GapBuffer_insert(GapBuffer **buffer, const char *string, size_t len,
                      size_t position);

static void expandGap(GapBuffer **buffer, size_t size);
static void shiftGapToPosition(GapBuffer *buffer, size_t position);

#endif
