#pragma once
#include "lexer.h"
#include <stdlib.h>
#include <stdint.h>

#define parsed_bytecode struct _parsed_bytecode
struct _parsed_bytecode {
  char** kw_word;
  uint16_t** kw_inst;
  size_t kw_len;
};

#define KW_INARR_STD_SIZE 6

parsed_bytecode** parse_lexer_tokens(lexer_token** lex_tokens, unsigned int* lex_len, size_t* len);
void free_parse_bytecode(parsed_bytecode** bytecode, size_t* len);
