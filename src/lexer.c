#include "token.h"
#include "zasm.h"
#include <stdlib.h>
#include <ctype.h>

char* unescape_string(const char* src, int len) {
  char* dest = malloc(len + 1);
  int i = 0;
  int j = 0;

  while (i < len) {
    if (src[i] == '\\' && i + 1 < len) {
      i++;
      switch (src[i]) {
        case 'n':  dest[j++] = '\n'; break;
        case 't':  dest[j++] = '\t'; break;
        case 'r':  dest[j++] = '\r'; break;
        case '\\': dest[j++] = '\\'; break;
        case '\"': dest[j++] = '\"'; break;
        case '0':  dest[j++] = '\0'; break;
        default:
          dest[j++] = src[i];
          break;
      }
    } else {
      dest[j++] = src[i];
    }
    i++;
  }

  dest[j] = '\0';
  return dest;
}

zasm_token *zasm_lex(zasm_file in, size_t *tok_count) {
  size_t cap = 128;
  size_t count = 0;
  zasm_token *tokens = malloc(cap * sizeof(zasm_token));

  if (!tokens) {
    return NULL;
  }
  char *p = (char *)in.data;
  char *end = p + in.size;
  int line = 0;

  while (p < end) {
    // whitespace
    if (isspace(*p) && *p != '\n') { p++; continue; }
    // comments
    if (*p == '/' && *(p + 1) == '/') {
      while (p < end && *p != '\n') p++;
    }

    if (count + 1 >= cap) {
      cap *= 2;
      tokens = realloc(tokens, cap * sizeof(zasm_token));
    }

    zasm_token *t = &tokens[count++];

    t->line = line;
    t->value = 0;
    if (*p == '"') {
      t->type = ZASMT_STR;
      t->start = ++p;
      while (p < end && *p != '"') {
        if (*p == '\\') {
          p++;
          if (p >= end) break;
        }
        p++;
      }
      t->len = p - t->start;
      // t->start = unescape_string(t->start, t->len);
      if (p < end) p++;
    }
    else if (isdigit(*p)) {
      t->type =  ZASMT_NUM;
      t->start = p;
      t->value = strtol(p, &p, 0);
      t->len = p - t->start;
    }
    else if (isalpha(*p) || *p == '_') {
      t->type = ZASMT_IDENT;
      t->start = p;
      while (p < end && (isalnum(*p) || *p == '_')) p++;
      t->len = p - t->start;
    }
    else if (*p == '\n') {
      t->type = ZASMT_NEWL;
      t->start = p;
      t->len = 0;
      line++;
      p++;
    }
    else {
      t->type = ZASMT_PUNCT;
      t->start = p;
      t->len = 1;
      p++;
    }

  }

  tokens[count].type = ZASMT_EOF;
  tokens[count].start = p;
  tokens[count].line = line;
  tokens[count].len = 0;
  *tok_count = count;
  return tokens;

  return NULL;
}
