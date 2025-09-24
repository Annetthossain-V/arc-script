#pragma once

#define lexer_token struct _lexer_token
struct _lexer_token {
  char* data;
  int token;
};

lexer_token** lex_tokenize_str(const char* str, unsigned int* len);
void close_lexer_token(lexer_token** lex, unsigned int len);

#define LEX_TOK_OTHER 10
#define LEX_TOK_SECTION 11
#define LEX_TOK_FUNC 12
#define LEX_TOK_CALL 13
#define LEX_TOK_FCALL 14
#define LEX_TOK_ECALL 15
