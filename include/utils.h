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

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

/* ------------------------TYPES------------------------ */
#define countof(a) (size)(sizeof(a) / sizeof(*(a)))
#define lengthof(s) (countof(s) - 1)

typedef uint8_t u8;
typedef int32_t b32;
typedef int32_t i32;
typedef uint32_t u32;
typedef uint64_t u64;
typedef float f32;
typedef double f64;
typedef uintptr_t uptr;
typedef char byte;
typedef ptrdiff_t size;
typedef size_t usize;

/* ------------------------ERROR HANDLING------------------------ */
#define ERR_OUT_OF_MEMORY "Out of memory (allocation failed)\n"
#define ERR_OBJECT_INITIALIZATION_FAILED "Failed to initialze object\n"
#define ERR_INVALID_SIZE "Invalid size of bytes provided (bytes > buffer size)\n"
#define ERR_STR_CMP_FAILED "Strings provided are unequal\n"

#define return_value_if(cond, value, ...) \
  do {                                    \
    if ((cond)) {                         \
      fputs(__func__, stderr);            \
      fputs(" : ", stderr);               \
      fprintf(stderr, __VA_ARGS__);       \
      return value;                       \
    }                                     \
  } while (0)

#define goto_handler_if(cond, handler, ...) \
  do {                                      \
    if ((cond)) {                           \
      fputs(__func__, stderr);              \
      fputs(" : " #handler " : ", stderr);  \
      fprintf(stderr, __VA_ARGS__);         \
      goto handler;                         \
    }                                       \
  } while (0)

#define abort_if(cond, ...)         \
  do {                              \
    if ((cond)) {                   \
      fputs(__func__, stderr);      \
      fputs(" : ", stderr);         \
      fprintf(stderr, __VA_ARGS__); \
      abort();                      \
    }                               \
  } while (0)
