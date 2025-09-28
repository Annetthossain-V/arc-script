#pragma once
// the lexer is gonna be
// small and simple because
// we don't really need a big complicated lexer

#define lexer_token struct _lexer_token
struct _lexer_token {
  char* data;
  int token;
};

lexer_token** lex_tokenize_str(const char* str, unsigned int* len);
void close_lexer_token(lexer_token** lex, unsigned int len);
// []{}()$@:;*&-+<>,/
#define TOK_UNKNOWN 1
#define TOK_SQUARE_BRACKET_OPEN 2
#define TOK_SQUARE_BRACKET_CLOSE 3
#define TOK_CURLY_BRACKETS_OPEN 4
#define TOK_CURLY_BRACKETS_CLOSE 5
#define TOK_BRACKETS_OPEN 6
#define TOK_BRACKETS_CLOSE 7
#define TOK_DOLLAR_SIGN 8
#define TOK_COLON 9
#define TOK_SEMI_COLON 10
#define TOK_ADD_SYMBOL 11
#define TOK_ASTERISK 12
#define TOK_AND_SYMBOL 13
#define TOK_MINUS_SIGN 14
#define TOK_PLUS_SIGN 15
#define TOK_LESS_THAN_SYMBOL 16
#define TOK_GREATER_THAN_SYMBOL 17
#define TOK_COMMA 18
#define TOK_SLASH 19
