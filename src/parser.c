#include "zasm.h"
#include "ast.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

static zasm_operand parse_operand(
  zasm_file  in,
  zasm_token *tokens,
  size_t     *index,
  size_t     count
) {
  zasm_operand op = {0};
  zasm_token t = tokens[*index];

  if (t.type == ZASMT_NUM) {
    op.type = ZASMO_IMM;
    op.imm_val = t.value;
  } 
  else if (t.type == ZASMT_PUNCT && *t.start == '[') {
    op.type = ZASMO_MEM;
    (*index)++;
    if (*index >= count || tokens[*index].type != ZASMT_IDENT)
      zasm_error(in, tokens[*index], "Expected register inside brackets");
    op.mem.base_reg = strndup(tokens[*index].start, tokens[*index].len);

    while (*index < count && !(tokens[*index].type == ZASMT_PUNCT && *tokens[*index].start == ']')) {
      (*index)++;
    }
    if (*index >= count)
      zasm_error(in, t, "Unclosed memory operand");
  } 
  else if (t.type == ZASMT_IDENT) {
    op.type = ZASMO_REG;
    op.reg_name = strndup(t.start, t.len);
  }
  else if (t.type == ZASMT_STR) {
    op.type = ZASMO_STR;
    op.str_val = strndup(t.start, t.len);
  }
  else {
    zasm_error(in, t, "Invalid operand");
  }

  return op;
}

void prog_add_node(zasm_program *prog, zasm_node *node) {
  prog->nodes = realloc(prog->nodes, sizeof(zasm_node *) * (prog->node_count + 1));
  prog->nodes[prog->node_count++] = node;
}

zasm_node* create_syscall_node(int num, int line) {
  zasm_syscall *node = malloc(sizeof(zasm_syscall));
  node->base.type = ZASMN_SYSCALL;
  node->base.line = line;
  node->id = num;
  node->arg_count = 0;
  return (zasm_node*)node;
}

zasm_node* create_label_node(zasm_token t, int line) {
  zasm_label *node = malloc(sizeof(zasm_label));
  node->base.type = ZASMN_LABEL;
  node->base.line = line;
  node->name = strndup(t.start, t.len);
  return (zasm_node*)node;
}

zasm_program *zasm_parse(zasm_file in, zasm_token *tokens, size_t count) {
  size_t i = 0;
  int current_line = 1;

  zasm_program *prog = malloc(sizeof(zasm_program));
  prog->base.type = ZASMN_PROGRAM;
  prog->nodes = nullptr;
  prog->node_count = 0;

  while (i < count && tokens[i].type != ZASMT_EOF) {
    zasm_token t = tokens[i];

    if (t.type == ZASMT_NEWL) {
      current_line++;
      i++;
      continue;
    }

    if (t.type == ZASMT_IDENT && (i + 1 < count) &&
      tokens[i+1].type == ZASMT_PUNCT && *tokens[i+1].start == ':') {

      prog_add_node(prog, create_label_node(t, current_line));
      i += 2;
      continue;
    }

    if (t.type == ZASMT_IDENT && strncmp(t.start, "syscall", t.len) == 0) {
      i++; 
      if (tokens[i].type != ZASMT_IDENT) 
        zasm_error(in, tokens[i], "Expected syscall name");

      zasm_token name_tok = tokens[i++];
      int sc_num = get_syscall(name_tok);

      if (sc_num == -1)
        zasm_error(in, name_tok, "Unknown syscall");

      zasm_syscall *sc_node = (zasm_syscall*)create_syscall_node(sc_num, current_line);

      if (tokens[i].type != ZASMT_PUNCT || *tokens[i].start != '(')
        zasm_error(in, tokens[i], "Expected '('");
      i++;

      while (i < count && !(tokens[i].type == ZASMT_PUNCT && *tokens[i].start == ')')) {
        if (sc_node->arg_count < 6) {
          sc_node->args[sc_node->arg_count++] = parse_operand(in, tokens, &i, count);
        } else {
          zasm_error(in, tokens[i], "Too many arguments for syscall");
        }

        i++;
        if (tokens[i].type == ZASMT_PUNCT && *tokens[i].start == ',') {
          i++;
        }
      }

      if (tokens[i].type != ZASMT_PUNCT || *tokens[i].start != ')')
        zasm_error(in, tokens[i], "Expected ')' to close syscall");

      i++;
      prog_add_node(prog, (zasm_node*)sc_node);
      continue;
    }

    if (t.type == ZASMT_IDENT) {
      zasm_instr *ins = malloc(sizeof(zasm_instr));
      ins->base.type = ZASMN_INSTR;
      ins->base.line = current_line;
      ins->mnemonic = strndup(t.start, t.len);
      ins->op_count = 0;
      i++;

      while (i < count && tokens[i].type != ZASMT_EOF) {
        if (tokens[i].type == ZASMT_NEWL) break;

        if (ins->op_count < 4) {
          ins->ops[ins->op_count++] = parse_operand(in, tokens, &i, count);
        }
        i++;
        if (i < count && tokens[i].type == ZASMT_PUNCT && *tokens[i].start == ',') i++;
        else break;
      }
      prog_add_node(prog, (zasm_node *)ins);
      continue;
    }

    i++;
  }

  return prog;
}
