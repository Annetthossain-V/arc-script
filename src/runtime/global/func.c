#include "../global.h"
#include <pthread.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static pthread_mutex_t GLOBAL_FUNC_MUTEX;

static table2_t** FUNC_TABLE;
static uint32_t FUNC_TABLE_LEN;
static uint32_t FUNC_TABLE_CAP;

static inline void grow_table() {
  FUNC_TABLE_CAP += 16;
  FUNC_TABLE = (table2_t**) realloc(FUNC_TABLE, sizeof(table2_t*) * FUNC_TABLE_CAP);
}

void global_func_init() {
  pthread_mutex_init(&GLOBAL_FUNC_MUTEX, NULL);
  FUNC_TABLE_CAP = 16;
  FUNC_TABLE_LEN = 0;
  FUNC_TABLE = (table2_t**) malloc(sizeof(table2_t*) * FUNC_TABLE_CAP);
}

void global_func_deinit() {
  pthread_mutex_destroy(&GLOBAL_FUNC_MUTEX);
  for (uint32_t i = 0; i < FUNC_TABLE_LEN; i++) {
    if (FUNC_TABLE[i]->id1 != NULL)
      free(FUNC_TABLE[i]->id1);
    if (FUNC_TABLE[i]->id2 != NULL)
      free(FUNC_TABLE[i]->id2);
    if (FUNC_TABLE[i] != NULL)
      free(FUNC_TABLE[i]);
  }
  free(FUNC_TABLE);
}

void global_func_insert(char* name, uint32_t index) {
  pthread_mutex_lock(&GLOBAL_FUNC_MUTEX);

  if (FUNC_TABLE_LEN >= FUNC_TABLE_CAP)
    grow_table();

  FUNC_TABLE[FUNC_TABLE_LEN] = (table2_t*) malloc(sizeof(table2_t));

  FUNC_TABLE[FUNC_TABLE_LEN]->id1 = (char*) malloc(strlen(name) + 1);
  strcpy(FUNC_TABLE[FUNC_TABLE_LEN]->id1, name);

  FUNC_TABLE[FUNC_TABLE_LEN]->id2 = (uint32_t*) malloc(sizeof(uint32_t));
  *(uint32_t*)FUNC_TABLE[FUNC_TABLE_LEN]->id2 = index;

  FUNC_TABLE_LEN++;
  pthread_mutex_unlock(&GLOBAL_FUNC_MUTEX);
}

void global_func_remove(char* name) {
  pthread_mutex_lock(&GLOBAL_FUNC_MUTEX);

  uint32_t i = 0;
  int32_t func_index = global_func_find(name, &i);
  if (func_index == -1) {
    fprintf(stderr, "[WARN] remove function doesn't exist\n");
    return;
  }

  free(FUNC_TABLE[i]->id1);
  free(FUNC_TABLE[i]->id2);
  free(FUNC_TABLE[i]);

  arr_shift_left((void**)FUNC_TABLE, FUNC_TABLE_LEN, i);
  FUNC_TABLE_LEN--;

  pthread_mutex_unlock(&GLOBAL_FUNC_MUTEX);
}

int32_t global_func_find(char* name, uint32_t* ii) {
  pthread_mutex_lock(&GLOBAL_FUNC_MUTEX);

  for (uint32_t i = 0; i < FUNC_TABLE_LEN; i++) {
    if (FUNC_TABLE[i]->id1 != NULL && strcmp(FUNC_TABLE[i]->id1, name) == 0) {
      if (ii != NULL)
        *ii = i;

      pthread_mutex_unlock(&GLOBAL_FUNC_MUTEX);
      return (int32_t) *(uint32_t*)FUNC_TABLE[i]->id2;
    }
  }

  pthread_mutex_unlock(&GLOBAL_FUNC_MUTEX);
  return -1;
}
