#include "strc.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char** tokenize_str_raw(const char* s, const char* delims, size_t* out_count) {
  char **arr = NULL;
  size_t n = 0;
  const char *p = s;
  while (*p) {
      if (isspace((unsigned char)*p)) { ++p; continue; }              /* skip whitespace */
      if (strchr(delims, *p)) {                                       /* single-char delimiter token */
          char *t = malloc(2); if (!t) goto err;
          t[0] = *p; t[1] = '\0'; ++p;
          char **tmp = realloc(arr, (n+1) * sizeof *arr); if (!tmp) { free(t); goto err; }
          arr = tmp; arr[n++] = t;
          continue;
      }
      /* regular token (run of non-space, non-delim chars) */
      const char *q = p;
      while (*q && !isspace((unsigned char)*q) && !strchr(delims, *q)) ++q;
      size_t len = q - p;
      char *t = malloc(len + 1); if (!t) goto err;
      memcpy(t, p, len); t[len] = '\0';
      char **tmp = realloc(arr, (n+1) * sizeof *arr); if (!tmp) { free(t); goto err; }
      arr = tmp; arr[n++] = t;
      p = q;
  }
  *out_count = n;
  return arr;

  err:
    for (size_t i = 0; i < n; ++i) free(arr[i]);
    free(arr);
    *out_count = 0;
    return NULL;
}

void free_str_arr(char **s, size_t *count) {
  while(*count) {
    free(s[*count]);
    *count = *count - 1;
  }
  free(s);
}
