/* This file is part of gapbuffer.

gapbuffer is free software: you can redistribute it and/or modify it under the terms of the GNU
General Public License as published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

gapbuffer is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
Public License for more details.

You should have received a copy of the GNU General Public License along with gapbuffer. If not, see
<https://www.gnu.org/licenses/>. */

#include "../include/s8.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "../include/utils.h"

s8 s8cat(const s8 str1, const s8 str2) {
  s8 result = {0};
  result.len = str1.len + str2.len;
  result.data = malloc(result.len * sizeof(u8));

  return_value_if(result.data == NULL, result, ERR_OUT_OF_MEMORY);

  memcpy(result.data, str1.data, str1.len);
  memcpy(result.data + str1.len, str2.data, str2.len);

  return result;
}

bool s8cmp(const s8 str1, const s8 str2) {
  if (str1.len != str2.len) {
    return false;
  }

  for (size i = 0; i < str1.len; i++) {
    if (str1.data[i] != str2.data[i]) {
      return false;
    }
  }

  return true;
}

void s8free(s8 str) {
  if (str.data) free(str.data);
}
