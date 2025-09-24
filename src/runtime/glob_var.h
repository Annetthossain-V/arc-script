#pragma once
#include <pthread.h>
#include <stdlib.h>

#define token_keys struct __Token_Keys
struct __Token_Keys {
  void* item1;
  void* item2;
};

extern pthread_mutex_t GlobalVarMutex;

extern token_keys** GlobalFuncTable;
extern token_keys** GlobalVarTable;

void add_func_table();
void remove_func_table();
void find_func_table();

void glob_vars_init();
void close_glob_vars();
