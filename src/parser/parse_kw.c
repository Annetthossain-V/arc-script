#include "parse.h"
#include "parse_kw.h"
#include "lexer.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool _pkw_i2_parse(unsigned int* i, lexer_token** lex_tokens, unsigned int* lex_len, parsed_bytecode* bcode) {
  unsigned int j = 0;
  unsigned int bindex = 1;
  for (j = 0; j < (*lex_len - *i) + 1; j++) {
    // rules
    // check if its '[' if not then only name
    // if it is then check for ']' after that ',' and again
    // 'mov r0, [r1 + r2];'
    if (lex_tokens[*i + j]->token == TOK_SQUARE_BRACKET_OPEN) {
      bcode->kw_word[bindex] = NULL;
      bcode->kw_len++;
      bcode->kw_inst[bindex];
      bindex++;

      while (lex_tokens[*i + j]->token != TOK_SQUARE_BRACKET_CLOSE) {
        if ((*i + j) > *lex_len) {
          fprintf(stderr, "[ERR] '[' out of bound\n");
          return false;
        }
        if (lex_tokens[*i + j]->token == TOK_UNKNOWN) {

        } else {
          switch (lex_tokens[*i + j]->token) {
            default:
              break;
          }
        }

        j++;
      }
    }
    else if (lex_tokens[*i + j]->token == TOK_UNKNOWN) {
    }
    else if (lex_tokens[*i + j]->token == TOK_SEMI_COLON) {
      break;
    }
    else if (lex_tokens[*i + j]->token == TOK_COMMA) {
    }
    else {
      fprintf(stderr, "[ERR] [_pkw_i2_parse] unknown token! j%u token %d\n", j, lex_tokens[*i + j]->token);
      return false;
    }
  }

  return true;
}

bool pkw_generic(unsigned int *i, struct _lexer_token **lex_tokens, unsigned int *lex_len, struct _parsed_bytecode *bcode) { return false; }

bool pkw_mov(unsigned int* i, lexer_token** lex_tokens, unsigned int* lex_len, parsed_bytecode* bcode) {
  bcode->kw_len++;
  bcode->kw_word[0] = NULL;
  bcode->kw_inst[0] = (uint16_t*) malloc(sizeof(uint16_t));
  *bcode->kw_inst[0] = PKW_MOV;

  *i += 1;
  if (!_pkw_i2_parse(i, lex_tokens, lex_len, bcode))
    return false;

  return true;
}

bool pkw_section(unsigned int* i, lexer_token** lex_tokens, unsigned int* lex_len, parsed_bytecode* bcode) {
  return false;
}

bool pkw_end(unsigned int* i, lexer_token** lex_tokens, unsigned int* lex_len, parsed_bytecode* bcode) { return false; }
