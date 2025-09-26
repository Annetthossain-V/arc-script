#include "parse.h"
#include "parse_kw.h"
#include "lexer.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool pkw_generic(unsigned int *i, struct _lexer_token **lex_tokens, unsigned int *lex_len, struct _parsed_bytecode *bcode) { return false; }

bool pkw_mov(unsigned int* i, lexer_token** lex_tokens, unsigned int* lex_len, parsed_bytecode* bcode) {
  if ((*lex_len - *i) < 3) {
    fprintf(stderr, "[ERR] mov expected 2 operands\n");
    return false;
  }
  if (lex_tokens[*i + 2]->token != TOK_COMMA) {
    fprintf(stderr, "[ERR] mov expected comma separating two items\n");
    return false;
  }

  bcode->kw_inst[0] = (uint16_t*) malloc(sizeof(uint16_t));
  bcode->kw_len = 1;
  bcode->kw_word[0] = NULL;
  *bcode->kw_inst[0] = PKW_MOV;

  bcode->kw_inst[1] = NULL;
  bcode->kw_len++;
  bcode->kw_word[1] = (char*) malloc(strlen(lex_tokens[*i + 1]->data));
  strcpy(bcode->kw_word[1], lex_tokens[*i + 1]->data);

  bcode->kw_inst[2] = NULL;
  bcode->kw_len++;
  bcode->kw_word[2] = (char*) malloc(strlen(lex_tokens[*i + 3]->data));
  strcpy(bcode->kw_word[2], lex_tokens[*i + 3]->data);

  *i += 3;
  return true;
}

bool pkw_section(unsigned int* i, lexer_token** lex_tokens, unsigned int* lex_len, parsed_bytecode* bcode) {
  return false;
}

bool pkw_end(unsigned int* i, lexer_token** lex_tokens, unsigned int* lex_len, parsed_bytecode* bcode) {}
