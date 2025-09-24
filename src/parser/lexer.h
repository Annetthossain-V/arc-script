#pragma once

#define lexer_token struct _lexer_token
struct _lexer_token {
  char* data;
  int token;
};

lexer_token** lex_tokenize_str(char* str);
void close_lexer_token(lexer_token** lex);

#define LEX_TOK_OTHER 10
#define LEX_TOK_SECTION 11
#define LEX_TOK_FUNC 12
