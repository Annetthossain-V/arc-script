#include "../global.h"
#include "types.h"
#include <stdint.h>
#include <pthread.h>

static pthread_mutex_t ENV_MUTEX;

static uint8_t* CURRENT_SCOPE;
static uint32_t SCOPE_LEN;
static uint32_t SCOPE_CAP;

static uint8_t CURRENT_SECTION;

void set_current_section(uint8_t section) {
  pthread_mutex_lock(&ENV_MUTEX);
  CURRENT_SECTION = section;
  pthread_mutex_unlock(&ENV_MUTEX);
}
uint8_t get_current_section() {
  return CURRENT_SECTION;
}

void env_init() {
  pthread_mutex_init(&ENV_MUTEX, NULL);

  SCOPE_LEN = 0;
  SCOPE_CAP = 16;

  CURRENT_SCOPE = (uint8_t*) malloc(sizeof(uint8_t) * SCOPE_CAP);
  CURRENT_SCOPE[0] = SCOPE_GLOBAL;
}

void env_deinit() {
  pthread_mutex_destroy(&ENV_MUTEX);
  free(CURRENT_SCOPE);
}

void add_scope(uint8_t scope) {
  pthread_mutex_lock(&ENV_MUTEX);
  SCOPE_LEN++;
  CURRENT_SCOPE[SCOPE_LEN] = scope;
  pthread_mutex_unlock(&ENV_MUTEX);
}

void pop_scope() {
  pthread_mutex_lock(&ENV_MUTEX);
  SCOPE_LEN--;
  pthread_mutex_unlock(&ENV_MUTEX);
}
uint8_t current_scope() {
  return CURRENT_SCOPE[SCOPE_LEN];
}
