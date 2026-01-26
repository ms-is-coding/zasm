#ifndef ZASM_TOKEN_H
#define ZASM_TOKEN_H

#include <stddef.h>

typedef enum {
  ZASMT_IDENT,
  ZASMT_NUM,
  ZASMT_STR,
  ZASMT_PUNCT,
  ZASMT_NEWL,
  ZASMT_EOF,
} zasm_token_type;

typedef struct {
  zasm_token_type type;
  int             line;
  const char      *start;
  size_t          len;
  size_t          value;
} zasm_token;

#endif
