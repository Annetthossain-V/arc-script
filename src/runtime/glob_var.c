#include "glob_var.h"
#include <pthread.h>
#include <stddef.h>
#include <stdlib.h>

pthread_mutex_t GlobalVarMutex;

token_keys** GlobalFuncTable;
static size_t GlobalFuncTable_len;

token_keys** GlobalVarTable;
static size_t GlobalVarTable_len;

static void GlobalTable_init() {
  pthread_mutex_lock(&GlobalVarMutex);

  pthread_mutex_unlock(&GlobalVarMutex);
}

static void GlobalTable_close() {
  pthread_mutex_lock(&GlobalVarMutex);

  pthread_mutex_unlock(&GlobalVarMutex);
}

void glob_vars_init() {
  pthread_mutex_init(&GlobalVarMutex, NULL);
  GlobalTable_init();
}

void close_glob_vars() {
  pthread_mutex_destroy(&GlobalVarMutex);
  GlobalTable_init();
}
