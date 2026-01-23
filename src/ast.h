#ifndef ZASM_AST_H
#define ZASM_AST_H

#include <stddef.h>
#include "token.h"

typedef enum {
  ZASMN_NONE,
  ZASMN_PROGRAM,
  ZASMN_LABEL,
  ZASMN_INSTR,
  ZASMN_SYSCALL,
} zasm_node_type;

typedef enum {
  ZASMO_NONE,
  ZASMO_REG,
  ZASMO_IMM,
  ZASMO_MEM,
  ZASMO_LABEL,
} zasm_op_type;

typedef struct {
  zasm_op_type type;
  union {
    char *reg_name;
    long imm_val;
    char *label_ref;
    struct {
      char *base_reg;
      int offset;
    } mem;
  };
} zasm_operand;

typedef struct {
  zasm_node_type  type;
  int             line;
} zasm_node;

typedef struct {
  zasm_node base;
  size_t    node_count;
  zasm_node **nodes;
} zasm_program;

typedef struct {
  zasm_node     base;
  int           id;
  int           arg_count;
  zasm_operand  args[6];
} zasm_syscall;

typedef struct {
  zasm_node base;
  char      *name;
} zasm_label;

typedef struct {
  zasm_node     base;
  char          *mnemonic;
  zasm_operand  ops[4];
  int           op_count;
} zasm_instr;

#endif
