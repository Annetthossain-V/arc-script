#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "cmdline.h"

void close_args(cmdline_value **args, uint16_t* len) {
  for (uint16_t i = 0; i < *len; i++) {
    if (args[i] != NULL)
      free(args[i]);
  }
  free(args);
  *len = 0;
}

cmdline_value** handle_args(int argc, char** argv, uint16_t* len) {
  cmdline_value** args = (cmdline_value**)malloc(sizeof(cmdline_value) * (argc - 1) + 1);
  for (int i = 1; i < argc; i++) {
    if (strlen(argv[i]) > 255)
      return NULL; // memory leak, need to fix later

    cmdline_value* arg = (cmdline_value*)malloc(sizeof(cmdline_value) + 1);
    args[*len] = arg;
    if (argv[i][0] == '-') {

    } else {
      strcpy(arg->str, argv[i]);
      arg->value = CMD_VALUE_FILE;
    }
    *len = i;
  }

  return args;
}
