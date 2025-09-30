#pragma once
#include "global/types.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>


// init & deinit
void global_func_init();
void global_func_deinit();
void register_init();
void register_deinit();
void env_init();
void env_deinit();

static inline void runtime_global_init() {
  global_func_init();
  register_init();
  env_init();
}

static inline void runtime_global_deinit() {
  global_func_deinit();
  register_deinit();
  env_deinit();
}

// func.c
void global_func_insert(char* name, uint32_t index);
void global_func_remove(char* name);
int32_t global_func_find(char* name, uint32_t* i);

// env.c
void add_scope(uint8_t scope);
void pop_scope();
uint8_t current_scope();
void set_current_section(uint8_t section);
uint8_t get_current_section();

// register.c
bool set_register();
bool get_register();
bool move_stack();
