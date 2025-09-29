#pragma once
#include "lexer.h"
#include "parse.h"
#include <stdbool.h>

// special codes {Pi2P}
#define PKW_PI2P_DEREF 1
#define PKW_PI2P_MUL 2
#define PKW_PI2P_DIV 3
#define PKW_PI2P_ADD 4
#define PKW_PI2P_SUB 5
#define PKW_PI2P_NAME 6
#define PKW_PI2P_MODE 7
#define PKW_PI2P_DEREF_END 8

// special codes {O2}
#define PKW_O2_NAME 1
#define PKW_O2_SECT_TEXT 2
#define PKW_O2_SECT_DATA 3
#define PKW_O2_SECT_RODATA 4

// opcodes
#define PKW_MOV 1
#define PKW_SECTION 2
#define PKW_END 3
#define PKW_FUNC 4

// the chosen one
// Sataro Gojo
#define PKW_GENERIC 40000
bool pkw_generic(unsigned int* i, lexer_token** lex_tokens, unsigned int* lex_len, parsed_bytecode* bcode);

bool pkw_mov(unsigned int* i, lexer_token** lex_tokens, unsigned int* lex_len, parsed_bytecode* bcode);
bool pkw_section(unsigned int* i, lexer_token** lex_tokens, unsigned int* lex_len, parsed_bytecode* bcode);
bool pkw_end(unsigned int* i, lexer_token** lex_tokens, unsigned int* lex_len, parsed_bytecode* bcode);
bool pkw_func(unsigned int* i, lexer_token** lex_tokens, unsigned int* lex_len, parsed_bytecode* bcode);

bool _pkw_i2_parse(unsigned int* i, lexer_token** lex_tokens, unsigned int* lex_len, parsed_bytecode* bcode);
