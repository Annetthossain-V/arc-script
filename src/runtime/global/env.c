#include "../global.h"
#include <stdint.h>
#include <pthread.h>

static pthread_mutex_t ENV_MUTEX;

static uint8_t* CURRENT_SCOPE;
static uint32_t SCOPE_LEN;
static uint32_t SCOPE_CAP;

void env_init() {}

void env_deinit() {}
