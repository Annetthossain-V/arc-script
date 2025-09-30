#include "../global.h"
#include <stdint.h>
#include <pthread.h>

static pthread_mutex_t REGIST_MUTEX;

static register** REGISTERS;
static uint32_t REG_SIZE;

static register** STACK;
static uint32_t STK_LEN;
static uint32_t STK_CAP;

void register_init() {
  pthread_mutex_init(&REGIST_MUTEX, NULL);
}

void register_deinit() {
  pthread_mutex_destroy(&REGIST_MUTEX);
}
