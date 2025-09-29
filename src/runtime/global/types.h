#include <stdint.h>
#include <stdlib.h>

#ifndef GLOBAL_TYPES_H
#define GLOBAL_TYPES_H

#define G_TYPE_INT 1;
#define G_TYPE_CHAR 2;
#define G_TYPE_FLOAT 3;
#define G_TYPE_PTR 4;

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

#endif // GLOBAL_TYPES_H
