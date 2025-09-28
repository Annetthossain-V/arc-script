#include "../parser/parse.h"
#include "../parser/parse_kw.h"
#include "code.h"
#include <stdio.h>

void dummy_dbg(parsed_bytecode** bytecode, int len) {
  for (int i = 0; i < len; i++) {
    for (int j = 0; j < (int)bytecode[i]->kw_len; j++) {
      if (bytecode[i]->kw_inst[j] != NULL)
        printf(" [Bytecode Inst: %d] ", *bytecode[i]->kw_inst[j]);
      else
         printf(" [Skipping Bytecode Inst..] ");
      if (bytecode[i]->kw_word[j] != NULL)
        printf(" [Bytecode Word: %s] ", bytecode[i]->kw_word[j]);
      else
        printf(" [Skipping Bytecode Word].. ");
    }
  }
}
