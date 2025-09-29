#include "parse.h"
#include "parse_kw.h"
#include "lexer.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static void inc_bcode_cap(parsed_bytecode* bcode) {
  bcode->kw_cap += 16;
  bcode->kw_inst = (uint16_t**) realloc(bcode->kw_inst, (sizeof(uint16_t*) * bcode->kw_cap));
  bcode->kw_word = (char**) realloc(bcode->kw_word, (sizeof(char*) * bcode->kw_cap));
}

// rules
// check if its '[' if not then only name
// if it is then check for ']' after that ',' and again
// 'mov r0, [r1 + r2];'
//
// BUG: skips r3 for some reason
// caused by a buffer overflow
// need to find that buffer overflow

bool _pkw_i2_parse(unsigned int* i, lexer_token** lex_tokens, unsigned int* lex_len, parsed_bytecode* bcode) {
  unsigned int j = 0;
  // unsigned int bindex = 1;
  bool expecting_comma = false;
  unsigned char input_count = 0;
  bool semi = false;

  // if ; is not present this loops until everything ends
  for (j = 0; j < (*lex_len - *i) + 1; j++) {
    if (bcode->kw_cap <= bcode->kw_len)
      inc_bcode_cap(bcode);

    if (lex_tokens[*i + j]->token == TOK_SQUARE_BRACKET_OPEN) {
      bcode->kw_word[bcode->kw_len] = NULL;
      bcode->kw_inst[bcode->kw_len] = (uint16_t*) malloc(sizeof(uint16_t));
      *bcode->kw_inst[bcode->kw_len] = PKW_PI2P_DEREF;
      bcode->kw_len++;
      // bindex++;

      bool expecting_name = true;
      while (lex_tokens[*i + j]->token != TOK_SQUARE_BRACKET_CLOSE) {
        if (bcode->kw_cap <= bcode->kw_len)
          inc_bcode_cap(bcode);

        j++;
        if ((*i + j) >= *lex_len) {
          fprintf(stderr, "[ERR] '[' out of bound\n");
          return false;
        }
        if (lex_tokens[*i + j]->token == TOK_UNKNOWN) {
          if (!expecting_name) {
            fprintf(stderr, "[ERR Token name was not expected!\n");
            return false;
          } expecting_name = false;

          bcode->kw_inst[bcode->kw_len] = (uint16_t*) malloc(sizeof(uint16_t));
          *bcode->kw_inst[bcode->kw_len] = PKW_PI2P_NAME;
          bcode->kw_word[bcode->kw_len] = (char*) malloc(strlen(lex_tokens[*i + j]->data) + 1);
          strcpy(bcode->kw_word[bcode->kw_len], lex_tokens[*i + j]->data);
          bcode->kw_len++;
        } else {
          if (expecting_name) {
            fprintf(stderr, "[ERR Token name was expected\n");
            return false;
          }

          bcode->kw_inst[bcode->kw_len] = (uint16_t*) malloc(sizeof(uint16_t));
          bcode->kw_word[bcode->kw_len] = NULL;

          switch (lex_tokens[*i + j]->token) {
            case TOK_PLUS_SIGN:
              *bcode->kw_inst[bcode->kw_len] = PKW_PI2P_ADD;
              break;
            case TOK_MINUS_SIGN:
              *bcode->kw_inst[bcode->kw_len] = PKW_PI2P_SUB;
              break;
            case TOK_ASTERISK:
              *bcode->kw_inst[bcode->kw_len] = PKW_PI2P_MUL;
              break;
            case TOK_SLASH:
              *bcode->kw_inst[bcode->kw_len] = PKW_PI2P_DIV;
              break;
            case TOK_SQUARE_BRACKET_CLOSE:
              *bcode->kw_inst[bcode->kw_len] = PKW_PI2P_DEREF_END;
              break;
            default:
              fprintf(stderr, "[ERR] Unknown Token! T%d\n", lex_tokens[*i + j]->token);
              return false;
          }
          expecting_name = true;
          bcode->kw_len++;
        }
      }
      input_count++;
      if (input_count == 1)
        expecting_comma = true;
    }
    else if (lex_tokens[*i + j]->token == TOK_UNKNOWN) {
      bcode->kw_inst[bcode->kw_len] = (uint16_t*) malloc(sizeof(uint16_t));
      *bcode->kw_inst[bcode->kw_len] = PKW_PI2P_NAME;
      bcode->kw_word[bcode->kw_len] = (char*) malloc(strlen(lex_tokens[*i + j]->data) + 1);
      strcpy(bcode->kw_word[bcode->kw_len], lex_tokens[*i + j]->data);
      bcode->kw_len++;

      input_count++;
      if (input_count == 1)
        expecting_comma = true;
    }
    else if (lex_tokens[*i + j]->token == TOK_SEMI_COLON) { semi = true; break; }
    else if (expecting_comma && lex_tokens[*i + j]->token == TOK_COMMA) { continue; }
    else {
      fprintf(stderr, "[ERR] [_pkw_i2_parse] unknown token! j%u token %d\n", j, lex_tokens[*i + j]->token);
      return false;
    }
  }

  if (!semi) {
    fprintf(stderr, "[ERR] missed a semi-colon!\n");
    return false;
  }

  *i += j;
  return true;
}
