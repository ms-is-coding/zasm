#ifndef ZASM_AST_H
#define ZASM_AST_H

#include <stddef.h>

typedef enum {
  ZASMN_NONE,
  ZASMN_PROGRAM,
  ZASMN_LABEL,
  ZASMN_INSTR,
  ZASMN_SYSCALL,
} zasm_node_type;

typedef struct {
  zasm_node_type type;
} zasm_node;

typedef struct {
  size_t    stmt_count;
  zasm_node *stmt;
} zasm_program;

typedef struct {
  zasm_node base;
  int       syscall_num;
  int       arg_count;
} zasm_syscall;

typedef struct {
  zasm_node base;
  char      *name;
} zasm_label;

#endif
