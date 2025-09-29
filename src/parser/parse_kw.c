#include "parse.h"
#include "parse_kw.h"
#include "lexer.h"
#include "../runtime/global.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool pkw_mov(unsigned int* i, lexer_token** lex_tokens, unsigned int* lex_len, parsed_bytecode* bcode, size_t bcode_len) {
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

bool pkw_section(unsigned int* i, lexer_token** lex_tokens, unsigned int* lex_len, parsed_bytecode* bcode, size_t bcode_len) {
  if (*i + 1 >= *lex_len) {
    fprintf(stderr, "[ERR] section out of bound\n");
    return false;
  }

  bcode->kw_word[bcode->kw_len] = NULL;
  bcode->kw_inst[bcode->kw_len] = (uint16_t*) malloc(sizeof(uint16_t));
  *bcode->kw_inst[bcode->kw_len] = PKW_SECTION;
  bcode->kw_len++;

  *i += 1;

  bcode->kw_inst[bcode->kw_len] = (uint16_t*) malloc(sizeof(uint16_t));
  bcode->kw_word[bcode->kw_len] = NULL;

  if (lex_tokens[*i]->data == NULL) {
    fprintf(stderr, "[ERR] Expected section name!\n");
    return false;
  }

  if (strcmp(lex_tokens[*i]->data, "text") == 0)
    *bcode->kw_inst[bcode->kw_len] = PKW_O2_SECT_TEXT;
  else if (strcmp(lex_tokens[*i]->data, "data") == 0)
    *bcode->kw_inst[bcode->kw_len] = PKW_O2_SECT_DATA;
  else if (strcmp(lex_tokens[*i]->data, "rodata") == 0)
    *bcode->kw_inst[bcode->kw_len] = PKW_O2_SECT_RODATA;
  else {
    fprintf(stderr, "[ERR] Unknown Section ID: %s\n", lex_tokens[*i]->data);
    return false;
  }

  bcode->kw_len++;
  return true;
}

bool pkw_end(unsigned int* i, lexer_token** lex_tokens, unsigned int* lex_len, parsed_bytecode* bcode, size_t bcode_len) {
  bcode->kw_inst[bcode->kw_len] = (uint16_t*) malloc(sizeof(uint16_t));
  *bcode->kw_inst[bcode->kw_len] = PKW_END;
  bcode->kw_word[bcode->kw_len] = NULL;
  bcode->kw_len++;

  return true;
}

bool pkw_func(unsigned int* i, lexer_token** lex_tokens, unsigned int* lex_len, parsed_bytecode* bcode, size_t bcode_len) {
  *i += 1;
  if (*i > *lex_len) {
    fprintf(stderr, "[ERR] func out of bound\n");
    return false;
  }

  if (lex_tokens[*i]->data == NULL) {
    fprintf(stderr, "[ERR] func name not found!\n");
    return false;
  }

  bcode->kw_inst[bcode->kw_len] = (uint16_t*) malloc(sizeof(uint16_t));
  *bcode->kw_inst[bcode->kw_len] = PKW_FUNC;
  bcode->kw_word[bcode->kw_len] = (char*) malloc(strlen(lex_tokens[*i]->data) + 1);
  strcpy(bcode->kw_word[bcode->kw_len], lex_tokens[*i]->data);
  bcode->kw_len++;

  // env insert
  global_func_insert(bcode->kw_word[bcode->kw_len - 1], (uint32_t)bcode_len);

  return true;
}
