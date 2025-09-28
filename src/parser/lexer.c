#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "strc.h"

void close_lexer_token(lexer_token **lex, unsigned int len) {
  for (int i = 0; i < len; i++) {
    if (lex[i]->data != NULL)
      free(lex[i]->data);
    free(lex[i]);
  }
  free(lex);
}

#define CHECK_TOK_MACRO(a, b, c, d)  \
  if (strcmp(a, b) == 0)             \
    c = d

static unsigned int str_to_token(char* str) {
  unsigned int retval = TOK_UNKNOWN;

  // Problem! doesn't return after finding token
  // making it check for every token
  // slowing it down
  // also we could just do str[0] == instead
  CHECK_TOK_MACRO(str, "[", retval, TOK_SQUARE_BRACKET_OPEN);
  CHECK_TOK_MACRO(str, "]", retval, TOK_SQUARE_BRACKET_CLOSE);
  CHECK_TOK_MACRO(str, "{", retval, TOK_CURLY_BRACKETS_OPEN);
  CHECK_TOK_MACRO(str, "}", retval, TOK_CURLY_BRACKETS_CLOSE);
  CHECK_TOK_MACRO(str, "(", retval, TOK_BRACKETS_OPEN);
  CHECK_TOK_MACRO(str, ")", retval, TOK_BRACKETS_CLOSE);
  CHECK_TOK_MACRO(str, "$", retval, TOK_DOLLAR_SIGN);
  CHECK_TOK_MACRO(str, "@", retval, TOK_ADD_SYMBOL);
  CHECK_TOK_MACRO(str, ":", retval, TOK_COLON);
  CHECK_TOK_MACRO(str, ";", retval, TOK_SEMI_COLON);
  CHECK_TOK_MACRO(str, "*", retval, TOK_ASTERISK);
  CHECK_TOK_MACRO(str, "&", retval, TOK_AND_SYMBOL);
  CHECK_TOK_MACRO(str, "-", retval, TOK_MINUS_SIGN);
  CHECK_TOK_MACRO(str, "+", retval, TOK_PLUS_SIGN);
  CHECK_TOK_MACRO(str, "<", retval, TOK_LESS_THAN_SYMBOL);
  CHECK_TOK_MACRO(str, ">", retval, TOK_GREATER_THAN_SYMBOL);
  CHECK_TOK_MACRO(str, ",", retval, TOK_COMMA);
  CHECK_TOK_MACRO(str, "/", retval, TOK_SLASH);

  return retval;
}

lexer_token** lex_tokenize_str(const char* str, unsigned int* len) {
  char* delims = " []{}()$@:;*&-+<>,/";
  size_t tokens_str_len = 0;
  char** tokens_str = tokenize_str_raw(str, delims, &tokens_str_len);

  lexer_token** tokens = (lexer_token**) malloc(sizeof(lexer_token) * tokens_str_len);
  for (size_t i = 0; i < tokens_str_len; i++) {
    tokens[i] = (lexer_token*) malloc(sizeof(lexer_token));
    unsigned int tok = str_to_token(tokens_str[i]);
    if (tok == TOK_UNKNOWN) {
      tokens[i]->data = (char*) malloc(strlen(tokens_str[i]) + 1);
      strcpy(tokens[i]->data, tokens_str[i]);
    } else {
      tokens[i]->data = NULL;
    }
    tokens[i]->token = tok;
    *len = i;
  }

  for (size_t i = 0; i < tokens_str_len; i++) {
    free(tokens_str[i]);
  } free(tokens_str);
  return tokens;
}
