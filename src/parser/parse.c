#include "parse.h"
#include "lexer.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "parse_kw.h"
#include <string.h>

#define PKW_CALL(kw, i, lex_tokens, lex_len, bcode, func, emsg, called) \
    if (strcmp(lex_tokens[*i]->data, kw) == 0) { \
      called = true;  \
      if (!func(i, lex_tokens, lex_len, bcode)) { \
        fprintf(stderr, emsg);  \
        return NULL; \
      } \
    }

static parsed_bytecode* parse_keyword_handler(unsigned int* i, lexer_token** lex_tokens, unsigned int* lex_len) {
  // lex_tokens[*i]->token is already TOK_UNKNOWN
  // no need to check
  if (lex_tokens[*i]->data == NULL)
    return NULL;

  parsed_bytecode* bcode = (parsed_bytecode*) malloc(sizeof(parsed_bytecode));
  bcode->kw_inst = (uint16_t**) malloc(sizeof(uint16_t*) * 6);
  bcode->kw_word = (char**) malloc(sizeof(char*) * 6);
  bcode->kw_len = 0;
  bcode->kw_cap = 6;

  bool called = false;

  if (strcmp(lex_tokens[*i]->data, "mov") == 0 || strcmp(lex_tokens[*i]->data, "mv") == 0 || strcmp(lex_tokens[*i]->data, "move") == 0) {
    called = true;
    if (!pkw_mov(i, lex_tokens, lex_len, bcode)) {
      fprintf(stderr, "[ERR] unable to parse kw_mov\n");
      return NULL;
    }
  }

  // performance is be lowerd because of this
  PKW_CALL("section", i, lex_tokens, lex_len, bcode, pkw_section, "[ERR] unable to parse kw_section\n", called);
  PKW_CALL("end", i, lex_tokens, lex_len, bcode, pkw_end, "[ERR unable to parse kw_end\n", called);

  // else
  if (!called) {
    if (!pkw_generic(i, lex_tokens, lex_len, bcode)) {
      fprintf(stderr, "[ERR] Unknown Keyword %s\n", lex_tokens[*i]->data);
      return NULL;
    }
  }

  return bcode;
}

static void append_bytecode(parsed_bytecode** bytecode, parsed_bytecode* appendi, unsigned int* cap, size_t len) {
  if (len - 2 == *cap) {
    bytecode = (parsed_bytecode**) realloc(*bytecode, sizeof(parsed_bytecode) * (*cap + 16));
    *cap += 16;
  }
  bytecode[len] = appendi;
}

parsed_bytecode** parse_lexer_tokens(lexer_token** lex_tokens, unsigned int* lex_len, size_t* len) {
  parsed_bytecode** bytecode = (parsed_bytecode**) malloc(sizeof(parsed_bytecode*) * 16);
  unsigned int bytecode_cap = 16;

  for (unsigned int i = 0; i < *lex_len; i++) {
    if (lex_tokens[i]->token != TOK_UNKNOWN) {
      fprintf(stderr, "[ERR] [Parser.c] Expected Keyword! Found Token\n");
      return NULL;
    }

    parsed_bytecode* bcode = parse_keyword_handler(&i, lex_tokens, lex_len);
    if (bcode == NULL) {
      fprintf(stderr, "[ERR] [Parser.c] Unable to find keyword!\n");
      return NULL;
    }

    append_bytecode(bytecode, bcode, &bytecode_cap, *len);
    (*len)++;
  }

  return bytecode;
}

void free_parse_bytecode(parsed_bytecode** bytecode, size_t* len) {
  for (size_t i = 0; i < *len; i++) {
    for (size_t j = 0; j < bytecode[i]->kw_len; j++) {
      if (bytecode[i]->kw_inst[j] != NULL)
        free(bytecode[i]->kw_inst[j]);
      if (bytecode[i]->kw_word[j] != NULL)
        free(bytecode[i]->kw_word[j]);
    }

    free(bytecode[i]->kw_word);
    free(bytecode[i]->kw_inst);
    free(bytecode[i]);

  } free(bytecode);
}
