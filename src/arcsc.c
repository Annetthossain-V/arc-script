#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include "cmdline.h"
#include "parser/lexer.h"
#include "parser/parse.h"
#include "runtime/global.h"
#include "vm/code.h"

char* load_file_mem(char* name) {
  FILE* fp = fopen(name, "rb");
  if (fp == NULL)
    return NULL;

  fseek(fp, 0, SEEK_END);
  long size = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  char* buf = (char*)malloc(size + 1);
  fread(buf, sizeof(char), size, fp);
  buf[size + 1] = '\0';

  return buf;
}

int main(int argc, char** argv) {
  uint16_t args_len = 0;
  cmdline_value** args = handle_args(argc, argv, &args_len);
  if (args == NULL) {
    fprintf(stderr, "[ERR] Unable to get args!\n");
    return EXIT_FAILURE;
  }

  runtime_global_init();

  // instead of creating new bytecodes and running and deleting for each file
  // make parse all the files and merge the bytecodes
  bool can_file = false;
  for (uint16_t i = 0; i < args_len; i++) {
    if (args[i]->value == CMD_VALUE_FILE) {
      can_file = true;
      char* file_buf = load_file_mem(args[i]->str);
      if (file_buf == NULL) {
        fprintf(stderr, "[ERR] Unable to read file %s\n", args[i]->str);
        return EXIT_FAILURE; /* continue; */
      }

      unsigned int lex_tokens_len = 0;
      lexer_token** lex_tokens = lex_tokenize_str(file_buf, &lex_tokens_len);
      if (lex_tokens == NULL) {
        fprintf(stderr, "[ERR] Unable to tokenize!\n");
        return EXIT_FAILURE;
      }

      size_t parse_len = 0;
      parsed_bytecode** bytecode = parse_lexer_tokens(lex_tokens, &lex_tokens_len, &parse_len);

      close_lexer_token(lex_tokens, lex_tokens_len);
      if (bytecode == NULL) {
        fprintf(stderr, "[ERR] Unable to parse tokens!\n");
        return EXIT_FAILURE;
      }

      dummy_dbg(bytecode, (int)parse_len);

      free_parse_bytecode(bytecode, &parse_len);
      free(file_buf);
    }
  }

  if (!can_file) {
    fprintf(stderr, "[ERR] No file specified!\n");
    fprintf(stderr, "Usage: %s <options> <files>\n", argv[0]);
    close_args(args, &args_len);
    return EXIT_FAILURE;
  }

  close_args(args, &args_len);
  runtime_global_deinit();
  return EXIT_SUCCESS;
}
