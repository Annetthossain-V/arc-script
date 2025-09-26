#pragma once
#include "lexer.h"
#include "parse.h"
#include <stdbool.h>

// opcodes
#define PKW_MOV 1

// the chosen one
// Sataro Gojo
#define PKW_GENERIC 40000
bool pkw_generic(unsigned int* i, lexer_token** lex_tokens, unsigned int* lex_len, parsed_bytecode* bcode);

bool pkw_mov(unsigned int* i, lexer_token** lex_tokens, unsigned int* lex_len, parsed_bytecode* bcode);
bool pkw_section(unsigned int* i, lexer_token** lex_tokens, unsigned int* lex_len, parsed_bytecode* bcode);
bool pkw_end(unsigned int* i, lexer_token** lex_tokens, unsigned int* lex_len, parsed_bytecode* bcode);
