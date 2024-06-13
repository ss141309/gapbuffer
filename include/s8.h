#pragma once
#include <stdbool.h>

#include "utils.h"

#define s8(s) \
  (s8) { (u8 *)s, lengthof(s) }

typedef struct {
  u8 *data;
  size len;
} s8;

s8 s8cat(const s8 str1, const s8 str2);
bool s8cmp(const s8 str1, const s8 str2);
