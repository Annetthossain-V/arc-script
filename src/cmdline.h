#pragma once
#include <stdint.h>

#define cmdline_value struct _cmdline_values
struct _cmdline_values {
  char str[255];
  int value;
};

#define CMD_VALUE_FILE 1

cmdline_value** handle_args(int argc, char** argv, uint16_t* len, uint16_t* file_len);
void close_args(cmdline_value** args, uint16_t* len);
