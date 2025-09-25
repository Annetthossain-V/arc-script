#include "../global.h"
#include <pthread.h>
#include <stdlib.h>

static pthread_mutex_t GLOBAL_FUNC_MUTEX;
static keys2* FUNC_TABLE;

void global_func_init() {
  pthread_mutex_init(&GLOBAL_FUNC_MUTEX, NULL);

  FUNC_TABLE = (keys2*) malloc(sizeof(keys2));

  FUNC_TABLE->len = 0;
  FUNC_TABLE->cap = 16;

  FUNC_TABLE->k1 = malloc(sizeof(char*) * FUNC_TABLE->cap);
  FUNC_TABLE->k2 = malloc(sizeof(int*) * FUNC_TABLE->cap);

  FUNC_TABLE->type[0] = G_TYPE_CHAR;
  FUNC_TABLE->type[1] = G_TYPE_INT;

  FUNC_TABLE->k1[0] = NULL;
  FUNC_TABLE->k2[0] = NULL;
  return;
}

void global_func_deinit() {
  pthread_mutex_destroy(&GLOBAL_FUNC_MUTEX);

  for (size_t i = 0; i < FUNC_TABLE->len; i++) {
    if (FUNC_TABLE->k1[i] != NULL)
      free(FUNC_TABLE->k1[i]);
    if (FUNC_TABLE->k2[i] != NULL)
      free(FUNC_TABLE->k2[i]);
  }

  free(FUNC_TABLE->k2);
  free(FUNC_TABLE->k1);
  free(FUNC_TABLE);

  return;
}

void global_func_insert() {}

void global_func_pop() {}

void global_func_pop_n() {}
