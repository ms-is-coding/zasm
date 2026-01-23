#include "zasm.h"
#include <stdlib.h>
#include <ctype.h>

zasm_token *zasm_lex(zasm_file in, size_t *tok_count) {
  size_t cap = 128;
  size_t count = 0;
  zasm_token *tokens = malloc(cap * sizeof(zasm_token));

  if (!tokens) {
    return NULL;
  }
  char *p = (char *)in.data;
  char *end = p + in.size;

  while (p < end) {
    // whitespace
    if (isspace(*p)) { p++; continue; }
    // comments
    if (*p == '/' && *(p + 1) == '/') {
      while (p < end && *p != '\n') p++;
    }

    if (count + 1 >= cap) {
      cap *= 2;
      tokens = realloc(tokens, cap * sizeof(zasm_token));
    }

    zasm_token *t = &tokens[count++];

    if (*p == '"') {
      t->type = ZASMT_STR;
      t->start = ++p;
      while (p < end && *p != '"') p++;
      t->len = p - t->start;
      p++;
    }
    else if (isdigit(*p)) {
      t->type =  ZASMT_NUM;
      t->value = strtol(p, &p, 0);
    }
    else if (isalpha(*p) || *p == '_') {
      t->type = ZASMT_IDENT;
      t->start = p;
      while (p < end && (isalnum(*p) || *p == '_')) p++;
      t->len = p - t->start;
    }
    else {
      t->type = ZASMT_PUNCT;
      t->start = p;
      t->len = 1;
      p++;
    }

  }

  tokens[count].type = ZASMT_EOF;
  *tok_count = count;
  return tokens;

  return NULL;
}
