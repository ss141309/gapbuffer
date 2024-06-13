#include "include/s8.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "include/utils.h"

s8 s8cat(const s8 str1, const s8 str2) {
  s8 result = {0};
  result.len = str1.len + str2.len;
  result.data = malloc(result.len * sizeof(u8));

  goto_handler_if(result.data == NULL, CONCAT_FAILED, ERR_OUT_OF_MEMORY);

  memcpy(result.data, str1.data, str1.len);
  memcpy(result.data + str1.len, str2.data, str2.len);

  return result;

CONCAT_FAILED:
  free(result.data);
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
