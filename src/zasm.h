#ifndef ZASM_H
#define ZASM_H

#include <stddef.h>
#include <stdint.h>
#include "ast.h"

typedef struct {
  uint8_t *data;
  size_t  size;
  int     error;
} zasm_file;

typedef enum {
  ZASMT_IDENT,
  ZASMT_NUM,
  ZASMT_STR,
  ZASMT_PUNCT,
  ZASMT_EOF,
} zasm_token_type;

typedef struct {
  zasm_token_type type;
  int             line;
  const char      *start;
  size_t          len;
  size_t          value;
} zasm_token;

zasm_file zasm_input(const char *filename);
zasm_file zasm_output(const char *filename, size_t size);
void zasm_close(zasm_file file);

zasm_token *zasm_lex(zasm_file in, size_t *tok_count);
zasm_program *zasm_parse(zasm_token *tokens, size_t tok_count);

#endif // ZASM_H
