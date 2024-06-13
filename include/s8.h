/* This file is part of gapbuffer.

gapbuffer is free software: you can redistribute it and/or modify it under the terms of the GNU
General Public License as published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

gapbuffer is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
Public License for more details.

You should have received a copy of the GNU General Public License along with gapbuffer. If not, see
<https://www.gnu.org/licenses/>. */

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
