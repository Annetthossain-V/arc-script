#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include "cmdline.h"

int main(int argc, char** argv) {
  uint16_t args_len = 0;
  cmdline_value** args = handle_args(argc, argv, &args_len);
  if (args == NULL) {
    fprintf(stderr, "[ERR] Unable to get args!\n");
    return 1;
  }



  close_args(args, &args_len);
  return 0;
}
