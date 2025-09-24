#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "strc.h"

void close_lexer_token(lexer_token **lex, unsigned int len) {
  for (int i = 0; i < len; i++) {
    if (lex[i]->data != NULL)
      free(lex[i]->data);
  }
  free(lex);
}

unsigned int str_to_token(char* str) {
  unsigned int retval = LEX_TOK_OTHER;

  if (strcmp(str, "section") == 0)
    retval = LEX_TOK_SECTION;
  else if (strcmp(str, "func") == 0)
    retval = LEX_TOK_FUNC;

  return retval;
}

lexer_token** lex_tokenize_str(const char* str, unsigned int* len) {
  char* delims = " []{}()$@:*&-+<>";
  size_t tokens_str_len = 0;
  char** tokens_str = tokenize_str_raw(str, delims, &tokens_str_len);

  for (size_t i = 0; i < tokens_str_len; i++) {

  }

  for (size_t i = 0; i < tokens_str_len; i++) {
    free(tokens_str[i]);
  } free(tokens_str);
  return NULL;
}
