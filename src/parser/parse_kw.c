#include "parse.h"
#include "parse_kw.h"
#include "lexer.h"
#include <stdbool.h>
#include <stdio.h>

bool pkw_mov(unsigned int* i, lexer_token** lex_tokens, unsigned int* lex_len, parsed_bytecode* bcode) {
  if ((*lex_len - *i) < 3) {
    fprintf(stderr, "[ERR] mov expected 2 operands\n");
    return false;
  }
  if (lex_tokens[*i + 2]->token != TOK_COMMA) {
    fprintf(stderr, "[ERR] mov expected comma separating two items\n");
    return false;
  }



  return true;
}
