#include "ast.h"
#include "zasm.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <syscall.h>

void report_error(int line, const char *msg, zasm_token t) {
  fprintf(stderr, "zasm error (line %d): %s '%.*s'\n", 
          line, msg, (int)t.len, t.start);
  exit(1);
}



zasm_program *zasm_parse(zasm_token *tokens, size_t count) {
  size_t i = 0;
  int current_line = 1;
  zasm_program *prog = malloc(sizeof(zasm_program));

  while (i < count && tokens[i].type != ZASMT_EOF) {
    zasm_token t = tokens[i];

    if (t.type == ZASMT_IDENT && tokens[i+1].type == ZASMT_PUNCT && *tokens[i+1].start == ':') {
      printf("Parsing Label: %.*s\n", (int)t.len, t.start);
      i += 2;
      continue;
    }

    if (t.type == ZASMT_IDENT && strncmp(t.start, "syscall", t.len) == 0) {
      i++;
      if (tokens[i].type != ZASMT_IDENT) 
        report_error(current_line, "Expected syscall name after", tokens[i]);

      zasm_token syscall_name = tokens[i++];
      if (get_syscall(syscall_name) == -1)
        report_error(current_line, "Invalid syscall", syscall_name);
      if (tokens[i].type != ZASMT_PUNCT || *tokens[i].start != '(')
        report_error(current_line, "Expected '(' after syscall name", syscall_name);

      continue;
    }

    if (t.type == ZASMT_IDENT) {
      i++; 
      // if (!is_valid_instr(t)) report_error(...);
      continue;
    }

    if (t.type == ZASMT_PUNCT && *t.start == '\n') current_line++;
    i++;
  }
  return nullptr;
}
