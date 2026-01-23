#include "ast.h"
#include <stdio.h>

static void print_operand(zasm_operand op) {
    switch (op.type) {
        case ZASMO_REG:
            printf("Reg(%s)", op.reg_name);
            break;
        case ZASMO_IMM:
            printf("Imm(%ld)", op.imm_val);
            break;
        case ZASMO_LABEL:
            printf("LabelRef(%s)", op.label_ref);
            break;
        case ZASMO_MEM:
            printf("Mem([%s])", op.mem.base_reg);
            break;
    }
}

void zasm_print_ast(zasm_program *prog) {
    if (!prog) return;

    printf("--- ZASM AST DEBUG ---\n");
    for (size_t i = 0; i < prog->node_count; i++) {
        zasm_node *node = prog->nodes[i];
        printf("[%03d] ", node->line);

        switch (node->type) {
            case ZASMN_LABEL: {
                zasm_label *l = (zasm_label *)node;
                printf("LABEL: %s:\n", l->name);
                break;
            }
            case ZASMN_SYSCALL: {
                zasm_syscall *s = (zasm_syscall *)node;
                printf("SYSCALL: id=%d (", s->id);
                for (int j = 0; j < s->arg_count; j++) {
                    print_operand(s->args[j]);
                    if (j < s->arg_count - 1) printf(", ");
                }
                printf(")\n");
                break;
            }
            case ZASMN_INSTR: {
                zasm_instr *ins = (zasm_instr *)node;
                printf("INSTR:   %-8s ", ins->mnemonic);
                for (int j = 0; j < ins->op_count; j++) {
                    print_operand(ins->ops[j]);
                    if (j < ins->op_count - 1) printf(", ");
                }
                printf("\n");
                break;
            }
            default:
                printf("UNKNOWN_NODE_TYPE\n");
                break;
        }
    }
    printf("--- END AST ---\n");
}
