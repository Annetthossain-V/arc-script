#pragma once
#include <stdlib.h>

char** tokenize_str_raw(const char* s, const char* delims, size_t* out_count);
void free_str_arr(char** s, size_t* count);
