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
  uint16_t file_len;
  cmdline_value** args = handle_args(argc, argv, &args_len, &file_len);
  if (args == NULL) {
    fprintf(stderr, "[ERR] Unable to get args!\n");
    return EXIT_FAILURE;
  }

  runtime_global_init();

  size_t arr_len = 0;
  lexer_token*** lex_tokens_arr = (lexer_token***) malloc(sizeof(lexer_token**) * file_len);
  unsigned int** lex_len = (unsigned int**) malloc(sizeof(unsigned int*) * file_len + 2);

  parsed_bytecode*** bytecodes_arr = (parsed_bytecode***) malloc(sizeof(parsed_bytecode**) * file_len);
  size_t** bcode_len = (size_t**) malloc(sizeof(size_t*) * file_len + 2);

  for (uint16_t i = 0; i < file_len; i++) {
    bcode_len[i] = (size_t*) malloc(sizeof(size_t));
    lex_len[i] = (unsigned int*) malloc(sizeof(unsigned int));
  }

  for (uint16_t i = 0; i < args_len; i++) {
    if (args[i]->value == CMD_VALUE_FILE) {
      char* file_buf = load_file_mem(args[i]->str);
      if (file_buf == NULL) {
        fprintf(stderr, "[ERR] Reading File %s\n", args[i]->str);
        return 1;
      }

      lex_tokens_arr[arr_len] = lex_tokenize_str(file_buf, lex_len[arr_len]);
      if (lex_tokens_arr[arr_len] == NULL) {
        fprintf(stderr, "[ERR] lexing File\n");
        return 1;
      }

      bytecodes_arr[arr_len] = parse_lexer_tokens(lex_tokens_arr[arr_len], lex_len[arr_len], bcode_len[arr_len]);
      if (bytecodes_arr[arr_len] == NULL) {
        fprintf(stderr, "[ERR] Parsing File\n");
        return 1;
      }

      arr_len++;
      free(file_buf);
    }
  }

  for (size_t i = 0; i < arr_len; i++) {
    _Bool stat = _start_code(bytecodes_arr[i], *bcode_len[i]);
    if (stat == 0) {
      fprintf(stderr, "[ERR] failed to execute bytecode\n");
      return 1;
    }
  }

  for(uint16_t i = 0; i < file_len; i++) {
    free(lex_len[i]);
    free(bcode_len[i]);
  }
  free(lex_len);
  free(bcode_len);

  for (size_t i = 0; i < arr_len; i++) {
    free(lex_tokens_arr[i]);
    free(bytecodes_arr[i]);
  }
  free(lex_tokens_arr);
  free(bytecodes_arr);

  close_args(args, &args_len);
  runtime_global_deinit();
  return EXIT_SUCCESS;
}
