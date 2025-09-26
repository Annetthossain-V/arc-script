#pragma once
#include "parse.h"
#include <stdbool.h>

// opcodes
#define PKW_MOV 1

bool pkw_mov(unsigned int* i, lexer_token** lex_tokens, unsigned int* lex_len, parsed_bytecode* bcode);
