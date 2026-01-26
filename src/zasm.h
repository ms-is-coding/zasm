#ifndef ZASM_H
#define ZASM_H

#include <stddef.h>
#include <stdint.h>
#include "ast.h"
#include "token.h"

typedef struct {
  const char *name;
  uint8_t    *data;
  size_t     size;
  int        error;
} zasm_file;

zasm_file zasm_input(const char *filename);
zasm_file zasm_output(const char *filename, size_t size);
void zasm_close(zasm_file file);

int get_syscall(zasm_token tok);

zasm_token *zasm_lex(zasm_file in, size_t *tok_count);
zasm_program *zasm_parse(zasm_file in, zasm_token *tokens, size_t tok_count);
void zasm_codegen(zasm_program *prog, uint8_t *out_buf, size_t out_max);
void zasm_error(zasm_file in, zasm_token token, const char *message);

#endif // ZASM_H
