#pragma once
#include "global/types.h"
#include <stdlib.h>

struct _Keys2 {
  void** k1;
  void** k2;
  char type[2];
  size_t cap;
  size_t len;
};
#define keys2 struct _Keys2

struct _RegisterX32 {
  void* data;
  char type;
  size_t len;
  size_t cap;
};
#define register struct _RegisterX32

// init & deinit
extern void global_func_init();
extern void global_func_deinit();

static inline void runtime_global_init() {
  global_func_init();
}

static inline void runtime_global_deinit() {
  global_func_deinit();
}

// func.c
void global_func_insert();
void global_func_pop();
void global_func_pop_n();
