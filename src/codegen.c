#include "ast.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>

typedef struct {
  uint8_t *buffer;
  size_t size;
  size_t capacity;
  uint64_t vaddr_start;
} zasm_emitter;

void emit_byte(zasm_emitter *e, uint8_t b) {
  if (e->size >= e->capacity) return;
  e->buffer[e->size++] = b;
}

void emit_bytes(zasm_emitter *e, uint8_t *bytes, size_t len) {
  for (size_t i = 0; i < len; i++) emit_byte(e, bytes[i]);
}

int get_reg_id(const char *name) {
  if (strcmp(name, "rax") == 0 || strcmp(name, "eax") == 0 || strcmp(name, "al") == 0) return 0;
  if (strcmp(name, "rcx") == 0) return 1;
  if (strcmp(name, "rdx") == 0 || strcmp(name, "dl") == 0) return 2;
  if (strcmp(name, "rbx") == 0) return 3;
  if (strcmp(name, "rsp") == 0) return 4;
  if (strcmp(name, "rbp") == 0) return 5;
  if (strcmp(name, "rsi") == 0) return 6;
  if (strcmp(name, "rdi") == 0 || strcmp(name, "edi") == 0) return 7;
  return -1;
}

void emit_mov_imm(zasm_emitter *e, int reg, uint64_t val) {
  emit_byte(e, 0x48);
  emit_byte(e, 0xB8 + (reg & 7));
  emit_bytes(e, (uint8_t*)&val, 8);
}

void emit_syscall_macro(zasm_emitter *e, zasm_syscall *sc) {
  const char *sys_regs[] = {"rdi", "rsi", "rdx", "r10", "r8", "r9"};

  for (int i = 0; i < sc->arg_count && i < 6; i++) {
    zasm_operand op = sc->args[i];
    int target_reg = get_reg_id(sys_regs[i]);

    if (op.type == ZASMO_IMM) {
      emit_mov_imm(e, target_reg, op.imm_val);
    } else if (op.type == ZASMO_REG) {
      int src_reg = get_reg_id(op.reg_name);
      emit_byte(e, 0x48);
      emit_byte(e, 0x89);
      emit_byte(e, 0xC0 + (src_reg << 3) + target_reg);
    }
  }

  emit_mov_imm(e, 0, sc->id);

  emit_byte(e, 0x0F);
  emit_byte(e, 0x05);
}

void emit_instruction(zasm_emitter *e, zasm_instr *ins) {

  if (strcmp(ins->mnemonic, "syscall") == 0) {
    emit_byte(e, 0x0F);
    emit_byte(e, 0x05);
  } 
  else if (strcmp(ins->mnemonic, "xor") == 0) {
    if (ins->op_count == 2 && strcmp(ins->ops[0].reg_name, "edi") == 0) {
      emit_byte(e, 0x31);
      emit_byte(e, 0xFF);
    }
  }
}

void zasm_codegen(zasm_program *prog, uint8_t *out_buf, size_t out_max) {
  zasm_emitter e = {
    .buffer = out_buf,
    .capacity = out_max,
    .size = 0,
    .vaddr_start = 0x10000
  };

  for (size_t i = 0; i < prog->node_count; ++i) {
    zasm_node *node = prog->nodes[i];

    switch (node->type) {
      case ZASMN_LABEL:
        break;

      case ZASMN_SYSCALL:
        emit_syscall_macro(&e, (zasm_syscall *)node);
        break;

      case ZASMN_INSTR:
        emit_instruction(&e, (zasm_instr *)node);
        break;

      default:
        break;
    }
  }
}
