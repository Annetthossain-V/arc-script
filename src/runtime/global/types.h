#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifndef GLOBAL_TYPES_H
#define GLOBAL_TYPES_H

#define TYPE_INT 1;
#define TYPE_CHAR 2;
#define TYPE_FLOAT 3;
#define TYPE_PTR 4;

#define SCOPE_SECTION_DATA 1
#define SCOPE_SECTION_RODATA 2
#define SCOPE_SECTION_TEXT 3
#define SCOPE_TEXT_FUNC 4
#define SCOPE_GLOBAL 5

struct _RegisterX32 {
  void* data;
  char type;
  size_t len;
  size_t cap;
};
#define register struct _RegisterX32s

struct _table2 {
  void* id1;
  void* id2;
  size_t len;
};
#define table2_t struct _table2

static inline void arr_shift_left(void** arr, size_t len, size_t n) {
  if (n >= len) return;
  memmove(&arr[n], &arr[n + 1], (len - n - 1) * sizeof(void*));
}

#endif // GLOBAL_TYPES_H
