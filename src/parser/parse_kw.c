#include "parse.h"
#include "parse_kw.h"
#include "lexer.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool pkw_mov(unsigned int* i, lexer_token** lex_tokens, unsigned int* lex_len, parsed_bytecode* bcode) {
  if (*i + 1 >= *lex_len) {
    fprintf(stderr, "[ERR] Mov out of bound\n");
    return false;
  }

  bcode->kw_len++;
  bcode->kw_word[0] = NULL;
  bcode->kw_inst[0] = (uint16_t*) malloc(sizeof(uint16_t));
  *bcode->kw_inst[0] = PKW_MOV;

  if (lex_tokens[*i + 1]->data == NULL) {
    fprintf(stderr, "[ERR] mov requires specified mode\n");
    return false;
  }

  bcode->kw_len++;
  bcode->kw_inst[1] = (uint16_t*) malloc(sizeof(uint16_t));
  *bcode->kw_inst[1] = PKW_PI2P_MODE;
  bcode->kw_word[1] = (char*) malloc(strlen(lex_tokens[*i + 1]->data) + 1);
  strcpy(bcode->kw_word[1], lex_tokens[*i +1]->data);

  *i += 2;
  if (!_pkw_i2_parse(i, lex_tokens, lex_len, bcode))
    return false;

  return true;
}

bool pkw_section(unsigned int* i, lexer_token** lex_tokens, unsigned int* lex_len, parsed_bytecode* bcode) {

  return false;
}

bool pkw_end(unsigned int* i, lexer_token** lex_tokens, unsigned int* lex_len, parsed_bytecode* bcode) { return false; }

bool pkw_func(unsigned int* i, lexer_token** lex_tokens, unsigned int* lex_len, parsed_bytecode* bcode) { return false; }
