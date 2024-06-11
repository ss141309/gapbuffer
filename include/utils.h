#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

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

#define s8(s) \
  (s8) { (u8 *)s, lengthof(s) }

typedef struct {
  u8 *data;
  size len;
} s8;

#define ERR_OUT_OF_MEMORY "Out of memory (allocation failed)\n"

#define RETURN_VALUE_IF(cond, value, ...) \
  do {                                    \
    if ((cond)) {                         \
      fputs(__func__, stderr);            \
      fputs(" : ", stderr);               \
      fprintf(stderr, __VA_ARGS__);       \
      return value;                       \
    }                                     \
  } while (0)

#define GOTO_HANDLER_IF(cond, handler, ...) \
  do {                                      \
    if ((cond)) {                           \
      fputs(__func__, stderr);              \
      fputs(" : " #handler " : ", stderr);  \
      fprintf(stderr, __VA_ARGS__);         \
      goto handler;                         \
    }                                       \
  } while (0)

#define ABORT_IF(cond, ...)         \
  do {                              \
    if ((cond)) {                   \
      fputs(__func__, stderr);      \
      fputs(" : ", stderr);         \
      fprintf(stderr, __VA_ARGS__); \
      abort();                      \
    }                               \
  } while (0)
